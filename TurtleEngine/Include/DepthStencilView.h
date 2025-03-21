#pragma once
#include "PreRequisites.h"

// Clase que representa una vista de profundidad y est�ncil en Direct3D.
class Device;
class DeviceContext;
class Texture;

// Clase DepthStencilView, que maneja la vista de profundidad y est�ncil en Direct3D.
class DepthStencilView {
public:
    // Constructor por defecto.
    DepthStencilView() = default;

    // Destructor por defecto.
    ~DepthStencilView() = default;

    /*
    * Inicializa la vista de profundidad y est�ncil.
    * @param device El dispositivo gr�fico donde se crea la vista.
    */
    HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

    // Actualiza la vista de profundidad y est�ncil.
    void update();

    // Renderiza la vista de profundidad y est�ncil.
    // @param deviceContext El contexto del dispositivo que usar� esta vista.
    void render(DeviceContext& deviceContext);

    // Libera los recursos asociados a la vista de profundidad y est�ncil.
    void destroy();

public:
    // Puntero a la vista de profundidad y est�ncil de Direct3D.
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
