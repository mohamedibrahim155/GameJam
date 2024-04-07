#include "PlayerController.h"
#include "../GraphicsRender.h"
#include "States/IdleState.h"
#include "States/RunState.h"
#include "CameraController.h"
#include "../ApplicationRenderer.h"
PlayerController::PlayerController()
{
    LoadModel("Models/Character/X Bot.fbx");
    transform.SetScale(glm::vec3(0.01f));

    LoadAnimation("Models/Character/Idle.fbx", "Idle");
    LoadAnimation("Models/Character/Running.fbx", "Run");

    transform.SetRotation(glm::vec3(0, 180, 0));

    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().animationShader);


    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.dynamicFriction = 1;
    collider->SetPhysicsMaterial(playermaterial);

    AddState(ePlayerState::IDLE, new IdleState());
    AddState(ePlayerState::RUN, new RunState());

    frameSpeed = 30;

    cameraController = new CameraController(this);
}

PlayerController::PlayerController(ApplicationRenderer* application)
{
    this->application = application;

 

    LoadModel("Models/Character/X Bot.fbx");

    name = "PlayerController";
    tag = "Player";
    entityLayer = Layer::PLAYER;

    transform.SetScale(glm::vec3(0.01f));

    LoadAnimation("Models/Character/Idle.fbx", "Idle");
    LoadAnimation("Models/Character/Running.fbx", "Run");

    transform.SetRotation(glm::vec3(0, 180, 0));

    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().animationShader);


    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.dynamicFriction = 1;
    collider->SetPhysicsMaterial(playermaterial);

    AddState(ePlayerState::IDLE, new IdleState());
    AddState(ePlayerState::RUN, new RunState());

    frameSpeed = 30;

    cameraController = new CameraController(this);
}

PlayerController::~PlayerController()
{
    delete cameraController;

    for (std::pair<ePlayerState, BaseState*> pair : listOfPlayerStates)
    {
        if(pair.second)
        delete pair.second;
    }

    listOfPlayerStates.clear();

    if (currentState)
    {
        delete currentState;
    }

}



void PlayerController::Start()
{
    OnStateChange(ePlayerState::IDLE);

    application->ChangeCursorState(eCursorState::LOCKED);
}

void PlayerController::Update(float deltaTime)
{
    PhysicsSkinMeshRenderer::Update(deltaTime);

    GetCurrentState()->UpdateState(deltaTime);
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

    DrawPlayerControllerProperties();

    //GetCurrentState()->DrawStateProperties();


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

void PlayerController::OnStateChange(ePlayerState state)
{
    currentState->EndState();
    SetPlayerState(state);
    currentState->Start();
}

void PlayerController::AddState(ePlayerState playerState, BaseState* baseState)
{
    listOfPlayerStates[playerState] = baseState;
    baseState->playerController = this;

    currentState = baseState;
}

void PlayerController::RmoveState(ePlayerState playerstate)
{
    listOfPlayerStates.erase(playerstate);
}

void PlayerController::SetPlayerState(ePlayerState state)
{
    playerState = state;
    currentStateIndex = (int)playerState;
    currentState = listOfPlayerStates[state];
}

BaseState* PlayerController::GetCurrentState() const
{
    return currentState;
}

BaseState* PlayerController::GetState(ePlayerState state)
{
    return listOfPlayerStates[state];
}

void PlayerController::DrawPlayerControllerProperties()
{
    ImGui::NewLine();
    if (!ImGui::TreeNodeEx("PlayerController Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    DrawDragFloatImGui("MoveSpeed", playerMoveSpeed, 0.1f, 1.0f);

    for (std::pair<ePlayerState, BaseState*> pair : listOfPlayerStates)
    {
        pair.second->DrawStateProperties();
    }

    ImGui::TreePop();

}


