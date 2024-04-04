#pragma once
#include "../CameraManager.h"

class PlayerController;

class CameraController :  public Entity
{
public:
	CameraController(PlayerController* playerController);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	void Render() override;
	 void DrawProperties() override;
	 void SceneDraw() override;

	Camera* GetCamera() const;
private:

	PlayerController* playerController = nullptr;
	Camera* gameCamera;
};

