#pragma once
#include "Prerequisites.h"

// Declaración anticipada de clases.
class Device;
class DeviceContext;
class MeshComponent;

// Clase Buffer, que maneja buffers de diferentes tipos (Vertex, Index, Constant).
class Buffer {
public:

    // Constructor por defecto.
    Buffer() = default;

    // Destructor por defecto.
    ~Buffer() = default;

    // Inicializa los buffers de vértices e índices (Vertex e Index Buffers).
    // @param device El dispositivo gráfico donde se crea el buffer.
    HRESULT init(Device& device, MeshComponent& mesh, unsigned int bindFlag);

    // Inicializa los buffers constantes (Constant Buffers).
    HRESULT init(Device& device, unsigned int ByteWidth);

    // Actualiza la lógica del Constant Buffer.
    void update(DeviceContext& deviceContext,
                unsigned int DstSubresource,
                const D3D11_BOX* pDstBox,
                const void* pSrcData,
                unsigned int SrcRowPitch,
                unsigned int SrcDepthPitch);

    // Actualiza en el render los Vertex, Index y Constant Buffers.
    void render(DeviceContext& deviceContext, 
                unsigned int StartSlot, 
                unsigned int NumBuffers,
                bool setPixelShader = false,
                DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

    // Libera los recursos asociados al buffer.
    void destroy();

private:
    // Crea el buffer con las especificaciones dadas.
    HRESULT createBuffer(Device& device,
                         D3D11_BUFFER_DESC& desc,
                         D3D11_SUBRESOURCE_DATA* initData);

    // Puntero al objeto del buffer.
    ID3D11Buffer* m_buffer = nullptr;

    // Bandera de enlace que indica cómo se puede usar el buffer.
    unsigned int m_bindFlag = 0;

    // El tamaño del buffer, usado para cálculos de memoria.
    unsigned int m_stride = 0;

    // Desplazamiento del buffer.
    unsigned int m_offset = 0;
};
