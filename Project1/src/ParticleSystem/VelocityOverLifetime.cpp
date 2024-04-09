#include "VelocityOverLifetime.h"

VelocityOverLifetime::VelocityOverLifetime()
{
}

void VelocityOverLifetime::DrawProperties()
{
	DrawBoolImGui("Enabled", isEnabled);

	if (isEnabled)
	{
		DrawFloatImGui("Particle Speed", particleSpeed);

	}
	else
	{
		particleSpeed = 0;
	}
}

void VelocityOverLifetime::SceneDraw()
{
}
