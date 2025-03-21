#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

// Método para inicializar el DepthStencilView
HRESULT
DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
  HRESULT hr = S_OK;

  // Verificación de que el dispositivo no es nulo
  if (device.m_device == nullptr) {
    ERROR("RenderTargetView", "init", "Device is nullptr in DepthStencilView init method");
  }

  // Verificación de que la textura de DepthStencil no es nula
  if (!depthStencil.m_texture) {
    ERROR("RenderTargetView", "init", "depthStencil texture is nullptr in DepthStencilView init method");
  }

  // Configuración de las opciones del DepthStencilView
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  memset(&descDSV, 0, sizeof(descDSV));
  descDSV.Format = format;  // Formato de la vista
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS; // Tipo de vista (multisample)

  // Crear el DepthStencilView con la textura proporcionada
  hr = device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_depthStencilView);

  // Comprobación de errores en la creación del DepthStencilView
  if (FAILED(hr)) {
    ERROR("DepthStencilView", "CreateDepthStencilView", "Failed to create Depth Stencil View.");
    return hr;
  }

  return S_OK;
}

// Método de actualización (vacío en este caso)
void
DepthStencilView::update() {
}

// Método para renderizar, limpiando la vista de DepthStencil
void
DepthStencilView::render(DeviceContext& deviceContext) {
  // Verificación de que el contexto del dispositivo no es nulo
  if (!deviceContext.m_deviceContext) {
    ERROR("DepthStencilView", "render", "DeviceContext is nullptr in DepthStencilView render method");
  }

  // Limpiar el DepthStencilView
  deviceContext.ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// Método para destruir el DepthStencilView
void
DepthStencilView::destroy() {
  SAFE_RELEASE(m_depthStencilView);  // Liberar recursos del DepthStencilView
}
