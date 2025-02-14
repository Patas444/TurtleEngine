#include "BaseApp.h"

/**
 * Inicializa la aplicaci�n.
 * @return HRESULT con el estado de la inicializaci�n.
 */
HRESULT 
BaseApp::init() {
	return E_NOTIMPL;
}

// Actualiza el estado de la aplicaci�n en cada iteraci�n del bucle principal.
void 
BaseApp::update() {
}

// Renderiza el contenido de la aplicaci�n en la pantalla.
void 
BaseApp::render() {
}

// Libera los recursos utilizados por la aplicaci�n antes de cerrarla.
void 
BaseApp::destroy() {
}

/**
 * Ejecuta el bucle principal de la aplicaci�n.
 * @return C�digo de salida de la aplicaci�n.
 */
int 
BaseApp::run(HINSTANCE hInstance, 
						 HINSTANCE hPrevInstance, 
						 LPWSTR lpCmdLine, 
						 int nCmdShow, 
						 WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la aplicaci�n
	if (FAILED(init())) {
		destroy();
		return 0;
	}

	// Bucle principal de mensajes y ejecuci�n
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			update(); // Actualiza la l�gica de la aplicaci�n.
			render(); // Renderiza el contenido.
		}
	}

	destroy(); // Limpieza de recursos antes de salir.

	return (int)msg.wParam;
}