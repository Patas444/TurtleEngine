#include "BaseApp.h"

/**
 * Inicializa la aplicación.
 * @return HRESULT con el estado de la inicialización.
 */
HRESULT 
BaseApp::init() {
	return E_NOTIMPL;
}

// Actualiza el estado de la aplicación en cada iteración del bucle principal.
void 
BaseApp::update() {
}

// Renderiza el contenido de la aplicación en la pantalla.
void 
BaseApp::render() {
}

// Libera los recursos utilizados por la aplicación antes de cerrarla.
void 
BaseApp::destroy() {
}

/**
 * Ejecuta el bucle principal de la aplicación.
 * @return Código de salida de la aplicación.
 */
int 
BaseApp::run(HINSTANCE hInstance, 
						 HINSTANCE hPrevInstance, 
						 LPWSTR lpCmdLine, 
						 int nCmdShow, 
						 WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la aplicación
	if (FAILED(init())) {
		destroy();
		return 0;
	}

	// Bucle principal de mensajes y ejecución
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			update(); // Actualiza la lógica de la aplicación.
			render(); // Renderiza el contenido.
		}
	}

	destroy(); // Limpieza de recursos antes de salir.

	return (int)msg.wParam;
}