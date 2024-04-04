#include "BaseState.h"
#include "../PlayerController.h"

void BaseState::OnStateChange( ePlayerState state)
{
	if (playerController != nullptr)
		playerController->OnStateChange(state);
}
