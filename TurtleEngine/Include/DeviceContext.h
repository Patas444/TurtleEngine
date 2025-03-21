#pragma once
#include "Prerequisites.h"

// Clase que representa un contexto de dispositivo Direct3D, el cual se encarga de manejar las operaciones de rendering.
class DeviceContext {
public:
    // Constructor por defecto.
    DeviceContext() = default;

    // Destructor por defecto.
    ~DeviceContext() = default;

    // Inicializa el contexto del dispositivo.
    void init();

    // Actualiza el estado del contexto del dispositivo.
    void update();

    // Renderiza los elementos gr�ficos usando el contexto del dispositivo.
    void render();

    // Libera los recursos asociados con el contexto del dispositivo.
    void destroy();

    // Establece las vistas de renderizado y la vista de profundidad/est�ncil para el contexto.
    void OMSetRenderTargets(unsigned int NumViews,
                            ID3D11RenderTargetView* const* ppRenderTargetViews,
                            ID3D11DepthStencilView* pDepthStencilView);

    // Establece las vistas de viewport para el contexto.
    void RSSetViewports(unsigned int NumViewports,
                        const D3D11_VIEWPORT* pViewports);

    // Establece el dise�o de entrada para los shaders.
    void IASetInputLayout(ID3D11InputLayout* pInputLayout);

    // Establece los buffers de v�rtices para el pipeline de entrada.
    void IASetVertexBuffers(unsigned int StartSlot,
                            unsigned int NumBuffers,
                            ID3D11Buffer* const* ppVertexBuffers,
                            const unsigned int* pStrides,
                            const unsigned int* pOffsets);

    // Establece el buffer de �ndices para el pipeline de entrada.
    void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
                          DXGI_FORMAT Format,
                          unsigned int Offset);

    // Establece la topolog�a de primitiva para el pipeline de entrada.
    // @param Topology La topolog�a de primitivas a usar (ej. tri�ngulos, l�neas, etc.).
    void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

    // Actualiza los datos de un recurso (por ejemplo, un buffer).
    void UpdateSubresource(ID3D11Resource* pDstResource,
                           unsigned int DstSubresource,
                           const D3D11_BOX* pDstBox,
                           const void* pSrcData,
                           unsigned int SrcRowPitch,
                           unsigned int SrcDepthPitch);

    // Limpia la vista de renderizado con un color especificado.
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
                               const FLOAT ColorRGBA[4]);

    // Limpia la vista de profundidad y est�ncil.
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
                               unsigned int ClearFlags,
                               FLOAT Depth,
                               UINT8 Stencil);

    // Establece el shader de v�rtices a usar.
    void VSSetShader(ID3D11VertexShader* pVertexShader,
                     ID3D11ClassInstance* const* ppClassInstances,
                     unsigned int NumClassInstances);

    // Establece los buffers constantes para el shader de v�rtices.
    void VSSetConstantBuffers(unsigned int StartSlot,
                              unsigned int NumBuffers,
                              ID3D11Buffer* const* ppConstantBuffers);

    // Establece el shader de p�xeles a usar.
    void PSSetShader(ID3D11PixelShader* pPixelShader,
                     ID3D11ClassInstance* const* ppClassInstances,
                     unsigned int NumClassInstances);

    // Establece los buffers constantes para el shader de p�xeles.
    void PSSetConstantBuffers(unsigned int StartSlot,
                              unsigned int NumBuffers,
                              ID3D11Buffer* const* ppConstantBuffers);

    // Establece los recursos de shader (por ejemplo, texturas) para el shader de p�xeles.
    void PSSetShaderResources(unsigned int StartSlot,
                              unsigned int NumViews,
                              ID3D11ShaderResourceView* const* ppShaderResourceViews);

    // Establece los samplers para los shaders de p�xeles.
    void PSSetSamplers(unsigned int StartSlot,
                       unsigned int NumSamplers,
                       ID3D11SamplerState* const* ppSamplers);

    // Dibuja los elementos indexados.
    void DrawIndexed(unsigned int IndexCount,
                     unsigned int StartIndexLocation,
                     INT BaseVertexLocation);

public:
    // Puntero al contexto de dispositivo Direct3D.
    ID3D11DeviceContext* m_deviceContext = nullptr;

private:
};
