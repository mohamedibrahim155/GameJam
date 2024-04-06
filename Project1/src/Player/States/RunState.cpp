#include "RunState.h"
#include "../PlayerController.h"
#include"../../Time.h"
#include"../CameraController.h"
#include "../../Math.h"
#include "../../PhysX/PhysXUtils.h"
using namespace MathUtils;

void RunState::Start()
{
	playerController->PlayBlendAnimation("Run",0.2f);

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
	glm::vec3 camForward = playerController->cameraController->GetCamera()->transform.GetForward();
	glm::vec3 camRight = playerController->cameraController->GetCamera()->transform.GetRight();



	glm::vec3 moveDirection = vertical * camForward + horizontal * camRight;

	float magnitude = glm::length(moveDirection);

	if (magnitude >= 0.1f)
	{
	

		float angle = glm::degrees(atan2(moveDirection.x, moveDirection.z));

		glm::vec3 desiredRotation = glm::vec3(playerController->transform.rotation.x, angle, playerController->transform.rotation.z);

		
		playerController->transform.SetRotation(desiredRotation);

		glm::vec3  moveVelocity = moveDirection * playerController->playerMoveSpeed;

		velocity = glm::vec3(moveVelocity.x, playerController->GetVelocity().y, moveVelocity.z);
		playerController->SetVelocity(velocity);
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
