#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "MeshComponent.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "GUI.h"


// Clase base para la aplicaci�n.
class BaseApp {
public:
    // Constructor por defecto.
    BaseApp() = default;

    // Destructor por defecto.
    ~BaseApp() = default;

    // Inicializa la aplicaci�n.
    HRESULT init();
    
    // Actualiza el estado de la aplicaci�n.
    void update();
    
    // Renderiza los elementos de la aplicaci�n.
    void render();
    
    // Libera los recursos de la aplicaci�n.
    void destroy();

    // M�todo para redimensionar la ventana.
    HRESULT resizeWindow(HWND hWnd, LPARAM lParam);

    // Mapea las acciones de entrada (del teclado en este caso) en funci�n del tiempo.
    HRESULT inputActionMap(float deltaTime);

    // Actualiza la c�mara.
    void upadteCamera();

    // Rota la c�mara en funci�n de la entrada del rat�n.
    void rotateCamera(int mouseX, int mouseY);

    /*
    * M�todo principal de ejecuci�n de la aplicaci�n.
    * @return C�digo de salida del programa.
    */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

    // Funci�n de ventana (WndProc) para gestionar los mensajes de la ventana.
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    //--------------------------------------------------------------------------------------
    // Variables globales
    //--------------------------------------------------------------------------------------

    // Objeto para manejar la ventana de la aplicaci�n.
    Window                                  m_window;

    // Objeto para manejar el dispositivo gr�fico.
    Device                                  m_device;

    // Contexto del dispositivo, utilizado para operaciones de renderizado.
    DeviceContext                           m_deviceContext;

    // Objeto para manejar el swapchain (intercambio de buffers de pantalla).
    SwapChain                               m_swapchain;

    // Texturas utilizadas en la aplicaci�n (fondo y profundidad).
    Texture                                 m_backBuffer;
    Texture                                 m_depthStencil;

    // Vistas de los buffers (RenderTarget y DepthStencil).
    RenderTargetView                        m_renderTargetView;
    DepthStencilView                        m_depthStencilView;

    // Vista de la ventana y la resoluci�n de la pantalla.
    Viewport                                m_viewport;

    // Programa de shaders utilizado en el renderizado.
    ShaderProgram                           m_shaderProgram;

    // Recursos para shaders y buffers.
    Buffer                                  m_vertexBuffer;
    Buffer                                  m_indexBuffer;
    Buffer                                  m_neverChanges;
    Buffer                                  m_changeOnResize;
    Buffer                                  m_changesEveryFrame;
    
    // Textura y estado del sampler (muestras de texturas).
    Texture                                 m_textureRV;
    SamplerState                            m_samplerState;

    // Interfaz de usuario (UI).
    GUI                           m_UI;

    // Matrices para transformaciones de la escena.
    ID3D11SamplerState*                     g_pSamplerLinear = NULL; // Sampler utilizado para la textura.
    XMMATRIX                                m_World;        // Matriz de transformaci�n del mundo.
    XMMATRIX                                m_View;         // Matriz de visi�n/c�mara.
    XMMATRIX                                m_Projection;   // Matriz de proyecci�n.

    // Posici�n, rotaci�n y escala del objeto.
    XMFLOAT3                                position;
    XMFLOAT3                                rotation;
    XMFLOAT3                                scale;

    // Componente de malla (geometr�a).
    MeshComponent                           m_meshComponent;

    // C�mara de la escena.
    Camera                                  m_camera;

    // Buffers constantes para los shaders.
    CBChangesEveryFrame                     cb;               // Cambios cada fotograma.
    CBNeverChanges                          cbNeverChanges;        // Cambios que no cambian.
    CBChangeOnResize                        cbChangesOnResize;   // Cambios en el redimensionamiento de la ventana.

    // Variables de control de entradas.
    bool key[256] = { false };   // Estado de las teclas.
    bool mouseLeftDown = false;  // Estado del clic izquierdo del rat�n.
    int lastX;                   // �ltima posici�n en X del rat�n.
    int lastY;                   // �ltima posici�n en Y del rat�n.
    float camSpeed = 0.002f;     // Velocidad de la c�mara.
};
