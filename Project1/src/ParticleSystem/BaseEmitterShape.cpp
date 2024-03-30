#include "BaseEmitterShape.h"
#include "../ImGui/ImGuiUtils.h"
void BaseEmitterShape::DrawProperties()
{

	DrawTransformVector3ImGui("Position", position, 0, particleWidth);
	DrawTransformVector3ImGui("Rotation", rotation, 0, particleWidth);
	DrawTransformVector3ImGui("Scale", scale, 0, particleWidth);

	DrawBoolImGui("Randomize Direction", isRandomDir);
}
