#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

// Inicializa la vista (viewport) usando las dimensiones de una ventana dada
HRESULT 
Viewport::init(const Window& window) {
  HRESULT hr = S_OK;

  // Verifica si la ventana es v�lida
  if (window.m_hWnd == nullptr) {
    ERROR("Viewport", "init", "Window is nullptr in Viewport init method");
  }

  // Configura las propiedades de la vista (viewport)
  m_viewport.Width = static_cast<float>(window.m_width);  // Ancho de la ventana
  m_viewport.Height = static_cast<float>(window.m_height); // Alto de la ventana
  m_viewport.MinDepth = 0.0f;  // Profundidad m�nima
  m_viewport.MaxDepth = 1.0f;  // Profundidad m�xima
  m_viewport.TopLeftX = 0;     // Coordenada X de la esquina superior izquierda
  m_viewport.TopLeftY = 0;     // Coordenada Y de la esquina superior izquierda

  return E_NOTIMPL;  // Este m�todo a�n no est� implementado completamente
}

// Inicializa la vista (viewport) usando un ancho y alto espec�ficos
HRESULT 
Viewport::init(unsigned int width, unsigned int height) {
  // Verifica que el ancho no sea cero
  if (width == 0) {
    ERROR("Viewport", "init", "Width is zero in init method");
  }

  // Verifica que el alto no sea cero
  if (height == 0) {
    ERROR("Viewport", "init", "Height is zero in init method");
  }

  // Configura las propiedades de la vista (viewport)
  m_viewport.Width = static_cast<float>(width);
  m_viewport.Height = static_cast<float>(height);
  m_viewport.MinDepth = 0.0f;
  m_viewport.MaxDepth = 1.0f;
  m_viewport.TopLeftX = 0;
  m_viewport.TopLeftY = 0;

  return E_NOTIMPL;  // Este m�todo a�n no est� implementado completamente
}

// M�todo vac�o para actualizar la vista (viewport), pero est� reservado para futuras mejoras
void 
Viewport::update() {
  // No se realiza ninguna actualizaci�n por el momento
}

// Renderiza la vista (viewport) en el dispositivo de contexto especificado
void 
Viewport::render(DeviceContext& deviceContext) {
  // Verifica si el contexto del dispositivo es v�lido
  if (!deviceContext.m_deviceContext) {
    ERROR("Viewport", "render", "DeviceContext is nullptr in Viewport render method");
    return;
  }

  // Establece la vista (viewport) en el contexto del dispositivo
  deviceContext.RSSetViewports(1, &m_viewport);
}

// M�todo para destruir la vista, aunque no hay recursos din�micos que liberar en este caso
void 
Viewport::destroy() {
  // No hay recursos que liberar por ahora, pero este m�todo puede expandirse en el futuro
}
