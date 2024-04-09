#include "SizeOverLifetime.h"

void SizeOverLifetime::DrawProperties()
{
	float width = 150;
	DrawBoolImGui("IsEnabled", this->isEnabled);

	if (isEnabled)
	{
		DrawTransformVector3ImGui("Start Scale", startScale, 0, width);
		DrawTransformVector3ImGui("End Scale", endScale, 0, width);
	}
}

void SizeOverLifetime::SceneDraw()
{
}
