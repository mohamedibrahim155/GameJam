#pragma once
#include "BaseState.h"
#include "../../InputManager/InputManager.h"
class RunState : public BaseState
{
public :


	// Inherited via BaseState
	void Start() override;
	void UpdateState(float deltaTime) override;
	void EndState() override;
	void DrawStateProperties() override;



private:

	/*float horizontal;
	float vertical;*/
	float moveSpeed = 2;
    float columnWidth = 150.0f;
    float turnSmoothVelocity;
    float turnSmoothTime = 1;
	float rotationSpeed = 5;
	glm::vec3 velocity;



	void HandleTranslation();
	bool HandleInput();

};

