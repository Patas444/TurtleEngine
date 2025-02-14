#pragma once
#include "PreRequisites.h"

// Clase que representa una vista de profundidad y esténcil en Direct3D.
class Device;
class DeviceContext;
class Texture;

class
DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

	/*
	* Inicializa la vista de profundidad y esténcil.
	* @return Código HRESULT indicando éxito o error.	
	*/
	HRESULT
	init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

	// Actualiza la vista de profundidad y esténcil.
	void
	update();

	// Renderiza la vista de profundidad y esténcil.
	void
	render(DeviceContext& deviceContext);

	// Libera los recursos de la vista de profundidad y esténcil.
	void
	destroy();

// Puntero a la vista de profundidad y esténcil de Direct3D.
public:
ID3D11DepthStencilView* m_depthStencilView = nullptr;
};