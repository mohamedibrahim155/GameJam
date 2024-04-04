#include "CameraController.h"
#include "PlayerController.h"
CameraController::CameraController(PlayerController* playerController)
{
	this->playerController = playerController;
	gameCamera = CameraManager::GetInstance().GetMainCamera();
}

void CameraController::Start()
{
}

void CameraController::Update(float deltaTime)
{

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
}

void CameraController::SceneDraw()
{
	Entity::SceneDraw();
}

Camera* CameraController::GetCamera() const
{
	return gameCamera;
}
