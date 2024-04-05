#include "CameraController.h"
#include "PlayerController.h"
#include "../InputManager/InputManager.h"
#include "../Math.h"
#include "../Time.h"
using namespace MathUtils;

CameraController::CameraController(PlayerController* playerController)
{
	this->playerController = playerController;
	gameCamera = CameraManager::GetInstance().GetMainCamera();

	name = "Camera Controller";

	InitializeEntity(this);

	gameCamera->MouseSensitivity = 0.5f;

	InputManager::GetInstance().AddObserver(this);

	cameraOffset.y = 1.5f;
}

void CameraController::Start()
{
	intialCameraPosition = GetCamera()->transform.position;
	intialCameraRotation = GetCamera()->transform.rotation;
}

void CameraController::Update(float deltaTime)
{
#pragma region Old Code



	///*pitch += InputManager::GetInstance().GetMouseDeltaY();
	//pitch = glm::clamp(pitch, minVerticalAngle, maxVerticalAngle);*/

	////yaw += InputManager::GetInstance().GetMouseDeltaX();
	//yaw = glm::clamp(yaw, minYAngle, maxYAngle);


	//glm::vec3 targetRotation = glm::vec3(pitch, yaw, 0);
	//glm::vec3 currentCamPos = GetCamera()->transform.position;


	//offesetPos =  playerController->transform.position + cameraOffset;

	// offesetNormalized = glm::normalize(currentCamPos - offesetPos);


	// if (glm::length(offesetNormalized) > 0)
	// {
	//	 glm::quat lookAt = glm::quatLookAt(-offesetNormalized, glm::vec3(0, 1, 0));
	//	 //GetCamera()->transform.SetQuatRotation(lookAt);
	// }

	// 
	// 

	//GetCamera()->transform.position = offesetPos + playerController->transform.GetForward() * distance;

#pragma endregion


	 mouseX = InputManager::GetInstance().GetMouseDeltaX() * mouseSensitivity;
	 mouseY = InputManager::GetInstance().GetMouseDeltaY() * mouseSensitivity;

	yaw += mouseX ;
	yaw = glm::clamp(yaw, -360.0f, 360.0f);
	pitch -= mouseY;
	//pitch = glm::clamp(pitch, -minVerticalAngle, minVerticalAngle);

	glm::vec3 playerPosition = playerController->transform.position +  cameraOffset;

	glm::vec3 targetPosition = playerPosition + (playerController->transform.GetForward() /*+ cameraOffset*/ * distance);

	//targetPosition.y += cameraOffset.y;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glm::vec3 cameraPosition = playerPosition + (direction) * distance;


	glm::vec3 currentPosition = GetCamera()->transform.position;

	glm::vec3 newPosition =Math::LerpVec3(currentPosition, cameraPosition, deltaTime * moveSpeed);

	GetCamera()->transform.SetPosition(newPosition);

	glm::vec3 lookAtDirection = glm::normalize(playerPosition - newPosition);
	glm::quat lookAtRotation = glm::quatLookAt(lookAtDirection, glm::vec3(0, 1, 0));

	GetCamera()->transform.SetQuatRotation(glm::slerp(GetCamera()->transform.quaternionRotation, lookAtRotation, deltaTime * moveSpeed));

	mouseX = 0;
	mouseY = 0;
	//yaw = 0;
	//pitch = 0;
}

void CameraController::OnDestroy()
{
}

void CameraController::Render()
{
}

void CameraController::DrawProperties()
{
	Entity::DrawProperties();

	DrawCameraControlProperties();
}

void CameraController::SceneDraw()
{
	Entity::SceneDraw();
}

Camera* CameraController::GetCamera() const
{
	return gameCamera;
}

void CameraController::DrawCameraControlProperties()
{
	if (!ImGui::TreeNodeEx("Camera Controller", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	DrawDragFloatImGui("rotationX", pitch);
	DrawDragFloatImGui("rotationY", yaw);
	DrawDragFloatImGui("distance", distance);
	DrawDragFloatImGui("maxVerticalAngle", maxVerticalAngle);
	DrawDragFloatImGui("maxVerticalAngle", maxVerticalAngle);
	
	DrawTransformVector3ImGui("cameraPos", GetCamera()->transform.position,intialCameraPosition.x, columnWidth);
	DrawTransformVector3ImGui("cameraRot", GetCamera()->transform.rotation, intialCameraRotation.x, columnWidth);
	DrawTransformVector3ImGui("CameraOffset", cameraOffset, 0, columnWidth);
	//DrawTransformVector3ImGui("Direction", direction, 0, columnWidth);
	DrawTransformVector3ImGui("OffsetNormal", offesetNormalized, 0, columnWidth);
	DrawDragFloatImGui("Pitch", pitch);
	DrawDragFloatImGui("yaw", yaw);

	ImGui::TreePop();
}

void CameraController::OnKeyPressed(const int& key)
{
}

void CameraController::OnKeyReleased(const int& key)
{
}

void CameraController::OnKeyHold(const int& key)
{
}

void CameraController::OnMouseButtonPressed(const int& mouseButton)
{
}

void CameraController::OnMouseButtonReleased(const int& mouseButton)
{
}

void CameraController::OnMouseMouseMove(float& moveX, float& moveY)
{
	
	/*pitch += InputManager::GetInstance().GetMouseDeltaY();
	pitch = glm::clamp(pitch, minVerticalAngle, maxVerticalAngle);*/

	//yaw += InputManager::GetInstance().GetMouseDeltaX();
	//yaw = glm::clamp(yaw, minYAngle, maxYAngle);


		//yaw += InputManager::GetInstance().GetMouseDeltaX();
	//direction = glm::vec3(0);
	

	//glm::vec3 dir;
	////GetCamera()->transform.rotation.y = -yaw *  mouseSensitivity;
	//dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//dir.y = sin(glm::radians(pitch));
	//dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//direction = dir;
	//GetCamera()->transform.SetForward(glm::normalize(dir));
	//GetCamera()->transform.SetRotation(GetCamera()->transform.rotation);

}