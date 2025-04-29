#pragma once
#include "Prerequisites.h"
#include "ECS/Transform.h"
#include "ECS/Actor.h"

class Window;
class Device;
class DeviceContext;

class
GUI {
public:
  GUI() = default;
  ~GUI() = default;

  void
  init(void* window,
       ID3D11Device* device,
       ID3D11DeviceContext* deviceContext);

  void
  update();

  void
  render();


  void
  destroy();

  void
  setupGUIStyle();

  void
  GUITab(const std::string& tabName);

  void
  transformWindow(Transform& transform);

  void
  vec3Control(const std::string& label,
              float* values,
              float resetValues = 0.0f,
              float columnWidth = 100.0f);

private:
    EngineUtilities::TSharedPointer<Actor> m_actors;
};