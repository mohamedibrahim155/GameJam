#include "RunState.h"
#include "../PlayerController.h"
#include"../../Time.h"
void RunState::Start()
{
	playerController->PlayAnimation("Run");

}

void RunState::UpdateState(float deltaTime)
{

	HandleTranslation();
}

void RunState::EndState()
{
}

void RunState::OnKeyPressed(const int& key)
{
}

void RunState::OnKeyReleased(const int& key)
{
}

void RunState::OnKeyHold(const int& key)
{
}

void RunState::OnMouseButtonPressed(const int& mouseButton)
{
}

void RunState::OnMouseButtonReleased(const int& mouseButton)
{
}

void RunState::HandleTranslation()
{
	glm::vec3 forward = playerController->transform.GetForward();
	glm::vec3 right = playerController->transform.GetRight();

	glm::vec3 getCurrentPosition = playerController->GetVelocity();

	float horizontal = InputManager::GetInstance().GetHorizontalAxis() ;
	float vertical = InputManager::GetInstance().GetVerticalAxis();

	glm::vec3 moveDirection = vertical * -forward + horizontal * -right;


	if (moveDirection != glm::vec3(0));
	{

	}

	glm::vec3  moveVelocity = moveDirection * playerController->playerMoveSpeed;

	 velocity =  glm::vec3(moveVelocity.x, getCurrentPosition.y, moveVelocity.z);

	playerController->SetVelocity(velocity);
}

void RunState::OnMouseMouseMove(float& moveX, float& moveY)
{
}

void RunState::DrawStateProperties()
{
	if (!ImGui::TreeNodeEx("RunState velocity ", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}


	DrawTransformVector3ImGui("Velocity", velocity, 0, columnWidth);


	ImGui::TreePop();
}
