#include "PursueEnemyState.h"
#include "../Enemy.h"
#include "../../Time.h"
void PursueEnemyState::StartState()
{
	
	enemy->PlayBlendAnimation("Run", 0.2f);
	playAttackAnimation = false;
}

void PursueEnemyState::UpdateState()
{
	if (enemy->CheckPlayerInside(enemy->InnerRadius))
	{
		HandleMovement();
	}
	else
	{
		OnChangeState(eEnemyState::PATROL);
		return;
	}
	
}

void PursueEnemyState::EndState()
{
	playAttackAnimation = false;
}

void PursueEnemyState::Render()
{
}

void PursueEnemyState::StateProperites()
{
}

void PursueEnemyState::HandleMovement()
{
	glm::vec3 point = glm::vec3(target->position.x, enemy->transform.position.y, target->position.z);
	
	glm::vec3 diff = point - enemy->transform.position;
	glm::vec3 direction = glm::normalize(diff);
	float distance = glm::distance(enemy->transform.position, point);

	if (distance >= 0.75f)
	{
		if (playAttackAnimation)
		{
			enemy->PlayBlendAnimation("Run", 0.2f);
			playAttackAnimation = false;
		}

		glm::quat rotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

		enemy->transform.SetQuatRotation(rotation);

		enemy->transform.position += direction * enemy->enemyRangeSpeed * (float)Time::GetInstance().deltaTime;
	}
	else
	{
		if (!playAttackAnimation)
		{
			enemy->PlayBlendAnimation("Attack", 0.2f);
			playAttackAnimation = true;
		}
	}
	
}
