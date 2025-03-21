#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Window.h"
#include "Texture.h"

HRESULT 
SwapChain::init(Device& device,
                DeviceContext& deviceContext,
                Texture& backBuffer,
                Window window) {
  // Verificar si el puntero de la ventana es válido
  if (!window.m_hWnd) {
    ERROR("SwapChain", "init", "Invalid Window handle (m_hWnd is nullptr)");
    return E_POINTER;
  }

  HRESULT hr = S_OK;

  // Configurar las banderas de creación para el dispositivo (habilitar depuración en modo de desarrollo)
  unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

  // Tipos de driver a probar para la creación del dispositivo
  D3D_DRIVER_TYPE driverTypes[] = {
    D3D_DRIVER_TYPE_HARDWARE,  // Usar el driver de hardware
    D3D_DRIVER_TYPE_WARP,      // Usar el driver de software (para depuración)
    D3D_DRIVER_TYPE_REFERENCE  // Usar el driver de referencia (para pruebas de comportamiento)
  };
  unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

  // Niveles de características que el dispositivo soportará
  D3D_FEATURE_LEVEL featureLevels[] = {
    D3D_FEATURE_LEVEL_11_0,  // Nivel de características 11.0
    D3D_FEATURE_LEVEL_10_1,  // Nivel de características 10.1
    D3D_FEATURE_LEVEL_10_0   // Nivel de características 10.0
  };
  unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

  // Intentar crear el dispositivo con cada tipo de driver
  for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
    m_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDevice(
      nullptr,                      // Sin un dispositivo de hardware existente
      m_driverType,                 // Tipo de driver a utilizar
      nullptr,                      // Sin un archivo de dispositivo de captura (p. ej. archivo pfx)
      createDeviceFlags,            // Bandera de creación del dispositivo
      featureLevels,                // Niveles de características soportados
      numFeatureLevels,             // Número de niveles de características
      D3D11_SDK_VERSION,            // Versión del SDK de Direct3D
      &device.m_device,             // Puntero al dispositivo creado
      &m_featureLevel,              // Nivel de características soportado
      &deviceContext.m_deviceContext // Puntero al contexto del dispositivo creado
    );

    if (SUCCEEDED(hr)) {
      break;  // Si se crea correctamente, salimos del bucle
    }
  }

  // Si la creación del dispositivo falló, reportamos el error
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to create D3D11 device");
    return hr;
  }

  // Configurar MSAA (Multisample Anti-Aliasing) 
  m_sampleCount = 4; // Configurar a 4 muestras por píxel
  hr = device.m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_sampleCount, &m_qualityLevels);
  if (FAILED(hr) || m_qualityLevels == 0) {
    ERROR("SwapChain", "init", "MSAA not supported or invalid quality level");
    return hr;
  }

  // Configurar la descripción del SwapChain (cadena de intercambios de buffers)
  DXGI_SWAP_CHAIN_DESC sd = {};
  sd.BufferCount = 1; // Solo un buffer de intercambio
  sd.BufferDesc.Width = window.m_width; // Ancho de la ventana
  sd.BufferDesc.Height = window.m_height; // Alto de la ventana
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Formato de color de los píxeles
  sd.BufferDesc.RefreshRate.Numerator = 60;  // 60Hz de frecuencia de refresco
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usar como destino de renderizado
  sd.OutputWindow = window.m_hWnd; // Asociar con la ventana de salida
  sd.Windowed = TRUE; // Mantener en modo ventana
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Descarta el contenido anterior cuando se realiza un intercambio
  sd.SampleDesc.Count = m_sampleCount; // Número de muestras por píxel
  sd.SampleDesc.Quality = m_qualityLevels - 1; // Máxima calidad de MSAA

  // Obtener la fábrica DXGI
  hr = device.m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgiDevice));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to query IDXGIDevice");
    return hr;
  }

  hr = m_dxgiDevice->GetAdapter(&m_dxgiAdapter); // Obtener el adaptador DXGI
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get DXGI Adapter");
    return hr;
  }

  // Conectar el adaptador a la fábrica DXGI
  hr = m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgiFactory));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get DXGI Factory");
    return hr;
  }

  // Crear el SwapChain
  hr = m_dxgiFactory->CreateSwapChain(device.m_device, &sd, &g_pSwapChain);
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to create SwapChain");
    return hr;
  }

  // Obtener el back buffer de la SwapChain
  hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer.m_texture));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get SwapChain buffer");
    return hr;
  }

  return S_OK;
}

void 
SwapChain::update() {
  // Este método no realiza ninguna actualización en este caso.
  // Puede ser utilizado para hacer cambios a la configuración del SwapChain si es necesario.
}

void 
SwapChain::render() {
  // Este método no realiza ninguna acción en este momento.
  // Puede ser usado para preparar la SwapChain para el renderizado, si fuera necesario.
}

void 
SwapChain::destroy() {
  // Liberar todos los recursos asociados al SwapChain y la fábrica DXGI
  SAFE_RELEASE(g_pSwapChain);
  SAFE_RELEASE(m_dxgiFactory);
  SAFE_RELEASE(m_dxgiAdapter);
  SAFE_RELEASE(m_dxgiDevice);
}

void 
SwapChain::present() {
  // Presentar el contenido del back buffer al front buffer
  if (g_pSwapChain) {
    HRESULT hr = g_pSwapChain->Present(0, 0); // Presentar sin sincronización vertical
    if (FAILED(hr)) {
      ERROR("Swapchain", "present", "Failed to present SwapChain");
    }
  }
  else {
    ERROR("Swapchain", "present", "SwapChain is nullptr");
  }
}
