#include "BaseApp.h"

/**
 * Inicializa la aplicación.
 * Creación de un dispositivo Direct3D y una cadena de intercambio.
 * @return HRESULT con el estado de la inicialización.
 */

HRESULT
BaseApp::init() {
	HRESULT hr = S_OK;

	// Inicializa Swapchain y BackBuffer
	hr = m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
	if (FAILED(hr)) {
		return hr;
	}

	// Crea el Render Target View
	hr = m_renderTargetView.init(m_device,
		m_backBuffer,
		DXGI_FORMAT_R8G8B8A8_UNORM);
	if (FAILED(hr)) {
		return hr;
	}

	// Crea el Depth Stencil
	hr = m_depthStencil.init(m_device,
		m_window.m_width,
		m_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_BIND_DEPTH_STENCIL, 4, 16);
	if (FAILED(hr)) {
		return hr;
	}

	// Crea la vista Depth Stencil View
	hr = m_depthStencilView.init(m_device,
		m_depthStencil,
		DXGI_FORMAT_D24_UNORM_S8_UINT);
	if (FAILED(hr)) {
		return hr;
	}

	// Configura el viewport
	hr = m_viewport.init(m_window);

	// Definición del Input Layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	D3D11_INPUT_ELEMENT_DESC position{};
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord{};
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	// Creación del Shader Program
	hr = m_shaderProgram.init(m_device, "TurtleEngine.fx", Layout);
	if (FAILED(hr)) {
		return hr;
	}

	// Creación del buffer constante
	hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
	if (FAILED(hr))
		return hr;

	hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
	if (FAILED(hr))
		return hr;

	// Inicialización de View Matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);

	m_UI.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

	// Set Actor: Mario and Luigi
	//m_loader.LoadFBXModel("Models/GIRL_fbx.fbx");

	// Load the Texture
	Texture BaseColor;
	BaseColor.init(m_device, "Texture/RMSH/RedMushroom_BaseColor.png", ExtensionType::PNG);

	m_default.init(m_device, "Texture/RMSH/Default.png", ExtensionType::PNG);

	m_Textures.push_back(BaseColor);

	m_Textures.push_back(m_default);
	// Set Actor: Mario and Luigi
	m_loader.LoadFBXModel("Models/Mushroom.fbx");

	
	AModel = EngineUtilities::MakeShared<Actor>(m_device);
	if (!AModel.isNull()) {
		// Init Transform
		AModel->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(2.0f, 1.0f, 1.0f),
			EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f),
			EngineUtilities::Vector3(1.0f, 1.0f, 1.0f));
		// Init Actor Mesh
		AModel->setMesh(m_device, m_loader.meshes);
		// Init Actor Textures
		AModel->setTextures(m_Textures);

		m_actors.push_back(AModel);


		std::string msg = AModel->getName() + "Actor accessed successfully.";
		MESSAGE("Actor", "Actor", msg.c_str());
	}
	else {
		MESSAGE("Actor", "Actor", "Actor resource not found")
	}

	return S_OK;
}

// Actualiza el estado de la aplicación en cada iteración del bucle principal.
void 
BaseApp::update() {
	// Updates the UI
	m_UI.update();

	m_UI.GUITab("GUI");
	m_UI.transformWindow(*AModel->getComponent<Transform>());

	// Actualizar tiempo y rotaci�n
	static float t = 0.0f;
	if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	inputActionMap(t);

	// Initialize the projection matrix
	float FOV = XMConvertToRadians(90.0f);
	m_Projection = XMMatrixPerspectiveFovLH(FOV, m_window.m_width / (float)m_window.m_height, 0.01f, 10000.0f);

	upadteCamera();

	// Actualizar la proyecci�n en el buffer constante
	cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
	m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	AModel->update(0, m_deviceContext);
}

// Renderiza el contenido de la aplicación en la pantalla.
void 
BaseApp::render() {
	// Limpiar los buffers
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// Establecer el Viewport
	m_viewport.render(m_deviceContext);

	// Establecer el Render Target View
	m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

	// Establecer el Depth Stencil View
	m_depthStencilView.render(m_deviceContext);

	// Configurar los buffers y shaders para el pipeline
	m_shaderProgram.render(m_deviceContext);

	// Render the models
	AModel->render(m_deviceContext);

	// Renderizar buffers constantes en el Vertex Shader
	m_neverChanges.render(m_deviceContext, 0, 1);
	m_changeOnResize.render(m_deviceContext, 1, 1);

	// Render the UI
	m_UI.render();

	// Presentar el frame en pantalla
	m_swapchain.present();
}

// Libera los recursos utilizados por la aplicación antes de cerrarla.
void
BaseApp::destroy() {
	if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

	AModel->destroy();

	m_changeOnResize.destroy();
	m_changeEveryFrame.destroy();
	m_neverChanges.destroy();
	m_shaderProgram.destroy();
	m_depthStencil.destroy();
	m_depthStencilView.destroy();
	m_renderTargetView.destroy();
	m_swapchain.destroy();
	m_deviceContext.destroy();
	m_device.destroy();
	m_UI.destroy();
}

