#include "IdleState.h"
#include "../PlayerController.h"
#include "../../InputManager/InputManager.h"
void IdleState::Start()
{
	playerController->PlayAnimation("Idle");
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
