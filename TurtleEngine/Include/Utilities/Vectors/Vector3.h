#pragma once
#include "Utilities/Utilities/EngineMath.h"
namespace 
EngineUtilities {
  /**
 * @brief A 3D vector class.
 *
 * This class represents a vector in 3-dimensional space and provides
 * basic vector operations such as addition, subtraction, scalar multiplication,
 * and normalization.
 */
  class Vector3 {
  public:
    float x; /**< The x-coordinate of the vector. */
    float y; /**< The y-coordinate of the vector. */
    float z; /**< The z-coordinate of the vector. */

    /**
     * @brief Default constructor.
     *
     * Initializes the vector to (0, 0, 0).
     */
    Vector3() : x(0), y(0), z(0) {}

    /**
     * @brief Parameterized constructor.
     *
     * Initializes the vector to the given x, y, and z values.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param z The z-coordinate.
     */
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * @brief Adds another vector to this vector.
     *
     * @param other The vector to add.
     * @return The result of the addition.
     */
    Vector3 
    operator+(const Vector3& other) const {
      return Vector3(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Subtracts another vector from this vector.
     *
     * @param other The vector to subtract.
     * @return The result of the subtraction.
     */
    Vector3 
    operator-(const Vector3& other) const {
      return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Multiplies this vector by a scalar.
     *
     * @param scalar The scalar to multiply by.
     * @return The result of the multiplication.
     */
    Vector3 
    operator*(float scalar) const {
      return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Calculates the magnitude (length) of the vector.
     *
     * @return The magnitude of the vector.
     */
    float 
    magnitude() const {
      return EngineUtilities::sqrt(x * x + y * y + z * z);
    }

    /**
     * @brief Normalizes the vector.
     *
     * @return The normalized vector.
     */
    Vector3 
    normalize() const {
      float mag = magnitude();
      if (mag == 0) {
        return Vector3(0, 0, 0);
      }
      return Vector3(x / mag, y / mag, z / mag);
    }

    void
    zero() {
      Vector3(0, 0, 0);
    }
    
    void
    one() {
      Vector3(1,1,1);
    }

    // Método para obtener un puntero a los datos como un arreglo
    // @return: Puntero a los componentes del vector
    float* 
    data() { return &x; }

    const float* 
    data() const { return &x; }
  };
}