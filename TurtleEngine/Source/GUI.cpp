#include "GUI.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "BaseApp.h"

void 
GUI::init(void* window, 
                    ID3D11Device* device, 
                    ID3D11DeviceContext* deviceContext) {
  IMGUI_CHECKVERSION(); // Check ImGUI version
  ImGui::CreateContext(); // Initialize the context
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Setup GUI Style
  setupGUIStyle();

  // / When viewports are enabled we tweak WindowRounding/WindoBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform and Renderer bindings
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

}

void 
GUI::update() {
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
GUI::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();

  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault(); // Update default platform for Windows
    //if (ImGui::DragFloat3("Posici�n", reinterpret_cast<float*>(&g_bApp.position), 0.1f)) {
  }
}

void 
GUI::destroy() {
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void 
GUI::setupGUIStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Bordes redondeados y suaves para un diseño más amigable y orgánico
  style.WindowBorderSize = 1.5f;
  style.FrameBorderSize = 1.0f;
  style.WindowRounding = 8.0f;
  style.FrameRounding = 6.0f;
  style.ScrollbarRounding = 8.0f;
  style.GrabRounding = 8.0f;

  // Colores más suaves con un toque alegre
  ImVec4 blue = ImVec4(0.18f, 0.47f, 0.72f, 1.00f);   // Azul claro para las ventanas
  ImVec4 blueHover = ImVec4(0.22f, 0.55f, 0.85f, 1.00f); // Azul más brillante al hacer hover
  ImVec4 white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);     // Blanco brillante para los textos y algunos bordes

  ImVec4* colors = style.Colors;

  // Fondo de la ventana, color celeste claro
  colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.29f, 0.42f, 1.00f);  // Azul de fondo más claro y suave

  // Títulos con azul suave
  colors[ImGuiCol_TitleBg] = blue;

  // Bordes blancos para los elementos interactivos
  colors[ImGuiCol_Border] = white;

  // Elementos interactivos con un color suave y brillante
  colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.34f, 0.56f, 1.00f);  // Fondo más oscuro para elementos interactivos

}


void 
GUI::GUITab(const std::string& tabName) {
  ImGui::Begin(tabName.c_str());
  ImGui::End();
}

void 
GUI::transformWindow(Transform& transform) {

  ImGui::Begin("Transform"); 

  EngineUtilities::Vector3 position = transform.getPosition();
  EngineUtilities::Vector3 rotation = transform.getRotation();
  EngineUtilities::Vector3 scale = transform.getScale();

  // Se editan los valores en ImGui
  if (ImGui::DragFloat3("Position", &position.x, 0.1f)) {
      transform.setPosition(position);
  }
  if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f)) {
      transform.setRotation(rotation);
  }
  if (ImGui::DragFloat3("Scale", &scale.x, 0.1f)) {
      transform.setScale(scale);
  }

  ImGui::End();
}

void
GUI::vec3Control(const std::string& label, 
                           float* values, 
                                float resetValues,
                                float columnWidth) {
  ImGuiIO& io = ImGui::GetIO();
  auto boldFont = io.Fonts->Fonts[0];

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

  float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("X", buttonSize)) values[0] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", buttonSize)) values[1] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PopStyleVar();
  ImGui::Columns(1);

  ImGui::PopID();
}