#pragma once
// Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
//#include <memory>
#include <thread>

// Librerias DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

// MACROS PARA MANEJO DE RECURSOS Y DEPURACIÓN.

// Libera un recurso COM de DirectX si no es nullptr y lo establece en nullptr.
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// Macro para registrar un mensaje de creación de recursos en la consola de depuración.
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

// Macro para registrar mensajes de error en la consola de depuración.
#define ERROR(classObj, method, errorMSG)                     \
{                                                             \
    try {                                                     \
        std::wostringstream os_;                              \
        os_ << L"ERROR : " << classObj << L"::" << method     \
            << L" : " << errorMSG << L"\n";                   \
        OutputDebugStringW(os_.str().c_str());                \
    } catch (...) {                                           \
        OutputDebugStringW(L"Failed to log error message.\n");\
    }                                                         \
}

// ESTRUCTURAS DE SOMBREADORES Y CONSTANTES.

// Representa un vértice con posición y coordenadas de textura.
struct 
SimpleVertex {
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

// Representa la matriz de vista utilizada en transformaciones de cámara.
struct 
CBNeverChanges {
  XMMATRIX mView;
};

// Representa la matriz de proyección, actualizada en cambios de tamaño de ventana.
struct 
CBChangeOnResize {
  XMMATRIX mProjection;
};

// Representa la matriz del mundo y el color de malla, que pueden cambiar cada fotograma.
struct 
CBChangesEveryFrame {
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};

// Define los tipos de extensión de imagen compatibles con el sistema.
enum ExtensionType {
  DDS = 0,
  PNG = 1,
  JPG = 2
};