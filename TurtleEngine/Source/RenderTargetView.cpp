#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "DepthStencilView.h"

HRESULT
RenderTargetView::init(Device& device, Texture& backBuffer, DXGI_FORMAT format) {
  HRESULT hr = S_OK;

  // Validar que el dispositivo no sea nulo
  if (device.m_device == nullptr) {
    ERROR("RenderTargetView", "init", "Device is nullptr in RenderTargetView init method");
    ///return E_POINTER;  // Retorna un código de error si el dispositivo es nulo
  }

  // Validar que el back buffer tenga una textura válida
  if (!backBuffer.m_texture) {
    ERROR("RenderTargetView", "init", "backBuffer texture is nullptr in RenderTargetView init method");
    ///return E_POINTER;  // Retorna un código de error si la textura del back buffer es nula
  }

  D3D11_RENDER_TARGET_VIEW_DESC desc;
  memset(&desc, 0, sizeof(desc));  // Inicializar la estructura a cero

  desc.Format = format;  // Establecer el formato del render target view
  desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;  // Definir la dimensión del render target view como 2D Multisampled (MS)

  // Intentar crear el RenderTargetView usando la textura del back buffer y las descripciones proporcionadas
  hr = device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);

  if (FAILED(hr)) {
    ERROR("RenderTargetView", "CreateRenderTargetView", "Failed to create Render Target View.");
    return hr;  // Retorna el código de error si la creación del RenderTargetView falla
  }

  return S_OK;  // Retorna S_OK si la inicialización fue exitosa
}

void 
RenderTargetView::update() {
}

void 
RenderTargetView::render(DeviceContext& deviceContext, 
                        DepthStencilView& depthStencilView, 
                        unsigned int numOfViews, 
                        const float clearColor[4]) {
  // Validar que el DeviceContext no sea nulo
  if (!deviceContext.m_deviceContext) {
    ERROR("RenderTargetView", "render", "DeviceContext is nullptr in RenderTargetView render method");
    ///return;  // Retorna si el contexto del dispositivo no está inicializado correctamente
  }

  // Validar que el DepthStencilView no sea nulo
  if (!depthStencilView.m_depthStencilView) {
    ERROR("RenderTargetView", "render", "DepthStencilView is nullptr in RenderTargetView render method");
    ///return;  // Retorna si el DepthStencilView no está correctamente inicializado
  }

  // Limpiar el render target view con el color proporcionado
  deviceContext.ClearRenderTargetView(m_renderTargetView, clearColor);

  // Asignar el render target view y el depth stencil view al pipeline de salida
  deviceContext.OMSetRenderTargets(numOfViews, &m_renderTargetView, depthStencilView.m_depthStencilView);
}

void 
RenderTargetView::destroy() {
  // Liberar el recurso del RenderTargetView de forma segura para evitar fugas de memoria
  SAFE_RELEASE(m_renderTargetView);
}