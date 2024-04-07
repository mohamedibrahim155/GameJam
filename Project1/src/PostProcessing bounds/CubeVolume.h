#pragma once
#include "BaseVolume.h"
class CubeVolume : public BaseVolume
{
public:
	CubeVolume();

	void SetExtends(const glm::vec3& extends);
	void DrawVolume() override;

	 void OnTriggerEnter(PhysXObject* otherObject) override;
	 void OnTriggerExit(PhysXObject* otherObject)  override;
private:
	glm::vec3 extends;
};

