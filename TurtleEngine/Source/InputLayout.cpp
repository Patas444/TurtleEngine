#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT 
InputLayout::init(Device& device, 
                  std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout, 
                  ID3DBlob* VertexShaderData) {

  // Validar que el vector Layout no esté vacío
  if (Layout.empty()) {
    ERROR("InputLayout", "init", "Layout vector is empty");
    return E_INVALIDARG;  // Retorna un código de error si el vector está vacío
  }

  // Validar que los datos del shader de vértices no sean nulos
  if (!VertexShaderData) {
    ERROR("InputLayout", "init", "VertexShaderData is nullptr");
    return E_POINTER;  // Retorna un código de error si los datos del shader son nulos
  }

  HRESULT hr = S_OK;

  // Crear el Input Layout utilizando el Device y los datos del shader de vértices
  hr = device.CreateInputLayout(Layout.data(),
    static_cast<unsigned int>(Layout.size()),  // Número de elementos en Layout
    VertexShaderData->GetBufferPointer(),      // Datos del shader
    VertexShaderData->GetBufferSize(),         // Tamaño de los datos del shader
    &m_inputLayout);                           // Apuntador al Input Layout creado

  if (FAILED(hr)) {
    ERROR("InputLayout", "init", "Failed to create InputLayout");
    return hr;  // Retorna el código de error si la creación del InputLayout falla
  }

  return S_OK;  // Retorna S_OK si la inicialización fue exitosa
}

void 
InputLayout::update() {
}

void 
InputLayout::render(DeviceContext& deviceContext) {
  // Validar que el contexto del dispositivo no sea nulo
  if (!deviceContext.m_deviceContext) {
    ERROR("InputLayout", "render", "DeviceContext is nullptr in InputLayout render method");
    return;  // Retorna si el DeviceContext no está correctamente inicializado
  }

  // Asignar el Input Layout al Input Assembler del contexto de dispositivo
  // Esto es necesario para que el dispositivo sepa cómo leer los datos de los vértices
  deviceContext.IASetInputLayout(m_inputLayout);
}

void 
InputLayout::destroy() {
  // Liberar el recurso del Input Layout de forma segura para evitar fugas de memoria
  SAFE_RELEASE(m_inputLayout);
}