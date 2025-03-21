#pragma once
#include "Prerequisites.h"

// Clase que encapsula la creación y gestión de una ventana en Windows.
class 
Window {
public:
  Window() = default; ///< Constructor por defecto.
  ~Window() = default; ///< Destructor.

  // Inicializa la ventana.
  HRESULT
  init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  // Actualiza el estado de la ventana.
  void
  update();

  // Renderiza el contenido en la ventana.
  void 
  render();
  
  // Libera los recursos asociados a la ventana.
  void 
  destroy();

public:
  HWND m_hWnd = nullptr; ///< Manejador de la ventana (HWND).
  unsigned int m_width; ///< Ancho de la ventana.
  unsigned int m_height; ///< Alto de la ventana.

private:
  HINSTANCE m_hInst = nullptr; ///< Identificador de la instancia de la aplicación.
  RECT m_rect; ///< Rectángulo que define la posición y el tamaño de la ventana.
  std::string m_windowName = "Turtle Engine"; ///< Nombre de la ventana.
};
