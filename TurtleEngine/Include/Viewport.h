#pragma once
#include "PreRequisites.h"

class Window;
class DeviceContext;

/**
 * @class Viewport
 * @brief Clase encargada de manejar el viewport en Direct3D 11.
 *
 * Un viewport define la región de la pantalla en la que se renderiza una imagen.
 * Esta clase permite configurar y actualizar el viewport en Direct3D 11, así como renderizar el contenido en esa región.
 */
class 
Viewport {
public:
  Viewport() = default; ///< Constructor por defecto.
  ~Viewport() = default; ///< Destructor.

  // Inicializa el viewport con las dimensiones de la ventana.
  HRESULT
  init(const Window& window);

  // Inicializa el viewport con las dimensiones especificadas.
  HRESULT
  init(unsigned int width, unsigned int height);

  // Actualiza el estado del viewport.
  void
  update();

  // Renderiza el contenido en el viewport.
  void
  render(DeviceContext& deviceContext);

  // Libera los recursos asociados al viewport.
  void
  destroy();

private:
  D3D11_VIEWPORT m_viewport; ///< Estructura interna que representa el viewport en Direct3D.
};
