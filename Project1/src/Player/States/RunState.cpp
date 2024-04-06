#include "RunState.h"
#include "../PlayerController.h"
#include"../../Time.h"
#include"../CameraController.h"
#include "../../Math.h"
#include "../../PhysX/PhysXUtils.h"
using namespace MathUtils;

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
#pragma region Old



	/*glm::vec3 forward = playerController->transform.GetForward();
	glm::vec3 right = playerController->transform.GetRight();
	glm::vec3 cameraForward = playerController->cameraController->transform.GetForward();

	glm::vec3 getCurrentPosition = playerController->GetVelocity();

	float horizontal = InputManager::GetInstance().GetHorizontalAxis() ;
	float vertical = InputManager::GetInstance().GetVerticalAxis();

	glm::vec3 moveDirection = vertical * -cameraForward + horizontal * -right;


	if (glm::length(moveDirection) > 0)
	{
		float angle = glm::acos(glm::dot(forward, cameraForward));


		playerController->transform.SetRotation(cameraForward);
	}

	glm::vec3  moveVelocity = moveDirection  * playerController->playerMoveSpeed;

	 velocity =  glm::vec3(moveVelocity.x, getCurrentPosition.y, moveVelocity.z);

	playerController->SetVelocity(velocity);*/

#pragma endregion

	float horizontal = InputManager::GetInstance().GetHorizontalAxis();
	float vertical = InputManager::GetInstance().GetVerticalAxis();

	glm::vec3 forward = playerController->transform.GetForward();
	glm::vec3 right = playerController->transform.GetRight();

	// Calculate the movement direction based on input
	glm::vec3 direction = glm::vec3(horizontal, 0, -vertical);

	glm::vec3 moveDirection = vertical * -forward + horizontal * -right;
	// Calculate the magnitude of the direction vector
	float magnitude = glm::length(direction);

	if (magnitude >= 0.1f)
	{
	
		float cameraYRot = playerController->cameraController->GetCamera()->transform.rotation.y;

		glm::vec3 currentPlayerRot = glm::vec3(playerController->transform.rotation.x, cameraYRot - 180.0f , playerController->transform.rotation.z);

		
		playerController->transform.SetRotation(currentPlayerRot);

		glm::vec3  moveVelocity = moveDirection * playerController->playerMoveSpeed;

		velocity = glm::vec3(moveVelocity.x, playerController->GetVelocity().y, moveVelocity.z);
		playerController->SetVelocity(moveVelocity);
	}


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
