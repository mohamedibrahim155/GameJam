#include "BaseEmitterShape.h"
#include "../ImGui/ImGuiUtils.h"
void BaseEmitterShape::DrawProperties()
{

	DrawTransformVector3ImGui("EmitPosition", position, 0, particleWidth);
	DrawTransformVector3ImGui("EmitRotation", rotation, 0, particleWidth);
	DrawTransformVector3ImGui("EmitScale", scale, 0, particleWidth);

	DrawBoolImGui("Randomize Direction", isRandomDir);
}
