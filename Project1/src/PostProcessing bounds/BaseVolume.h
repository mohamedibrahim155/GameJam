#pragma once
#include "../PhysX/PhysXObject.h"
#include "../CameraManager.h"
enum class eVolumeType 
{
	CUBE,
	SPHERE
};

struct PostProccsingData
{
	bool isChromaticEnabled = false;
	bool isPixelizationEnabled = false;

};

class BaseVolume : public PhysXObject
{
public:
    void Intialize(Camera* camera);

	virtual void DrawVolume()= 0;

	 void DrawProperties()override ;
	 void SceneDraw()override;
	 void Render()override;

	virtual void Start()  override {};
	virtual void Update(float deltaTime) override {};
	virtual void OnDestroy() override {};

	virtual void OnTriggerEnter(PhysXObject* otherObject) {};
	virtual void OnTriggerStay(PhysXObject* otherObject) {};
	virtual void OnTriggerExit(PhysXObject* otherObject) {};

	virtual void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo) {};
	virtual void OnCollisionStay(PhysXObject* otherObject) {};
	virtual void OnCollisionExit(PhysXObject* otherObject) {};
protected:

	eVolumeType volumeType = eVolumeType::CUBE;
	Camera* camera = nullptr;
	PostProcessing* postProcessing;

	void EnablePostProccesing(bool enable);

};

