#include "Window.h"

/**
 * Inicializa la ventana de la aplicaci�n.
 * @return C�digo HRESULT indicando �xito o error.
 */
HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc) {
  // Almacena la instancia de la clase
  m_hInst = hInstance;

  // Registra la clase de ventana
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);  // Tama�o de la estructura WNDCLASSEX
  wcex.style = CS_HREDRAW | CS_VREDRAW;  // La ventana se redibuja si cambia su tama�o horizontal o vertical
  wcex.lpfnWndProc = wndproc;  // Puntero a la funci�n que manejar� los mensajes de la ventana
  wcex.cbClsExtra = 0;  // No se usan datos adicionales para la clase de ventana
  wcex.cbWndExtra = 0;  // No se usan datos adicionales para la ventana
  wcex.hInstance = m_hInst;  // Instancia de la aplicaci�n
  wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);  // Icono de la ventana
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);  // Cursor de la ventana
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Color de fondo de la ventana
  wcex.lpszMenuName = NULL;  // No se asigna men�
  wcex.lpszClassName = "TutorialWindowClass";  // Nombre de la clase de ventana
  wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);  // Icono peque�o

  // Registra la clase de ventana
  if (!RegisterClassEx(&wcex)) {
    MessageBox(nullptr, "RegisterClassEx failed!", "Error", MB_OK);
    ERROR("Window", "init", "CHECK FOR RegisterClassEx");
    return E_FAIL;  // Error al registrar la clase de ventana
  }

  // Crea la ventana
  RECT rc = { 0, 0, 1200, 720 };  // Tama�o inicial de la ventana
  m_rect = rc;

  // Ajusta el tama�o de la ventana para que sea correcta seg�n el estilo
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  
  // Crea la ventana usando la clase registrada
  m_hWnd = CreateWindow("TutorialWindowClass",  // Clase de ventana
                         m_windowName.c_str(),   // Nombre de la ventana
                         WS_OVERLAPPEDWINDOW,    // Estilo de la ventana (ventana est�ndar con borde)
                         CW_USEDEFAULT,          // Posici�n X por defecto
                         CW_USEDEFAULT,          // Posici�n Y por defecto
                         m_rect.right - m_rect.left, // Ancho de la ventana
                         m_rect.bottom - m_rect.top, // Alto de la ventana
                         NULL,                    // No se asigna ventana padre
                         NULL,                    // No se asigna men�
                         m_hInst,                 // Instancia de la aplicaci�n
                         NULL);                   // No se pasa par�metro adicional
  if (!m_hWnd) {
    MessageBox(nullptr, "CreateWindow failed!", "Error", MB_OK);
    ERROR("Window", "init", "CHECK FOR CreateWindow()");
    return E_FAIL;  // Error al crear la ventana
  }

  // Muestra la ventana y la actualiza
  ShowWindow(m_hWnd, nCmdShow);
  UpdateWindow(m_hWnd);

  // Ajusta las dimensiones del viewport (�rea cliente de la ventana)
  GetClientRect(m_hWnd, &m_rect);  // Obtiene las dimensiones del �rea cliente
  m_width = m_rect.right - m_rect.left;  // Ancho de la ventana
  m_height = m_rect.bottom - m_rect.top;  // Alto de la ventana

  return S_OK;  // Inicializaci�n exitosa
}
