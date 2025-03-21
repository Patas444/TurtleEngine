#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

// Clase que representa un diseño de entrada para los shaders en Direct3D.
class InputLayout {
public:
    // Constructor por defecto.
    InputLayout() = default;

    // Destructor por defecto.
    ~InputLayout() = default;

    /*
    * Inicializa el diseño de entrada para los shaders.
    * @param device El dispositivo Direct3D para crear el input layout.
    */
    HRESULT init(Device& device,
                 std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
                 ID3DBlob* VertexShaderData);

    // Actualiza el diseño de entrada (si es necesario).
    void update();

    // Renderiza los elementos del diseño de entrada en el contexto del dispositivo.
    // @param deviceContext El contexto de dispositivo para ejecutar el renderizado.
    void render(DeviceContext& deviceContext);

    // Libera los recursos asociados con el diseño de entrada.
    void destroy();

public:
    // Puntero al diseño de entrada de Direct3D.
    ID3D11InputLayout* m_inputLayout = nullptr;
};
