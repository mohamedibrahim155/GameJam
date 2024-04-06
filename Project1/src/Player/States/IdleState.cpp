#include "IdleState.h"
#include "../PlayerController.h"
#include "../../InputManager/InputManager.h"
void IdleState::Start()
{
	playerController->PlayBlendAnimation("Idle",0.2f);
	playerController->SetVelocity(glm::vec3(0, playerController->GetVelocity().y, 0));
}

void IdleState::UpdateState(float deltaTime)
{
	//float horizontal = InputManager::GetInstance().GetHorizontalAxis();

	/*if (horizontal != 0)
	{
		OnStateChange(ePlayerState::RUN);
		return;
	}*/
}

void IdleState::EndState()
{

}

void IdleState::DrawStateProperties()
{
}
