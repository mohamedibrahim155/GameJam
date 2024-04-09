#pragma once
#include "../EmitterProperty.h"
class SizeOverLifetime : public EmitterProperty
{
public:


	bool isEnabled = true;
	glm::vec3 startScale = glm::vec3(1);
	glm::vec3 endScale = glm::vec3(1);
	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;
};

