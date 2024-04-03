#include "PlayerController.h"
#include "../GraphicsRender.h"


PlayerController::PlayerController()
{
    LoadModel("Models/Character/X Bot.fbx");
    transform.SetScale(glm::vec3(0.01f));

    LoadAnimation("Models/Character/Rumba Dancing.fbx", "Dance1");
    LoadAnimation("Models/Character/Punching Bag.fbx", "Punching");
    LoadAnimation("Models/Character/Mma Kick.fbx", "Kick");
    LoadAnimation("Models/Character/Snake Hip Hop Dance.fbx", "Dance2");
    LoadAnimation("Models/Character/Waving.fbx", "Wave");

    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().animationShader);

    InputManager::GetInstance().AddObserver(this);

    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.dynamicFriction = 1;
    collider->SetPhysicsMaterial(playermaterial);
}

PlayerController::~PlayerController()
{
}



void PlayerController::Start()
{
}

void PlayerController::Update(float deltaTime)
{
}

void PlayerController::Render()
{
    PhysicsSkinMeshRenderer::Render();
}

void PlayerController::OnDestroy()
{
}

void PlayerController::DrawProperties()
{
	PhysicsSkinMeshRenderer::DrawProperties();
}

void PlayerController::SceneDraw()
{
	PhysicsSkinMeshRenderer::SceneDraw();

}
void PlayerController::OnTriggerEnter(PhysXObject* otherObject)
{
}

void PlayerController::OnTriggerStay(PhysXObject* otherObject)
{
}

void PlayerController::OnTriggerExit(PhysXObject* otherObject)
{
}

void PlayerController::OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo)
{
}

void PlayerController::OnCollisionStay(PhysXObject* otherObject)
{
}

void PlayerController::OnCollisionExit(PhysXObject* otherObject)
{
}

void PlayerController::OnKeyPressed(const int& key)
{
  
}

void PlayerController::OnKeyReleased(const int& key)
{
    if (key == GLFW_KEY_W)
    {
        SetVelocity(glm::vec3(0, 0, 0));
    }
}

void PlayerController::OnKeyHold(const int& key)
{
    if (key == GLFW_KEY_W)
    {
        SetVelocity(glm::vec3(0, 0, 1));
    }
}

void PlayerController::OnMouseButtonPressed(const int& mouseButton)
{
}

void PlayerController::OnMouseButtonReleased(const int& mouseButton)
{
}
