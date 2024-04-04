#pragma once
#include "../PhysX/PhysicsSkinMeshRenderer.h"
#include "../InputManager/InputManager.h"
#include "States/BaseState.h"
#include <unordered_map>
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


	 void OnStateChange(ePlayerState state);
	 void AddState(ePlayerState playerstate, BaseState* baseState);
	 void RmoveState(ePlayerState playerstate);
	 void SetPlayerState(ePlayerState state);

	 BaseState* GetCurrentState() const;
	 BaseState* GetState(ePlayerState state);

	 float playerMoveSpeed = 2.5f;
private:


	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;
	void OnMouseButtonPressed(const int& mouseButton) override;
	void OnMouseButtonReleased(const int& mouseButton) override;

	void DrawPlayerControllerProperties();

	int currentStateIndex = 0;
	ePlayerState playerState = ePlayerState::IDLE;
	BaseState* currentState;
	std::unordered_map<ePlayerState, BaseState*> listOfPlayerStates;

};

