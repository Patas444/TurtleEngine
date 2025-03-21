#pragma once
#include "Prerequisites.h"

// Clase que representa un dispositivo Direct3D para la gestión de recursos gráficos.
class Device {
public:
    // Constructor por defecto.
    Device() = default;

    // Destructor por defecto.
    ~Device() = default;

    // Inicializa el dispositivo.
    // Este método prepara el dispositivo gráfico para realizar operaciones.
    void init();

    // Actualiza el estado del dispositivo.
    // Usado para actualizar configuraciones o parámetros del dispositivo.
    void update();

    // Renderiza los elementos gráficos del dispositivo.
    // Este método es responsable de ejecutar el proceso de renderizado.
    void render();

    // Libera los recursos del dispositivo.
    // Este método limpia cualquier recurso que el dispositivo haya usado.
    void destroy();

    // Crea una vista de renderizado.
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
                                   const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
                                   ID3D11RenderTargetView** ppRTView);

    // Crea una textura 2D.
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                            const D3D11_SUBRESOURCE_DATA* pInitialData,
                            ID3D11Texture2D** ppTexture2D);

    // Crea una vista de profundidad y esténcil.
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
                                   const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                                   ID3D11DepthStencilView** ppDepthStencilView);

    // Crea un shader de vértices.
    HRESULT CreateVertexShader(const void* pShaderBytecode,
                               unsigned int BytecodeLength,
                               ID3D11ClassLinkage* pClassLinkage,
                               ID3D11VertexShader** ppVertexShader);

    // Crea un diseño de entrada para los shaders (Input Layout).
    HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                              unsigned int NumElements,
                              const void* pShaderBytecodeWithInputSignature,
                              unsigned int BytecodeLength,
                              ID3D11InputLayout** ppInputLayout);

    // Crea un Pixel Shader.
    HRESULT CreatePixelShader(const void* pShaderBytecode,
                              unsigned int BytecodeLength,
                              ID3D11ClassLinkage* pClassLinkage,
                              ID3D11PixelShader** ppPixelShader);

    // Crea un buffer de recursos (como un Vertex Buffer o Index Buffer).
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
                         const D3D11_SUBRESOURCE_DATA* pInitialData,
                         ID3D11Buffer** ppBuffer);

    // Crea un estado de rasterización (Rasterizer State).
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
                               ID3D11SamplerState** ppSamplerState);

    // Puntero al dispositivo Direct3D.
    ID3D11Device* m_device = nullptr;

private:
};
