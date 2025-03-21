#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class Texture
 * @brief Clase encargada de gestionar las texturas en Direct3D 11.
 *
 * La clase `Texture` permite manejar texturas en Direct3D 11, tanto para cargar texturas 
 * desde archivos como para crear texturas vacías o de datos en memoria. 
 * También permite configurar la textura para que pueda ser utilizada en shaders.
 */
class 
Texture {
public:
  Texture() = default;  ///< Constructor por defecto.
  ~Texture() = default; ///< Destructor.

  // Inicializa la textura a partir de un archivo de imagen.
  HRESULT
  init(Device device,
       const std::string& textureName,
       ExtensionType extensionType);

  // Inicializa la textura con un tamaño y formato específico.
  HRESULT
  init(Device device,
       unsigned int width,
       unsigned int height,
       DXGI_FORMAT Format,
       unsigned int BindFlags,
       unsigned int sampleCount = 1,
       unsigned int qualityLevels = 0);

  // Actualiza el estado de la textura.
  void
  update();

  // Renderiza la textura en el contexto del dispositivo.
  void
  render(DeviceContext& deviceContet, 
         unsigned int StartSlot, 
         unsigned int NumViews);

  // Libera los recursos asociados a la textura.
  void 
  destroy();

public:
  ID3D11Texture2D* m_texture = nullptr; ///< Puntero a la textura en Direct3D.
  ID3D11ShaderResourceView* m_textureFromImg = nullptr; ///< Puntero a la vista de recurso de la textura (para usarla en shaders).
};
