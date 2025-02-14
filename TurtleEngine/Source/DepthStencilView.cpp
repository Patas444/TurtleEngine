#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

//  Inicializa la vista de Depth Stencil.
// @param device Referencia al objeto Device.
// @param depthStencil Referencia a la textura de Depth Stencil.
// @param format Formato DXGI del Depth Stencil.
// @return HRESULT indicando éxito o error en la inicialización.
HRESULT DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
  if (!device.m_device) {
    ERROR("DepthStencilView", "init", "Device is nullptr");
    return E_POINTER;
  }
  if (!depthStencil.m_texture) {
    ERROR("DepthStencilView", "init", "DepthStencil texture is nullptr");
    return E_POINTER;
  }

  HRESULT hr = S_OK;

  // Configurar la descripci�n de la vista del Depth Stencil
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  memset(&descDSV, 0, sizeof(descDSV));
  descDSV.Format = format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
  descDSV.Texture2D.MipSlice = 0;

  // Crear la Depth Stencil View
  hr = device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_depthStencilView);
  if (FAILED(hr)) {
    ERROR("DepthStencilView", "init", "Failed to create DepthStencilView");
    return hr;
  }

  return S_OK;
}

// Renderiza el Depth Stencil View limpiándolo.
// @param deviceContext Referencia al contexto del dispositivo.
void DepthStencilView::render(DeviceContext& deviceContext) {
  if (!m_depthStencilView) {
    ERROR("DepthStencilView", "render", "DepthStencilView is nullptr");
    return;
  }
  if (!deviceContext.m_deviceContext) {
    ERROR("DepthStencilView", "render", "DeviceContext is nullptr");
    return;
  }

  // Limpiar el depth stencil
  deviceContext.ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// Libera los recursos asociados al Depth Stencil View.
void DepthStencilView::destroy() {
  SAFE_RELEASE(m_depthStencilView);
}