#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * @class RenderTargetView
 * @brief Clase encargada de gestionar Render Target Views en Direct3D 11.
 *
 * Un Render Target View (RTV) permite renderizar gráficos en una textura en lugar de directamente en la pantalla.
 */
class 
RenderTargetView {
public:
	RenderTargetView()  = default;
	~RenderTargetView() = default;

 /**
  * @brief Inicializa un Render Target View a partir de un buffer de textura.
  * @param device Referencia al dispositivo Direct3D.
  * @param backBuffer Referencia a la textura utilizada como render target.
  * @param Format Formato de la textura (DXGI_FORMAT).
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  init(Device& device, Texture &backBuffer, DXGI_FORMAT Format);

  // Actualiza el estado del render target.
  void 
  update();
  
  // Renderiza el contenido en el render target.
  void 
  render(DeviceContext & deviceContext, 
         DepthStencilView & depthStencilView, 
         unsigned int numViews, 
         const float ClearColor[4]);
  
  // Libera los recursos asociados al Render Target View.
  void 
  destroy();

public:
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};