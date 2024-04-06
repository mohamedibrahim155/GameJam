#pragma once
#include "iInputOberver.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>
class InputManager
{
public:

	InputManager();
	~InputManager();

	static InputManager& GetInstance();

	void AddObserver(iInputObserver* observer);
	void RemoveObserver(iInputObserver* observer);

	void OnKeyPressed(const int& key);
	void OnKeyReleased(const int& key);
	void OnkeyHold();
	void OnMouseButtonPressed(const int& button);
	void OnMouseButtonReleased(const int& button);
	void Update(float deltaTime);
	void OnMouseMove(float x, float y);
	void OnMouseMoveObservers(float x, float y);
	void SetMouseSmoothDelta(const glm::vec2& delta);
	void InputAxis();

	float GetMouseX();
	float GetMouseY();
	float GetMouseDeltaX();
	float GetMouseDeltaY();

	float GetHorizontalAxis();
	float GetVerticalAxis();

	float GetInputAxis(const std::string& axis);

	glm::vec2 mouseCurrentPosition{ 0 };
	glm::vec2 mouseLastPosition{ 0 };
	glm::vec2 mouseDelta{ 0 };
	glm::vec2 smoothedMouseDelta{ 0 };
private:

	class Pimpl;
	Pimpl* pimpl;

	std::vector<iInputObserver*> observersList;
	

	float mouseX = 0;
	float mouseY = 0;
	float horizontal = 0;
	float vertical = 0;

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;
};

