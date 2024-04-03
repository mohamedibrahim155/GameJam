#pragma once
#include "../PhysX/PhysicsSkinMeshRenderer.h"
#include "../InputManager/InputManager.h"
class PlayerController : public PhysicsSkinMeshRenderer, public iInputObserver
{
public:
	PlayerController();
	~PlayerController();

	 void DrawProperties() override;
	 void SceneDraw() override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render() override;
	 void OnDestroy() override;

	 void OnTriggerEnter(PhysXObject* otherObject) override;
	 void OnTriggerStay(PhysXObject* otherObject) override;
	 void OnTriggerExit(PhysXObject* otherObject) override;

	 void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo) override;
	 void OnCollisionStay(PhysXObject* otherObject) override;
	 void OnCollisionExit(PhysXObject* otherObject) override;

private:


	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;
	void OnMouseButtonPressed(const int& mouseButton) override;
	void OnMouseButtonReleased(const int& mouseButton) override;

};

