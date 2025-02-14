#pragma once
#include "Prerequisites.h"

// Clase que encapsula la creación y gestión de una ventana en Windows.
class 
Window {
public:
	Window() = default;
	~Window() = default;

   /**
    * @brief Inicializa la ventana.
    * @param hInstance Identificador de la instancia de la aplicación.
    * @param nCmdShow Comando de visualización de la ventana.
    * @param wndproc Función de procesamiento de mensajes de la ventana.
    * @return HRESULT Código de éxito o error en la inicialización.
    */
	HRESULT
	init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);
	
	// Actualiza el estado de la ventana.
	void 
	update();
	
	// Renderiza el contenido de la ventana.
	void 
	render();
	
	// Libera los recursos asociados a la ventana.
	void 
	destroy();

public:
	HWND m_hWnd = nullptr;
	unsigned int m_width;
	unsigned int m_height;
private:
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	std::string m_windowName = "Turtle Engine";
};