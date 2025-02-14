#pragma once
#include "Prerequisites.h"

// Forward Declarations - Declaraciones Directas
class Device;
class DeviceContext;
class Window;
class Texture;

// Clase para manejar el intercambio de buffers en DirectX 11.
class 
SwapChain {
public:
	SwapChain()  = default;
	~SwapChain() = default;

    
  /**
   * @brief Inicializa la cadena de intercambio.
   * @param device Referencia al dispositivo de DirectX.
   * @param deviceContext Referencia al contexto del dispositivo.
   * @param backBuffer Referencia a la textura del buffer trasero.
   * @param window Referencia a la ventana asociada.
   * @return HRESULT Código de error si falla la inicialización.
  */
  HRESULT
  init(Device & device, 
       DeviceContext & deviceContext, 
       Texture & backBuffer, 
       Window window);

  // Actualiza el estado de la cadena de intercambio.
  void 
  update();
  
  // Renderiza el contenido en la cadena de intercambio.
  void 
  render();
  
  // Libera los recursos utilizados por la cadena de intercambio.
  void 
  destroy();

  // Presenta el buffer trasero en la pantalla.
  void
  present();

public:
  IDXGISwapChain* m_swapchain = nullptr;
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
  // MSAA Configuration
  /*
   * Para evitar que los p�xeles se vean con un efecto de "serrucho" (aliasing) en DirectX 11 con C++,
   * se puede utilizar una t�cnica llamada anti-aliasing.
   *
   * Multisample Anti-Aliasing (MSAA)
   * MSAA es una t�cnica que suaviza los bordes de los objetos al muestrear varios puntos por p�xel.
   * Para habilitar MSAA en DirectX 11:
   *
   */
  unsigned int m_sampleCount;  // Number of MSAA samples (4x MSAA)
  unsigned int m_qualityLevels;

  // Punteros a las interfaces DXGI
  IDXGIDevice* m_dxgiDevice = nullptr;
  IDXGIAdapter* m_dxgiAdapter = nullptr;
  IDXGIFactory* m_dxgiFactory = nullptr;

};