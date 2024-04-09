#include "RigidBody.h"
#include "PhysXEngine.h"
#include "PhysXUtils.h"
#include "../ImGui/ImGuiUtils.h"
RigidBody::RigidBody()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

RigidBody::~RigidBody()
{
	
}

PxRigidDynamic* RigidBody::AsDynamicRigidBody()
{
	return (PxRigidDynamic*)rigidActor;
}

PxRigidStatic* RigidBody::AsStaticRigidBody()
{
	return (PxRigidStatic*)rigidActor;

}

PxRigidActor* RigidBody::GetPxRigidBody()
{
	return physicsObject->rigidActor;
}

void RigidBody::SetRigidBodyType(RigidBodyType type)
{
	rigidBodyType = type;
}

void RigidBody::SetDrag(float drag)
{
	
}

void RigidBody::SetMass(float _mass)
{
	mass = _mass;
	if (rigidActor == nullptr) return;

	if (rigidBodyType == RigidBodyType::DYNAMIC)
	((PxRigidDynamic*)rigidActor)->setMass(mass);
}

void RigidBody::SetKinematic(bool isKinematic)
{
	this->isKinematic = isKinematic;

}

void RigidBody::SetGravity(bool useGravity)
{
	this->useGravity = useGravity;
}

void RigidBody::SetVelocity(const glm::vec3& velocity)
{
	AsDynamicRigidBody()->setLinearVelocity(GLMToPxVec3(velocity));
}

void RigidBody::DrawRigidProperties()
{
	ImGui::NewLine();

	if (!ImGui::TreeNodeEx("RigidBody Properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	int currentType = (int)rigidBodyType;

	ImGui::Text(("Rigidbody Type :" + type[currentType]).c_str());

	if (rigidBodyType ==RigidBodyType::DYNAMIC)
	{
		if (DrawBoolImGui("useGravity", useGravity,200))
		{
			SetGravity(useGravity);
			UpdateGravity(useGravity);
		}
		if (DrawBoolImGui("isKinematic", isKinematic,200))
		{
			SetKinematic(isKinematic);
			UpdateKinematic(isKinematic);
		}

		if (DrawDragFloatImGui("Mass", mass))
		{
			SetMass(mass);
		}

		if (ImGui::TreeNode("Constraints")) 
		{
			if (ImGui::TreeNode("Freeze positions")) 
			{
				if (DrawBoolImGui("X-Pos", freezePosition.x) ||
					DrawBoolImGui("Y-Pos", freezePosition.y) ||
					DrawBoolImGui("Z-Pos", freezePosition.z)) 
				{
					SetPositionFreezeContraints(freezePosition);
				}
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Freeze rotations")) 
			{
				if (DrawBoolImGui("X-Rot", freezeRotation.x) ||
					DrawBoolImGui("Y-Rot", freezeRotation.y) ||
					DrawBoolImGui("Z-Rot", freezeRotation.z))
				{
					SetRotationFreezeContraints(freezeRotation);
				}
				ImGui::TreePop();
			}

			ImGui::TreePop(); 
		}



	}

	ImGui::TreePop();
}

void RigidBody::SetPositionFreezeContraints(Contraints& position)
{
	if (rigidActor == nullptr) return;

	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, position.x);
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, position.y);
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, position.z);
	}
}

void RigidBody::SetRotationFreezeContraints(Contraints& rotation)
{
	if (rigidActor == nullptr) return;

	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, rotation.x);
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, rotation.y);
		dynamicActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, rotation.z);
	}
}

void RigidBody::UpdateGravity(bool gravity)
{
	if (rigidActor == nullptr) return;

	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !(gravity));

		if (useGravity)
		{
			dynamicActor->wakeUp();
		}
	}
}

void RigidBody::UpdateKinematic(bool isKinematic)
{
	if (rigidActor == nullptr) return;

	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
		if (!this->isKinematic)
		{
			dynamicActor->wakeUp();
		}
	}
}




void RigidBody::InitializeRigidBody(PhysXObject* object)
{
	physicsObject = object;
	modelTransform = &object->transform;
	collider = object->collider;

	/*PxTransform transform(GLMToPxVec3(modelTransform->position),
		       GLMToPxQuat(modelTransform->quaternionRotation));*/

	PxTransform transform(GLMToPxVec3(collider->GetPosition()),
		GLMToPxQuat(collider->GetRotation()));

	switch (rigidBodyType)
	{
	case RigidBody::RigidBodyType::DYNAMIC:
		rigidActor = physics->createRigidDynamic(transform);
		break;
	case RigidBody::RigidBodyType::STATIC:

		rigidActor = physics->createRigidStatic(transform);
		break;
	//case RigidBody::RigidBodyType::KINEMATIC:
	//	//rigidActor = physics->createRigidDynamic(transform);
		
	}

	if (rigidActor)
	{
		rigidActor->userData = object;

		rigidActor->attachShape(*collider->GetShape());

		rigidActor->setGlobalPose(transform);

		object->rigidActor = rigidActor;

		SetPositionFreezeContraints(freezePosition);
		SetRotationFreezeContraints(freezeRotation);

		PhysXEngine::GetInstance().GetPhysicsScene()->addActor(*rigidActor);


		switch (rigidBodyType)
		{
		case RigidBody::RigidBodyType::DYNAMIC:
			UpdateGravity(useGravity);
			UpdateKinematic(isKinematic);
			break;
		}
		object->collider->TriggerState();


	}
	

	isRigidBodyInitilized = true;

}

