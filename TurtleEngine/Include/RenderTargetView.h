#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

// Clase encargada de gestionar Render Target Views en Direct3D 11.
class 
RenderTargetView {
public:
  RenderTargetView()  = default;
  ~RenderTargetView() = default; 

  // Inicializa un Render Target View a partir de un buffer de textura.
  HRESULT
  init(Device& device, Texture& backBuffer, DXGI_FORMAT format);


  // Actualiza el estado del render target.
  void 
  update();
  
  // Renderiza el contenido en el render target.
  void
  render(DeviceContext& deviceContext, 
         DepthStencilView& depthStencilView, 
         unsigned int numOfViews, 
         const float clearColor[4]);
  
  //  Libera los recursos asociados al Render Target View.
  void 
  destroy();

public:
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
