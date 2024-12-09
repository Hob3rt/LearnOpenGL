#include "Ui.h"

void Ui::show_camera_info(Camera& camera)
{
	
	float width = 250.0;
	float height = 150.0;
	ImGui::SetNextWindowSize(ImVec2(width, height), 2);
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - width, 0.0), ImGuiCond_Once);
	ImGui::Begin("Camera info");
	ImGui::InputFloat3("Position", &camera.Position.x);
	ImGui::InputFloat3("Front", &camera.Front.x);
	ImGui::InputFloat3("Up", &camera.Up.x);
	ImGui::InputFloat3("Right", &camera.Right.x);
	ImGui::End();

}

void Ui::show_window_info()
{
	ImGui::SetNextWindowPos(ImVec2(0.0, 0.0), ImGuiCond_Once);
	ImGui::Begin("Basic info");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}
