#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ECS/Component.h"

// Clase que representa un componente de malla para su renderizado en Direct3D.
class 
MeshComponent : public Component {
public:
    // Constructor por defecto, inicializa el n�mero de v�rtices y de �ndices en 0.
	MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

    // Destructor por defecto.
    virtual
    ~MeshComponent() = default;

  /**
   * @brief Actualiza el actor.
   * @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n.
   * @param deviceContext Contexto del dispositivo para operaciones gr�ficas.
   */
  void
  update(float deltaTime) override {}

  /**
   * @brief Renderiza el actor.
   * @param deviceContext Contexto del dispositivo para operaciones gr�ficas.
   */
  void
  render(DeviceContext& deviceContext) override {}

public:
	std::string m_name;
	std::vector<SimpleVertex> m_vertex;
	std::vector<unsigned int> m_index;
	int m_numVertex;
	int m_numIndex;
};
