#include "SizeOverLifetime.h"
#include"../Utilities/Lerp.h"

SizeOverLifetime::SizeOverLifetime()
{
}

glm::vec3 SizeOverLifetime::ScaleOverLifetime()
{

	return Lerp(startScale, endScale, 1); //TODO find a way to lerp it with the lifetime
}

void SizeOverLifetime::DrawProperties()
{
	float width = 150;
	DrawBoolImGui("Enabled", isEnabled);

	if (isEnabled)
	{
		DrawTransformVector3ImGui("Start Scale", startScale,0, width);
		DrawTransformVector3ImGui("End Scale", endScale,0, width);

	}
	else
	{
		startScale = glm::vec3(1);
		endScale = glm::vec3(1);
	}
}

void SizeOverLifetime::SceneDraw()
{
}
