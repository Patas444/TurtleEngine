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
#include "ModelLoader.h"
#include "ECS\Actor.h"


// Clase base para la aplicación.
class BaseApp {
public:
    // Constructor por defecto.
    BaseApp() = default;

    // Destructor por defecto.
    ~BaseApp() = default;

    // Inicializa la aplicación.
    HRESULT init();
    
    // Actualiza el estado de la aplicación.
    void update();
    
    // Renderiza los elementos de la aplicación.
    void render();
    
    // Libera los recursos de la aplicación.
    void destroy();

    // Método para redimensionar la ventana.
    HRESULT resizeWindow(HWND hWnd, LPARAM lParam);

    // Mapea las acciones de entrada (del teclado en este caso) en función del tiempo.
    void
    inputActionMap(float deltaTime);

    // Actualiza la cámara.
    void upadteCamera();

    // Rota la cámara en función de la entrada del ratón.
    void rotateCamera(int mouseX, int mouseY);

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

public:
    Window													m_window;
    Device													m_device;
    DeviceContext										    m_deviceContext;
    SwapChain												m_swapchain;
    Texture													m_backBuffer;
    Texture													m_depthStencil;
    RenderTargetView										m_renderTargetView;
    DepthStencilView										m_depthStencilView;
    Viewport												m_viewport;
    ShaderProgram											m_shaderProgram;
    Buffer													m_neverChanges;
    Buffer													m_changeOnResize;
    Buffer													m_changeEveryFrame;
    GUI												        m_UI;

    XMMATRIX                                                m_View;
    XMMATRIX                                                m_Projection;

    Camera                                                  m_camera;
    
    // Actor
    ModelLoader												m_loader;
    EngineUtilities::TSharedPointer<Actor>                  AModel;
    std::vector<Texture>                                    m_Textures;
    Texture m_default;

    /*ModelLoader												m_loader2;
    EngineUtilities::TSharedPointer<Actor>                  AModel2;
    std::vector<Texture>                                    m_Textures2;*/

    CBNeverChanges cbNeverChanges;
    CBChangeOnResize cbChangesOnResize;

    std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;
    // Variables de control de entradas.
    bool key[256] = { false };   // Estado de las teclas.
    bool mouseLeftDown = false;  // Estado del clic izquierdo del ratón.
    int lastX=0;                   // Última posición en X del ratón.
    int lastY=0;                   // Última posición en Y del ratón.
    float camSpeed = 0.002f;     // Velocidad de la cámara.
};
