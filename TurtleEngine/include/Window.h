#pragma once
#include "Prerequisites.h"

// Clase que encapsula la creaci�n y gesti�n de una ventana en Windows.
class 
Window {
public:
	Window() = default;
	~Window() = default;

   /**
    * @brief Inicializa la ventana.
    * @param hInstance Identificador de la instancia de la aplicaci�n.
    * @param nCmdShow Comando de visualizaci�n de la ventana.
    * @param wndproc Funci�n de procesamiento de mensajes de la ventana.
    * @return HRESULT C�digo de �xito o error en la inicializaci�n.
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