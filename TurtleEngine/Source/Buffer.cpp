#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "MeshComponent.h"

/**
 * @brief Crea un búfer de Direct3D.
 * @param device Referencia al dispositivo utilizado para crear el búfer.
 * @param initData Datos iniciales opcionales para el búfer.
 */
HRESULT Buffer::createBuffer(Device& device, D3D11_BUFFER_DESC& desc, D3D11_SUBRESOURCE_DATA* initData) {
  if (!device.m_device) {
    ERROR("Buffer", "createBuffer", "Device es nullptr");
    return E_POINTER;
  }

  HRESULT hr = device.CreateBuffer(&desc, initData, &m_buffer);
  if (FAILED(hr)) {
    ERROR("Buffer", "createBuffer", "Fallo al crear el búfer");
    return hr;
  }

  return S_OK;
}

/**
 * @brief Inicializa el búfer con datos de una malla.
 * @param device Referencia al dispositivo.
 * @param bindFlag Especifica si el búfer es de vértices o índices.
 */
HRESULT Buffer::init(Device& device, MeshComponent& mesh, unsigned int bindFlag) {
  if (!device.m_device) {
    ERROR("Buffer", "init", "Device es nullptr");
    return E_POINTER;
  }

  if ((bindFlag & D3D11_BIND_VERTEX_BUFFER) && mesh.m_vertex.empty()) {
    ERROR("Buffer", "init", "El búfer de vértices está vacío");
    return E_INVALIDARG;
  }

  if ((bindFlag & D3D11_BIND_INDEX_BUFFER) && mesh.m_index.empty()) {
    ERROR("Buffer", "init", "El búfer de índices está vacío");
    return E_INVALIDARG;
  }

  D3D11_BUFFER_DESC desc = {};
  D3D11_SUBRESOURCE_DATA InitData = {};
  
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.CPUAccessFlags = 0;
  m_bindFlag = bindFlag;

  if (bindFlag & D3D11_BIND_VERTEX_BUFFER) {
    m_stride = sizeof(SimpleVertex);
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    InitData.pSysMem = mesh.m_vertex.data();
  }
  else if (bindFlag & D3D11_BIND_INDEX_BUFFER) {
    m_stride = sizeof(unsigned int);
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    InitData.pSysMem = mesh.m_index.data();
  }

  return createBuffer(device, desc, &InitData);
}

/**
 * @brief Inicializa el búfer como un búfer constante.
 * @param ByteWidth Tamaño del búfer en bytes.
 */
HRESULT Buffer::init(Device& device, unsigned int ByteWidth) {
  if (!device.m_device || ByteWidth == 0) {
    ERROR("Buffer", "init", "Parámetros inválidos");
    return E_INVALIDARG;
  }

  m_stride = ByteWidth;

  D3D11_BUFFER_DESC desc = {};
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.ByteWidth = ByteWidth;
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  m_bindFlag = desc.BindFlags;

  return createBuffer(device, desc, nullptr);
}

/**
 * @brief Actualiza los datos del búfer.
 * @param deviceContext Referencia al contexto del dispositivo.
 */
void Buffer::update(DeviceContext& deviceContext, unsigned int DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, unsigned int SrcRowPitch, unsigned int SrcDepthPitch) {
  if (!m_buffer) {
    ERROR("Buffer", "update", "Buffer es nullptr");
    return;
  }

  deviceContext.UpdateSubresource(m_buffer, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

/**
 * @brief Asigna el búfer al pipeline de renderizado.
 * @param deviceContext Referencia al contexto del dispositivo.
 */
void Buffer::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumBuffers, bool setPixelShader, DXGI_FORMAT format) {
  if (!m_buffer) {
    ERROR("Buffer", "render", "Buffer es nullptr");
    return;
  }

  switch (m_bindFlag) {
  case D3D11_BIND_VERTEX_BUFFER:
    deviceContext.IASetVertexBuffers(StartSlot, NumBuffers, &m_buffer, &m_stride, &m_offset);
    break;

  case D3D11_BIND_CONSTANT_BUFFER:
    deviceContext.VSSetConstantBuffers(StartSlot, NumBuffers, &m_buffer);
    if (setPixelShader) {
      deviceContext.PSSetConstantBuffers(StartSlot, NumBuffers, &m_buffer);
    }
    break;

  case D3D11_BIND_INDEX_BUFFER:
    deviceContext.IASetIndexBuffer(m_buffer, format, m_offset);
    break;

  default:
    ERROR("Buffer", "render", "BindFlag no soportado");
    break;
  }
}

// Libera la memoria del búfer.
void Buffer::destroy() {
  SAFE_RELEASE(m_buffer);
}
