#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
SamplerState::init(Device& device) {
  // Verificar si el dispositivo es nulo
  if (!device.m_device) {
    ERROR("SamplerState", "init", "Device is nullptr in SamplerState init method");
    return E_POINTER;  // Retorna un error si el dispositivo es nulo
  }

  HRESULT hr = S_OK;

  // Definir y configurar la descripción del sampler
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));  // Inicializar la descripción a cero

  // Establecer parámetros del filtro de muestreo (bilineal para min, mag y mip)
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

  // Establecer los modos de dirección para cada coordenada (wrap en X, Y y Z)
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

  // Establecer la función de comparación (ninguna en este caso)
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

  // Establecer el rango de LOD (Level of Detail) permitido para la textura
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;  // Usar el valor máximo de flotante como LOD máximo

  // Intentar crear el estado de sampler usando la descripción configurada
  hr = device.CreateSamplerState(&sampDesc, &m_samplerState);
  if (FAILED(hr)) {
    ERROR("SamplerState", "init", "Failed to create Sampler State.");
    return hr;  // Retorna un error si la creación del Sampler State falla
  }

  return S_OK;  // Retorna S_OK si la inicialización fue exitosa
}

void
SamplerState::update() {
  // Este método está reservado para futuras actualizaciones de estado del sampler
  // Actualmente no realiza ninguna acción, pero puede ser extendido si es necesario.
}

void
SamplerState::render(DeviceContext& deviceContext,
                     unsigned int StartSlot,
                     unsigned int numSamplers) {
  // Validar que el DeviceContext no sea nulo
  if (!deviceContext.m_deviceContext) {
    ERROR("SamplerState", "render", "DeviceContext is nullptr in SamplerState render method");
    return;  // Retorna si el contexto del dispositivo no está inicializado correctamente
  }

  // Configurar el sampler en el pixel shader (PS)
  deviceContext.PSSetSamplers(StartSlot, numSamplers, &m_samplerState);
}

void
SamplerState::destroy() {
  // Liberar el recurso del sampler de manera segura para evitar fugas de memoria
  SAFE_RELEASE(m_samplerState);
}
