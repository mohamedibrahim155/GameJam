#pragma once
#include "EntityManager/Entity.h"
class FogSystem : public Entity
{
public:
	FogSystem();

	// Inherited via Entity
	void Start() override {};

	void Update(float deltaTime) override {};

	void OnDestroy() override {};

	void Render() override {};

	 void DrawProperties() override;
	 void SceneDraw() override;

	 float fogDensity = 0.4;
	 float fogStart = 8.0;
	 float fogEnd = 40;
	 glm::vec3 fogColor = { 0.09,0.09,0.09 };
	 bool fogActive = false;

};

