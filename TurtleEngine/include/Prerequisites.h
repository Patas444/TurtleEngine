#pragma once

// Librerías estándar
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <xnamath.h>
#include <iostream>

// Librerías para manejo de memoria y hilos
#include <thread>

// Librerías de DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "Resource.h"

// Librerías de ImGUI para interfaces gráficas
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include "imgui_impl_win32.h"

// Third Parties
#include "Utilities\Memory\TSharedPointer.h"
#include "Utilities\Memory\TWeakPointer.h"
#include "Utilities\Memory\TStaticPtr.h"
#include "Utilities\Memory\TUniquePtr.h"

// Macro para liberar un recurso DirectX de forma segura
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// Macro para mostrar mensajes de creación de recursos
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

// Macro para mostrar errores con información detallada sobre el error
#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

// Estructuras de datos utilizadas en la aplicación

// Estructura simple para almacenar vértices (posición y coordenadas de textura)
struct SimpleVertex {
  XMFLOAT3 Pos; // Posición del vértice
  XMFLOAT2 Tex; // Coordenadas de textura
};

// Estructura para almacenar cambios constantes que no cambian
struct CBNeverChanges {
  XMMATRIX mView; // Matriz de vista
};

// Estructura para almacenar cambios cuando se cambia el tamaño de la ventana
struct CBChangeOnResize {
  XMMATRIX mProjection; // Matriz de proyección
};

// Estructura para almacenar los cambios en cada cuadro
struct CBChangesEveryFrame {
  XMMATRIX mWorld;     // Matriz de transformación mundial
  XMFLOAT4 vMeshColor; // Color del mesh
};

// Enumeración para tipos de extensión de archivo
enum ExtensionType {
  DDS = 0, 
  PNG = 1, 
  JPG = 2  
};

// Enumeración para tipos de shaders
enum ShaderType {
  VERTEX_SHADER = 0, // Shader de vértices
  PIXEL_SHADER = 1   // Shader de píxeles
};

enum
ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformación.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

// Estructura para representar una cámara
struct Camera {
  XMFLOAT3 position; // Posición de la cámara
  XMFLOAT3 target;   // Objetivo o punto hacia donde apunta la cámara

  XMFLOAT3 up;       // Vector hacia arriba de la cámara
  XMFLOAT3 forward;  // Dirección hacia adelante de la cámara
  XMFLOAT3 right;    // Dirección hacia la derecha de la cámara

  float yaw;         // Ángulo de rotación en el eje Y (giro)
  float pitch;       // Ángulo de rotación en el eje X (inclinación)

  // Constructor por defecto, establece valores iniciales para la cámara
  Camera() {
    position = XMFLOAT3(0.0f, 1.0f, -5.0f);
    target = XMFLOAT3(0.0f, 1.0f, 0.0f);
    up = XMFLOAT3(0.0f, 1.0f, 0.0f);
    forward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    right = XMFLOAT3(1.0f, 0.0f, 0.0f);
    yaw = 0.0f;
    pitch = 0.0f;
  }
};

struct LoadDataOBJ {
    std::string name; ///< Nombre del objeto.
    std::vector<SimpleVertex> vertex; ///< Vértices del objeto.
    std::vector<unsigned int> index; ///< Índices de los vértices.
    int numVertex = 0; ///< Número de vértices.
    int numIndex = 0; ///< Número de índices.
};
