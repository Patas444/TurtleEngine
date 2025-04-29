#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // Librería para cargar imágenes PNG
#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
Texture::init(Device device,
        const std::string& textureName,
        ExtensionType extensionType) {
  // Verificar si el dispositivo de Direct3D es válido
  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr in texture loading method");
    return E_POINTER; // Devolver un error si el dispositivo es inválido
  }

  HRESULT hr = S_OK;

  // Dependiendo del tipo de extensión, cargamos diferentes formatos de textura
  switch (extensionType) {
  case DDS:
    // Si la extensión es DDS, cargamos la textura usando D3DX11
    hr = D3DX11CreateShaderResourceViewFromFile(
      device.m_device,
      textureName.c_str(),  // Ruta al archivo de la textura
      nullptr,              // Opciones adicionales de carga (nulas en este caso)
      nullptr,              // No necesitamos un dispositivo de contexto adicional
      &m_textureFromImg,    // La textura cargada se almacenará aquí
      nullptr               // Sin parámetros adicionales
    );

    if (FAILED(hr)) {
      ERROR("Texture", "init",
        ("Failed to load DDS texture. Verify filepath: " + textureName).c_str());
      return hr; // Si falla, retornamos el error
    }
    break;

  case PNG: {
    // Si la extensión es PNG, cargamos la textura usando stb_image
    int width, height, channels;
    unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &channels, 4); // Cargar con 4 canales (RGBA)
    if (!data) {
      ERROR("Texture", "init",
        ("Failed to load PNG texture: " + std::string(stbi_failure_reason())).c_str());
      return E_FAIL;  // Si falla, devolvemos un error
    }

    // Crear la descripción de la textura
    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;  // Sin mipmaps
    textureDesc.ArraySize = 1;  // Solo una textura
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // Formato de color RGBA
    textureDesc.SampleDesc.Count = 1;  // Sin MSAA
    textureDesc.Usage = D3D11_USAGE_DEFAULT;  // Uso por defecto
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE; // La textura se usará como recurso de shader



    ///////////
    // Inicializar los datos de la textura
    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    initData.SysMemPitch = width * 4;  // Un byte por canal

    ////////

    // Crear la textura
    hr = device.CreateTexture2D(&textureDesc, &initData, &m_texture);
    stbi_image_free(data); // Liberar los datos de imagen una vez que la textura ha sido creada

    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create texture from PNG data");
      return hr;
    }

    // Crear la vista del recurso de la textura
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;  // Vista de 2D
    srvDesc.Texture2D.MipLevels = 1;  // Un solo nivel de mipmap

    // Crear la vista del recurso del shader
    hr = device.m_device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureFromImg);
    SAFE_RELEASE(m_texture); // Liberar la textura intermedia, ya que solo necesitamos la vista

    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create shader resource view for PNG texture");
      return hr;
    }
    break;
  }

  default:
    ERROR("Texture", "init", "Unsupported extension type");
    return E_INVALIDARG;  // Si la extensión no es válida, retornamos un error
  }

  return hr;  // Retornamos el resultado de la operación
}

HRESULT
Texture::init(Device device,
              unsigned int width,
              unsigned int height,
              DXGI_FORMAT Format,
              unsigned int BindFlags,
              unsigned int sampleCount,
              unsigned int qualityLevels) {
  // Verificar si el dispositivo de Direct3D es válido
  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr in texture initialization method");
    return E_POINTER;
  }

  // Verificar si las dimensiones de la textura son válidas
  if (width == 0 || height == 0) {
    ERROR("Texture", "init", "Width and height must be greater than 0");
    return E_INVALIDARG;  // Retornar error si las dimensiones no son válidas
  }

  HRESULT hr = S_OK;

  // Configurar la descripción de la textura
  D3D11_TEXTURE2D_DESC desc = {};
  desc.Width = width;
  desc.Height = height;
  desc.MipLevels = 1;  // Sin mipmaps
  desc.ArraySize = 1;  // Solo una textura
  desc.Format = Format;  // El formato de la textura es proporcionado
  desc.SampleDesc.Count = sampleCount;  // Configuración de muestras (MSAA)
  desc.SampleDesc.Quality = qualityLevels;  // Calidad de las muestras
  desc.Usage = D3D11_USAGE_DEFAULT;  // Uso por defecto
  desc.BindFlags = BindFlags;  // Especificar los flags de vinculación (por ejemplo, como recurso de shader)

  // Crear la textura
  hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
  if (FAILED(hr)) {
    ERROR("Texture", "init", "Failed to create texture with the specified parameters");
    return hr;  // Si falla, retornamos el error
  }

  return hr;  // Retornamos el resultado de la operación
}

void 
Texture::update() {
  // Este método no realiza ninguna acción en este momento.
  // Podría ser utilizado para actualizar la textura en el futuro si fuera necesario.
}

void 
Texture::render(DeviceContext& deviceContext, 
                unsigned int StartSlot, 
                unsigned int NumViews) {
  if (m_textureFromImg) {
    // Si la textura está cargada, establecerla en el contexto de la unidad de textura del píxel shader
    ID3D11ShaderResourceView* nullSRV[] = { nullptr };
    deviceContext.PSSetShaderResources(StartSlot, NumViews, nullSRV);  // Limpiar la unidad de textura
    deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);  // Establecer la textura
  }
  else {
    ERROR("Texture", "render", "Texture resource is not initialized");
  }
}

void 
Texture::destroy() {
  // Liberar los recursos de la textura
    if (m_texture != nullptr) {
        SAFE_RELEASE(m_texture);
    }
    else if (m_textureFromImg != nullptr) {
        SAFE_RELEASE(m_textureFromImg);
    }
}