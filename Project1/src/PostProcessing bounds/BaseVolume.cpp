#include "BaseVolume.h"



void BaseVolume::Intialize(Camera* camera)
{
	this->camera = camera;

	switch (volumeType)
	{
	case eVolumeType::CUBE:
		PhysXObject::Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);
		break;
	case eVolumeType::SPHERE:
		PhysXObject::Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::SPHERE);
		break;
	}

	collider->SetTriggerState(true);
}

void BaseVolume::DrawProperties()
{
	PhysXObject::DrawProperties();
}

void BaseVolume::SceneDraw()
{
	PhysXObject::SceneDraw();
}

void BaseVolume::Render()
{
	PhysXObject::Render();
}

void BaseVolume::EnablePostProccesing(bool enable)
{
	camera->isPostprocessing = enable;
}
