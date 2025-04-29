#include "BaseApp.h"
#include "GUI.h"

// Variables globales
BaseApp app;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Llamar cada vez que la aplicion reciba un mensaje.
static LRESULT CALLBACK
WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		app.resizeWindow(hWnd, lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		app.key[wParam] = true;
		break;

	case WM_KEYUP:
		app.key[wParam] = false;
		break;

	case WM_RBUTTONDOWN:
		app.mouseLeftDown = true;
		break;

	case WM_RBUTTONUP:
		app.mouseLeftDown = false;
		break;

	case WM_MOUSEMOVE:
		if (app.mouseLeftDown) { 
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			app.rotateCamera(x, y);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Punto de entrada al programa. Inicializa todo y entra en un procesamiento de mensajes
// en bucle. El tiempo de inactividad se utiliza para renderizar la escena.
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}