HRESULT 
BaseApp::resizeWindow(HWND hWnd, LPARAM lParam) {
	if (m_swapchain.g_pSwapChain) {

		// Libera los recursos existentes
		m_renderTargetView.destroy();
		m_depthStencil.destroy();
		m_depthStencilView.destroy();
		m_backBuffer.destroy();

		// Redimensionar los datos del ancho y alto de la ventana
		m_window.m_width = LOWORD(lParam);
		m_window.m_height = HIWORD(lParam);

		// Redimensionar el swap chain
		HRESULT hr = m_swapchain.g_pSwapChain->ResizeBuffers(0,
				m_window.m_width,
				m_window.m_height,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				0);
		if (FAILED(hr)) {
			ERROR("ResizeWindow", "SwapChain", "Failed to resize buffers");
			return hr;
		}

		// Recrear el backBuffer
		hr = m_swapchain.g_pSwapChain->GetBuffer(0,
			__uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&m_backBuffer.m_texture));
		if (FAILED(hr)) {
			ERROR("ResizeWindow", "ResizeWindow", "Failed to recreate back buffer");
			return hr;
		}

		// Recrear el render target view
		hr = m_renderTargetView.init(m_device,
			m_backBuffer,
			DXGI_FORMAT_R8G8B8A8_UNORM);
		if (FAILED(hr)) {
			ERROR("ResizeWindow", "Render Target View", "Failed to create Render Target View");
			return hr;
		}

		// Recrear el depth stencil
		hr = m_depthStencil.init(m_device,
			m_window.m_width,
			m_window.m_height,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			D3D11_BIND_DEPTH_STENCIL,
			4,
			0);
		if (FAILED(hr)) {
			ERROR("ResizeWindow", "Depth Stencil", "Failed to create Depth Stencil");
			return hr;
		}

		// Recrear el depth stencil view
		hr = m_depthStencilView.init(m_device,
			m_depthStencil,
			DXGI_FORMAT_D24_UNORM_S8_UINT);
		if (FAILED(hr)) {
			ERROR("ResizeWindow", "Depth Stencil View", "Failed to create new Depth Stencil View");
			return hr;
		}

		// Actualizar el viewport
		m_viewport.init(m_window);

		m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
		cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
		m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	}
}

void
BaseApp::inputActionMap(float deltaTime) {

	float sensibility = 0.001f; // Sensibilidad del movimiento
	float Cam_Sensibility = 0.001f; // Sensibilidad de la cámara
/*
	if (key[87]) { // W
		position.y += sensibility * deltaTime;
	}
	if (key[83]) { // S
		position.y -= sensibility * deltaTime;
	}

	if (key[65]) { // A
		position.x -= sensibility * deltaTime;
	}
	if (key[68]) { // D
		position.x += sensibility * deltaTime;
	}

	if (key[81]) { // Q
		position.z -= sensibility * deltaTime;
	}
	if (key[69]) { // E
		position.z += sensibility * deltaTime;
	}
*/

	// Cargar posición y direcciones de la cámara
	XMVECTOR pos = XMLoadFloat3(&m_camera.position);
	XMVECTOR forward = XMLoadFloat3(&m_camera.forward);
	XMVECTOR right = XMLoadFloat3(&m_camera.right);

	if (key[VK_UP]) pos += forward * sensibility;
	if (key[VK_DOWN]) pos -= forward * sensibility;
	if (key[VK_LEFT]) pos -= right * sensibility;
	if (key[VK_RIGHT]) pos += right * sensibility;

	// Guardar la nueva posición de la cámara
	XMStoreFloat3(&m_camera.position, pos);
}

void
BaseApp::upadteCamera() {
	//Covertir la dirección a vectores normalizados
	XMVECTOR pos = XMLoadFloat3(&m_camera.position);
	XMVECTOR dir = XMLoadFloat3(&m_camera.forward);
	XMVECTOR up = XMLoadFloat3(&m_camera.up);

	//Calcular la nueva bista
	m_View = XMMatrixLookAtLH(pos, pos + dir, up);

	//Transponer y actualizar el buffer de la vista
	cbNeverChanges.mView = XMMatrixTranspose(m_View);
	m_neverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void
BaseApp::rotateCamera(int mouseX, int mouseY) {
	// Calcular el desplazamiento del mouse en X e Y
	float offsetX = (mouseX - lastX) * camSpeed;
	float offsetY = (mouseY - lastY) * camSpeed;
	lastX = mouseX;
	lastY = mouseY;

	// Aplicar desplazamiento a la orientación de la cámara
	m_camera.yaw += offsetX;
	m_camera.pitch += offsetY;

	// Limitar el ángulo de inclinación (pitch) de la cámara
	if (m_camera.pitch > 1.5f) m_camera.pitch = 1.5f;
	if (m_camera.pitch < -1.5f) m_camera.pitch = -1.5f;

	// Calcular el vector de dirección (forward) de la cámara
	XMVECTOR forward = XMVectorSet(
		cosf(m_camera.yaw) * cosf(m_camera.pitch),
		sinf(m_camera.pitch),
		sinf(m_camera.yaw) * cosf(m_camera.pitch),
		0.0f
	);

	// Calcular el vector de la derecha (right) usando producto cruzado
	XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&m_camera.up));
	
	// Normalizar y almacenar los nuevos vectores de la cámara
	XMStoreFloat3(&m_camera.forward, XMVector3Normalize(forward));
	XMStoreFloat3(&m_camera.right, XMVector3Normalize(right));
}

/**
 * Ejecuta el bucle principal de la aplicación.
 * @return Código de salida de la aplicación.
 */
int 
BaseApp::run(HINSTANCE hInstance,
			 HINSTANCE hPrevInstance,
			 LPWSTR lpCmdLine,
			 int nCmdShow,
			 WNDPROC wndproc) {
			 UNREFERENCED_PARAMETER(hPrevInstance);
			 UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la aplicación
  if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
    return 0;

  if (FAILED(init())) {
    destroy();
    return 0;
  }

	// Bucle principal de mensajes y ejecución
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
	  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		  TranslateMessage(&msg);
		  DispatchMessage(&msg);
	  }
	  else {
		  update();
		  render();
	  }
  }

  destroy();

  return (int)msg.wParam;
}