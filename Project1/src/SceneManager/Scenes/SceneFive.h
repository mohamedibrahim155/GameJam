#pragma once
#include "../BaseScene.h"
class SceneFive : public BaseScene
{
public:
	SceneFive(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

