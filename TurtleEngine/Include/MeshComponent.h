#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"

// Clase que representa un componente de malla para su renderizado en Direct3D.
class MeshComponent {
public:
    // Constructor por defecto, inicializa el n�mero de v�rtices y de �ndices en 0.
    MeshComponent() : m_numVertex(0), m_numIndex(0) {};

    // Destructor por defecto.
    ~MeshComponent() = default;

public:
    // Nombre de la malla, utilizado para identificarla.
    std::string m_name;

    // Vector que contiene los v�rtices de la malla.
    std::vector<SimpleVertex> m_vertex;

    // Vector que contiene los �ndices de la malla, utilizados para formar las primitivas.
    std::vector<unsigned int> m_index;

    // N�mero de v�rtices en la malla.
    int m_numVertex;

    // N�mero de �ndices en la malla.
    int m_numIndex;
};
