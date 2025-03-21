#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * El SamplerState define las características del proceso de muestreo de texturas, 
 * como el filtrado y la envoltura de la textura.
 */
class
SamplerState {
public:
  SamplerState() = default;
  ~SamplerState() = default;

  // Inicializa el estado del sampler.
  HRESULT
  init(Device& device);

  // Actualiza el estado del sampler.
  void
  update();

  // Renderiza utilizando el estado del sampler.
  void
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int numSamplers);

  // Libera los recursos asociados al estado del sampler.
  void
  destroy();

private:
  ID3D11SamplerState* m_samplerState = nullptr;
};
