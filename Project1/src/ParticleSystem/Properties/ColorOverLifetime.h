#pragma once
#include "../EmitterProperty.h"
class ColorOverLifetime : public EmitterProperty
{
public:

	bool isEnabled = false;

	
	// Inherited via EmitterProperty
	void DrawProperties() override;

	void SceneDraw() override;

};

