#pragma once
#include "Prerequisites.h"
#include "Window.h"

// Clase base para la aplicación.
class 
BaseApp {
public:
	BaseApp() = default;
	~BaseApp()= default;

	// Inicializa la aplicación.
	HRESULT
	init();
	
	// Actualiza el estado de la aplicación.
	void 
	update();
	
	// Renderiza los elementos de la aplicación.
	void 
	render();
	
	// Libera los recursos de la aplicación.
	void 
	destroy();

	/*
	* Método principal de ejecución de la aplicación.
	* @return Código de salida del programa.	
	*/
	int 
	run(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPWSTR lpCmdLine, 
		int nCmdShow, 
		WNDPROC wndproc);

// Objeto que maneja la ventana de la aplicación.
private:
Window m_window;
};