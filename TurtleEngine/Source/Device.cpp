#include "Device.h"

// M�todo para destruir el dispositivo
void 
Device::destroy() {
  SAFE_RELEASE(m_device); // Liberar el dispositivo
}

// M�todo para crear un Render Target View
HRESULT
Device::CreateRenderTargetView(ID3D11Resource* pResource, 
                              const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
                              ID3D11RenderTargetView** ppRTView) {
  // Validar par�metros de entrada
  if (!pResource) {
    ERROR("Device", "CreateRenderTargetView", "pResource is nullptr");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppRTView) {
    ERROR("Device", "CreateRenderTargetView", "ppRTView is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Render Target View
  HRESULT hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateRenderTargetView", "Render Target View created successfully!");
  } else {
    ERROR("Device", "CreateRenderTargetView",
      ("Failed to create Render Target View. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

// M�todo para crear una textura 2D
HRESULT 
Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, 
                        const D3D11_SUBRESOURCE_DATA* pInitialData, 
                        ID3D11Texture2D** ppTexture2D) {
  // Validar par�metros de entrada
  if (!pDesc) {
    ERROR("Device", "CreateTexture2D", "pDesc is nullptr");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppTexture2D) {
    ERROR("Device", "CreateTexture2D", "ppTexture2D is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear la textura 2D
  HRESULT hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateTexture2D", "Texture2D created successfully!");
  } else {
    ERROR("Device", "CreateTexture2D",
      ("Failed to create Texture 2D. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

// M�todo para crear un Depth Stencil View
HRESULT 
Device::CreateDepthStencilView(ID3D11Resource* pResource, 
                              const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
                              ID3D11DepthStencilView** ppDepthStencilView) {
  // Validar par�metros de entrada
  if (!pResource) {
    ERROR("Device", "CreateDepthStencilView", "pResource is nullptr");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppDepthStencilView) {
    ERROR("Device", "CreateDepthStencilView", "ppDepthStencilView is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Depth Stencil View
  HRESULT hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateDepthStencilView", "Depth Stencil View created successfully!");
  } else {
    ERROR("Device", "CreateDepthStencilView",
      ("Failed to create Depth Stencil View. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}
HRESULT 
Device::CreateVertexShader(const void* pShaderBytecode, 
                          unsigned int BytecodeLength, 
                          ID3D11ClassLinkage* pClassLinkage, 
                          ID3D11VertexShader** ppVertexShader) {
  // Validar par�metros de entrada
  if (!pShaderBytecode) {
    ERROR("Device", "CreateVertexShader", "Invalid shader bytecode");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (BytecodeLength == 0) {
    ERROR("Device", "CreateVertexShader", "Bytecode length is 0");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppVertexShader) {
    ERROR("Device", "CreateVertexShader", "ppVertexShader is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Vertex Shader
  HRESULT hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateVertexShader", "Vertex Shader created successfully!");
  } else {
    ERROR("Device", "CreateVertexShader",
      ("Failed to create Vertex Shader. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT 
Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 
                          unsigned int NumElements, 
                          const void* pShaderBytecodeWithInputSignature, 
                          unsigned int BytecodeLength, 
                          ID3D11InputLayout** ppInputLayout) {
  // Validar par�metros de entrada
  if (!pInputElementDescs) {
    ERROR("Device", "CreateInputLayout", "Invalid input element description");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!pShaderBytecodeWithInputSignature) {
    ERROR("Device", "CreateInputLayout", "Invalid shader bytecode");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppInputLayout) {
    ERROR("Device", "CreateInputLayout", "ppInputLayout is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Input Layout
  HRESULT hr = m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateInputLayout", "Input Layout created successfully!");
  } else {
    ERROR("Device", "CreateInputLayout",
      ("Failed to create Input Layout. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT 
Device::CreatePixelShader(const void* pShaderBytecode, 
                          unsigned int BytecodeLength, 
                          ID3D11ClassLinkage* pClassLinkage,
                          ID3D11PixelShader** ppPixelShader) {
  // Validar par�metros de entrada
  if (!pShaderBytecode) {
    ERROR("Device", "CreateInputLayout", "Invalid shader bytecode");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (BytecodeLength == 0) {
    ERROR("Device", "CreateVertexShader", "Bytecode length is 0");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppPixelShader) {
    ERROR("Device", "CreateInputLayout", "ppPixelShader is nullptr");
    return E_INVALIDARG; // Puntero nulo
  }

  // Crear el Pixel Shader
  HRESULT hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreatePixelShader", "Pixel Shader created successfully!");
  } else {
    ERROR("Device", "CreatePixelShader",
      ("Failed to create Pixel Shader. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT 
Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, 
                    const D3D11_SUBRESOURCE_DATA* pInitialData, 
                    ID3D11Buffer** ppBuffer) {
  // Validar par�metros de entrada
  if (!pDesc) {
    ERROR("Device", "CreateBuffer", "pDesc is nullptr");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppBuffer) {
    ERROR("Device", "CreateBuffer", "ppBuffer is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Buffer
  HRESULT hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateBuffer", "Buffer created successfully!");
  } else {
    ERROR("Device", "CreateBuffer",
      ("Failed to create Buffer. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT 
Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, 
                           ID3D11SamplerState** ppSamplerState) {
  // Validar par�metros de entrada
  if (!pSamplerDesc) {
    ERROR("Device", "CreateSamplerState", "pSamplerDesc is nullptr");
    return E_INVALIDARG; // Argumento inv�lido
  }

  if (!ppSamplerState) {
    ERROR("Device", "CreateSamplerState", "ppSamplerState is nullptr");
    return E_POINTER; // Puntero nulo
  }

  // Crear el Sampler State
  HRESULT hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);

  // Comprobaci�n de �xito o error
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateSamplerState", "Sampler State created successfully!");
  } else {
    ERROR("Device", "CreateSamplerState",
      ("Failed to create Sampler State. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}
