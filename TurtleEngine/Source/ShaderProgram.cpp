#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
ShaderProgram::init(Device& device, const std::string& fileName, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
  // Verificar si el dispositivo es nulo
  if (!device.m_device) {
    ERROR("ShaderProgram", "init", "Device is nullptr");
    return E_POINTER;
  }

  // Verificar si el layout de entrada está vacío
  if (Layout.empty()) {
    ERROR("ShaderProgram", "init", "Input layout vector is empty");
    return E_INVALIDARG;
  }

  m_shaderFileName = fileName;

  // Crear el Vertex Shader (sombra de vértices)
  HRESULT hr = CreateShader(device, ShaderType::VERTEX_SHADER);
  if (FAILED(hr)) return hr;

  // Crear el Input Layout
  hr = CreateInputLayout(device, Layout);
  if (FAILED(hr)) return hr;

  // Crear el Pixel Shader (sombra de píxeles)
  hr = CreateShader(device, ShaderType::PIXEL_SHADER);
  return hr;
}

void
ShaderProgram::update() {
  // Este método se deja vacío por ahora, pero puede ser usado para actualizar datos dinámicos.
  // Aquí podrías agregar actualizaciones de constantes o cambiar valores del shader si fuera necesario.
}

void
ShaderProgram::render(DeviceContext& deviceContext) {
  // Asegurarse de que los shaders y el input layout están correctamente inicializados
  if (!m_VertexShader || !m_PixelShader || !m_inputLayout.m_inputLayout) {
    ERROR("ShaderProgram", "render", "Shaders or InputLayout not initialized");
    return;
  }

  // Configurar el input layout y los shaders en el contexto de dispositivo para renderizar
  m_inputLayout.render(deviceContext);
  deviceContext.VSSetShader(m_VertexShader, nullptr, 0); // Establecer el Vertex Shader
  deviceContext.PSSetShader(m_PixelShader, nullptr, 0); // Establecer el Pixel Shader
}

void
ShaderProgram::destroy() {
  // Liberar todos los recursos asociados a los shaders y el input layout
  SAFE_RELEASE(m_VertexShader);
  m_inputLayout.destroy();
  SAFE_RELEASE(m_PixelShader);
  SAFE_RELEASE(m_vertexShaderData);
  SAFE_RELEASE(m_pixelShaderData);
}

HRESULT
ShaderProgram::CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
  // Verificar si los datos del Vertex Shader están disponibles antes de crear el Input Layout
  if (!m_vertexShaderData) {
    ERROR("ShaderProgram", "CreateInputLayout", "VertexShaderData is nullptr");
    return E_POINTER;
  }

  // Inicializar el input layout con la descripción proporcionada
  HRESULT hr = m_inputLayout.init(device, Layout, m_vertexShaderData);
  SAFE_RELEASE(m_vertexShaderData); // Liberar el shader compilado una vez que el input layout esté creado

  if (FAILED(hr)) {
    ERROR("ShaderProgram", "CreateInputLayout", "Failed to create InputLayout");
  }

  return hr;
}

HRESULT
ShaderProgram::CreateShader(Device& device, ShaderType type) {
  HRESULT hr = S_OK;
  ID3DBlob* shaderData = nullptr;
  const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";  // Determinar el punto de entrada del shader
  const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0"; // Establecer el modelo del shader (ps_4_0 o vs_4_0)

  // Compilar el shader desde el archivo
  hr = CompileShaderFromFile(m_shaderFileName.data(),
    shaderEntryPoint,
    shaderModel,
    &shaderData);
  if (FAILED(hr)) {
    ERROR("ShaderProgram", "CreateShader", "Failed to compile shader");
    return hr;
  }

  // Crear el shader según su tipo
  if (type == PIXEL_SHADER) {
    hr = device.CreatePixelShader(shaderData->GetBufferPointer(),
      shaderData->GetBufferSize(),
      nullptr,
      &m_PixelShader);
  }
  else {
    hr = device.CreateVertexShader(shaderData->GetBufferPointer(),
      shaderData->GetBufferSize(),
      nullptr,
      &m_VertexShader);
  }

  if (FAILED(hr)) {
    ERROR("ShaderProgram", "CreateShader", "Failed to create shader " + type);
    shaderData->Release();
    return hr;
  }

  // Almacenar el código compilado del shader
  if (type == PIXEL_SHADER) {
    SAFE_RELEASE(m_pixelShaderData);
    m_pixelShaderData = shaderData;
  }
  else {
    SAFE_RELEASE(m_vertexShaderData);
    m_vertexShaderData = shaderData;
  }

  return S_OK;
}

HRESULT
ShaderProgram::CompileShaderFromFile(char* szFileName, 
                                    LPCSTR szEntryPoint, 
                                    LPCSTR szShaderModel, 
                                    ID3DBlob** ppBlobOut) {
  HRESULT hr = S_OK;

  // Configurar las banderas de compilación para el shader
  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;  // Habilitar la estricta validación
#if defined( DEBUG ) || defined( _DEBUG )
  dwShaderFlags |= D3DCOMPILE_DEBUG;  // Activar modo depuración si es un entorno de desarrollo
#endif

  ID3DBlob* pErrorBlob = nullptr;
  
  // Compilar el shader desde el archivo fuente
  hr = D3DX11CompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
    dwShaderFlags, 0, nullptr, ppBlobOut, &pErrorBlob, nullptr);

  // Si la compilación falla, mostrar el error
  if (FAILED(hr)) {
    if (pErrorBlob != nullptr)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());  // Mostrar el error en la salida de depuración
    if (pErrorBlob) pErrorBlob->Release();  // Liberar el error
    return hr;
  }

  SAFE_RELEASE(pErrorBlob); // Liberar el blob de error si no hubo errores

  return S_OK;  // Retornar éxito si la compilación fue correcta
}
