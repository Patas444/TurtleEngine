#pragma once
#include "Prerequisites.h"

// Forward Declarations - Declaraciones Directas
class Device;
class DeviceContext;
class Window;
class Texture;

/**
 * @class SwapChain
 * 
 *
 * La clase `SwapChain` es responsable de gestionar la cadena de intercambio de buffers, 
 * lo que permite la presentación de contenido en la pantalla mediante Direct3D 11.
 * La cadena de intercambio se utiliza para manejar el rendering a la pantalla, 
 * alternando entre un buffer trasero y el buffer frontal que se muestra al usuario.
 */
class 
SwapChain {
public:
  SwapChain() = default;  ///< Constructor por defecto.
  ~SwapChain() = default; ///< Destructor.

  // Inicializa la cadena de intercambio.
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

  // Libera los recursos asociados a la cadena de intercambio.
  void 
  destroy();

  // Presenta el contenido en la cadena de intercambio.
  void
  present();

public:
  IDXGISwapChain* g_pSwapChain = nullptr; ///< Puntero a la cadena de intercambio de DirectX (IDXGISwapChain).
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL; ///< Tipo de controlador de Direct3D.

private:
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0; ///< Nivel de características soportado por Direct3D.
  
  // MSAA Configuration
  /*
   * Para evitar que los píxeles se vean con un efecto de "serrucho" (aliasing) en DirectX 11 con C++,
   * se puede utilizar una técnica llamada anti-aliasing.
   *
   * Multisample Anti-Aliasing (MSAA)
   * MSAA es una técnica que suaviza los bordes de los objetos al muestrear varios puntos por píxel.
   * Para habilitar MSAA en DirectX 11:
   *
   */
  unsigned int m_sampleCount; ///< Número de muestras MSAA (ejemplo: 4x MSAA).
  unsigned int m_qualityLevels; ///< Niveles de calidad para MSAA.

  // Punteros a las interfaces DXGI
  IDXGIDevice* m_dxgiDevice = nullptr; ///< Puntero a la interfaz de dispositivo DXGI.
  IDXGIAdapter* m_dxgiAdapter = nullptr; ///< Puntero a la interfaz de adaptador DXGI.
  IDXGIFactory* m_dxgiFactory = nullptr; ///< Puntero a la fábrica DXGI.
};
