#pragma once
#include "PreRequisites.h"

// Clase que representa un contexto de dispositivo Direct3D para la gesti�n de estados y recursos gr�ficos.
class 
DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() = default;

	// Inicializa el contexto del dispositivo.
	void
	init();
	
	// Actualiza el estado del contexto.
	void 
	update();
	
	// Renderiza los elementos gr�ficos asociados al contexto.
	void 
	render();
	
	// Libera los recursos del contexto.
	void 
	destroy();

	// Configura las vistas de la pantalla.
	void 
	RSSetViewports(unsigned int NumViewports,const D3D11_VIEWPORT *pViewports);

	// Configura los recursos de textura para el sombreador de p�xeles.
	void 
	PSSetShaderResources(unsigned int StartSlot,
						 unsigned int NumViews,
						 ID3D11ShaderResourceView* const* ppShaderResourceViews);

	// Establece el dise�o de entrada para la etapa de ensamblaje de entrada.
	void 
	IASetInputLayout(ID3D11InputLayout* pInputLayout);

	// Configura el sombreador de v�rtices.
	void
	VSSetShader(ID3D11VertexShader* pVertexShader, 
				ID3D11ClassInstance* const* ppClassInstances, 
				unsigned int NumClassInstances);

	// Configura el sombreador de p�xeles.
	void 
	PSSetShader(ID3D11PixelShader *pPixelShader,
                ID3D11ClassInstance *const *ppClassInstances,
                unsigned int NumClassInstances);

	// Actualiza una subrecurso en la GPU.
	void 
	UpdateSubresource(ID3D11Resource* pDstResource, 
                      unsigned int DstSubresource,
                      const D3D11_BOX* pDstBox,
                      const void* pSrcData,
                      unsigned int SrcRowPitch,
                      unsigned int SrcDepthPitch);

    // Establece los b�feres de v�rtices para la etapa de ensamblaje de entrada.
    void 
    IASetVertexBuffers(unsigned int StartSlot,
                       unsigned int NumBuffers,
                       ID3D11Buffer *const *ppVertexBuffers,
                       const unsigned int*pStrides,
                       const unsigned int*pOffsets);
	// Establece el b�fer de �ndices.
	void 
	IASetIndexBuffer(ID3D11Buffer *pIndexBuffer,
					 DXGI_FORMAT Format,
					 unsigned int Offset);

	// Configura los muestreadores para el sombreador de p�xeles.
	void
	PSSetSamplers(unsigned int StartSlot,
				  unsigned int NumSamplers,
				  ID3D11SamplerState* const* ppSamplers);
	
	// Establece el estado de rasterizaci�n.
	void 
	RSSetState(ID3D11RasterizerState* pRasterizerState);

	// Establece el estado de rasterizaci�n.
	void 
	OMSetBlendState(ID3D11BlendState* pBlendState,
					const float BlendFactor[4],
					unsigned int SampleMask);

	// Configura los render targets.
	void 
	OMSetRenderTargets(unsigned int NumViews, 
					   ID3D11RenderTargetView* const* ppRenderTargetViews, 
					   ID3D11DepthStencilView* pDepthStencilView);
	// Establece la topolog�a de ensamblaje de primitivas.
	void
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

	// Limpia la vista de renderizado con un color espec�fico.
	void
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, 
						  const float ColorRGBA[4]);

	// Limpia la vista de profundidad y est�ncil.
	void
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, 
						  unsigned int ClearFlags, 
						  float Depth, 
						  UINT8 Stencil);

	// Configura los b�feres constantes para el sombreador de v�rtices.
	void
	VSSetConstantBuffers(unsigned int StartSlot, 
						 unsigned int NumBuffers, 
						 ID3D11Buffer* const* ppConstantBuffers);

	// Configura los b�feres constantes para el sombreador de p�xeles.
	void
	PSSetConstantBuffers(unsigned int StartSlot, 
						 unsigned int NumBuffers, 
						 ID3D11Buffer* const* ppConstantBuffers);

	// Dibuja un conjunto de �ndices.
	void
	DrawIndexed(unsigned int IndexCount, 
				unsigned int StartIndexLocation, 
				int BaseVertexLocation);
private:

// Puntero al contexto del dispositivo Direct3D.
public:
ID3D11DeviceContext* m_deviceContext = nullptr;
};