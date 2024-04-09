#pragma once
#include "EmitterProperty.h"
class VelocityOverLifetime : public EmitterProperty
{
public:
	VelocityOverLifetime();

	bool isEnabled = false;
	float particleSpeed = 0;
	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;
};

