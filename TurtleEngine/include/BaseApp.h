#pragma once
#include "Prerequisites.h"
#include "Window.h"

// Clase base para la aplicaci�n.
class 
BaseApp {
public:
	BaseApp() = default;
	~BaseApp()= default;

	// Inicializa la aplicaci�n.
	HRESULT
	init();
	
	// Actualiza el estado de la aplicaci�n.
	void 
	update();
	
	// Renderiza los elementos de la aplicaci�n.
	void 
	render();
	
	// Libera los recursos de la aplicaci�n.
	void 
	destroy();

	/*
	* M�todo principal de ejecuci�n de la aplicaci�n.
	* @return C�digo de salida del programa.	
	*/
	int 
	run(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPWSTR lpCmdLine, 
		int nCmdShow, 
		WNDPROC wndproc);

// Objeto que maneja la ventana de la aplicaci�n.
private:
Window m_window;
};