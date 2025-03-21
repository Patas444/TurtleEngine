#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"

// Clase que representa un componente de malla para su renderizado en Direct3D.
class MeshComponent {
public:
    // Constructor por defecto, inicializa el número de vértices y de índices en 0.
    MeshComponent() : m_numVertex(0), m_numIndex(0) {};

    // Destructor por defecto.
    ~MeshComponent() = default;

public:
    // Nombre de la malla, utilizado para identificarla.
    std::string m_name;

    // Vector que contiene los vértices de la malla.
    std::vector<SimpleVertex> m_vertex;

    // Vector que contiene los índices de la malla, utilizados para formar las primitivas.
    std::vector<unsigned int> m_index;

    // Número de vértices en la malla.
    int m_numVertex;

    // Número de índices en la malla.
    int m_numIndex;
};
