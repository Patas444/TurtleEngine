#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

/**
 * Un programa de shader se compone de shaders de vértices y píxeles. 
 * Esta clase maneja la creación, compilación, actualización y renderización de estos shaders.
 */
class 
ShaderProgram {
public:

  ShaderProgram() = default;
  ~ShaderProgram() = default;

  // Inicializa el programa de shader.
  HRESULT
  init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  // Actualiza el estado del programa de shader.
  void
  update();

  // Renderiza utilizando el programa de shader.
  void
  render(DeviceContext& DeviceContext);
   

  // Libera los recursos del programa de shader.
  void
  destroy();

  // Crea un layout de entrada para los shaders de vértices.
  HRESULT
  CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  // Crea un shader (vértice o píxel) a partir del tipo especificado.
  HRESULT
  CreateShader(Device& device, ShaderType type);

  // Compila un shader desde un archivo.
  HRESULT
  CompileShaderFromFile(char* szFileName,
                        LPCSTR szEntryPoint,
                        LPCSTR szShaderModel,
                        ID3DBlob** ppBlobOut);

public:
  ID3D11VertexShader* m_VertexShader = nullptr; ///< Puntero al shader de vértices.
  ID3D11PixelShader* m_PixelShader = nullptr;   ///< Puntero al shader de píxeles.
  InputLayout m_inputLayout;                    ///< Layout de entrada para los shaders.

private:
  std::string m_shaderFileName;  ///< Nombre del archivo de shaders.
  ID3DBlob* m_vertexShaderData = nullptr; ///< Datos del shader de vértices.
  ID3DBlob* m_pixelShaderData = nullptr;  ///< Datos del shader de píxeles.
};
