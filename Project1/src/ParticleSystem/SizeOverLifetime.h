#pragma once
#include "EmitterProperty.h"

class SizeOverLifetime : public EmitterProperty
{
public:
	SizeOverLifetime();

	bool isEnabled;

	glm::vec3 startScale;
	glm::vec3 endScale;

	glm::vec3 ScaleOverLifetime();
	// Inherited via EmitterProperty
	void DrawProperties() override;

	void SceneDraw() override;

};

