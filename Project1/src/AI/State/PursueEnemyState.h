#pragma once
#include "BaseEnemyState.h"
class PursueEnemyState : public BaseEnemyState
{
public:
	// Inherited via BaseEnemyState
	void StartState() override;
	void UpdateState() override;
	void EndState() override;
	void Render() override;
	void StateProperites() override;

private:
	void HandleMovement();

	float rangedSpeed;
	bool playAttackAnimation = false;

};

