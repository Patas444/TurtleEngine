#pragma once
#include "Prerequisites.h"

// Clase que representa un dispositivo Direct3D para la gesti�n de recursos gr�ficos.
class 
Device {
public:
	Device()  = default;
	~Device() = default;

	// Inicializa el dispositivo.
	void
	init();
	
	// Actualiza el estado del dispositivo.
	void 
	update();
	
	// Renderiza los elementos gr�ficos del dispositivo.
	void 
	render();
	
	// Libera los recursos del dispositivo.
	void 
	destroy();

	// Crea una vista de renderizado.
	HRESULT 
	CreateRenderTargetView(ID3D11Resource* pResource,
							const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
							ID3D11RenderTargetView** ppRTView);

	// Crea un shader de v�rtices.
	HRESULT 
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
				    const D3D11_SUBRESOURCE_DATA* pInitialData,
					ID3D11Texture2D** ppTexture2D);

	// Crea una vista de profundidad y est�ncil.
	HRESULT 
	CreateDepthStencilView(ID3D11Resource* pResource,
						   const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
						   ID3D11DepthStencilView** ppDepthStencilView);

	// Crea un dise�o de entrada para los shaders.
	HRESULT 
	CreateVertexShader(const void* pShaderBytecode,
						unsigned int BytecodeLength,
						ID3D11ClassLinkage* pClassLinkage,
						ID3D11VertexShader** ppVertexShader);

	// Crea un shader de p�xeles.
	HRESULT 
	CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
						unsigned int NumElements,
						const void *pShaderBytecodeWithInputSignature,
						unsigned int BytecodeLength,
						ID3D11InputLayout **ppInputLayout);

	// Crea un b�fer en la GPU.
	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
					    unsigned int BytecodeLength,
						ID3D11ClassLinkage* pClassLinkage,
						ID3D11PixelShader** ppPixelShader);

	// Crea un estado de muestreo.
	HRESULT 
	CreateBuffer(const D3D11_BUFFER_DESC *pDesc,
				 const D3D11_SUBRESOURCE_DATA *pInitialData,
				 ID3D11Buffer **ppBuffer);
	// Crea un estado de rasterizaci�n.
	HRESULT
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
						ID3D11SamplerState** ppSamplerState);
	
	// Crea un estado de mezcla.
	HRESULT
	CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, 
						   ID3D11RasterizerState** ppRasterizerState);

	HRESULT 
	CreateBlendState(const D3D11_BLEND_DESC *pBlendStateDesc,
					  ID3D11BlendState **ppBlendState);

// Puntero al dispositivo Direct3D.
public:
ID3D11Device* m_device = nullptr;
};