#pragma once
#include "BaseState.h"
#include "../../InputManager/InputManager.h"
class RunState : public BaseState, public iInputObserver
{
public :


	// Inherited via BaseState
	void Start() override;
	void UpdateState(float deltaTime) override;
	void EndState() override;
	void DrawStateProperties() override;

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;
	void OnMouseButtonPressed(const int& mouseButton) override;
	void OnMouseButtonReleased(const int& mouseButton) override;

private:

	/*float horizontal;
	float vertical;*/
	float moveSpeed = 2;
    float columnWidth = 150.0f;
    float turnSmoothVelocity;
    float turnSmoothTime = 1;
	glm::vec3 velocity;


	void HandleTranslation();






	// Inherited via iInputObserver
	void OnMouseMouseMove(float& moveX, float& moveY) override;

};

