#include "SceneFive.h"
#include "../../ApplicationRenderer.h"
#include "../../Player/PlayerController.h"
#include "../../PostProcessing bounds/CubeVolume.h"
SceneFive::SceneFive(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
	
}

void SceneFive::Start()
{
    std::string diffuseTexturePath = "Models/Graveyard/Fences/atlas-universal-albedo-a.png";
    Texture* diffuseTexture = new Texture(diffuseTexturePath);

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    PlayerController* player = new PlayerController(application);
    player->transform.SetPosition(glm::vec3(-75.91, 5.82, 105.85));

    PhysXObject* terrain = new PhysXObject();
    terrain->LoadModel("Models/Terrain/Terrain2.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(terrain, application->defaultShader);
    terrain->name = "Terrain";
    terrain->transform.SetPosition(glm::vec3(0, -2, 0));
    terrain->transform.SetRotation(glm::vec3(0, 0, 0));
    terrain->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    CubeVolume* cube = new CubeVolume();
    cube->transform.SetPosition(glm::vec3(0, -1, 5));
    cube->transform.SetScale(glm::vec3(0.5f));
    cube->Intialize(application->gameScenecamera);


    PhysXObject* gate = new PhysXObject();
    gate->LoadModel("Models/Graveyard/Fences/Gate.fbx");
    gate->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(gate, application->defaultShader);
    gate->name = "Gate";
    gate->transform.SetPosition(glm::vec3(-76.10, 4.00, 106.90));
    gate->transform.SetRotation(glm::vec3(0, 50, 0));
    gate->transform.SetScale(glm::vec3(0.015));
    gate->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


   
    PhysXObject* wall = new PhysXObject();
    wall->LoadModel("Models/Graveyard/Fences/WallBig.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(wall, application->defaultShader);
    wall->name = "Wall";
    wall->transform.SetPosition(glm::vec3(-82.10, 4.00, 107.50));
    wall->transform.SetRotation(glm::vec3(0, 1.50, 0));
    wall->transform.SetScale(glm::vec3(0.015));
    wall->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);
    
    //for (size_t i = 0; i < 2; i++)
    //{

    //    PhysXObject* wallCopy = new PhysXObject();
    //    wallCopy->LoadModel(*wall);
    //    GraphicsRender::GetInstance().AddModelAndShader(wallCopy, application->defaultShader);
    //    wallCopy->name = "Wall " + std::to_string(i) ;
    //    wallCopy->transform.SetPosition(glm::vec3(-84.10, 2.90, 107.50));
    //    //wall->transform.SetRotation(glm::vec3(0, 50, 0));
    //    wallCopy->transform.SetScale(glm::vec3(0.015));
    //    wallCopy->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    //}

    PhysXObject* wallCopy = new PhysXObject();
    wallCopy->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy, application->defaultShader);
    wallCopy->name = "Wall 1" ;
    wallCopy->transform.SetPosition(glm::vec3(-70.00, 4.00, 106.10));
    wallCopy->transform.SetRotation(glm::vec3(0, 6.20, 0));
    wallCopy->transform.SetScale(glm::vec3(0.015));
    wallCopy->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* corner = new PhysXObject();
    corner->LoadModel("Models/Graveyard/Fences/CornerBig.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(corner, application->defaultShader);
    corner->name = "Corner";
    corner->transform.SetPosition(glm::vec3(-86.40, 3.95, 106.80));
    corner->transform.SetRotation(glm::vec3(0, 280.90, 0));
    corner->transform.SetScale(glm::vec3(0.015, 0.015, -0.01));
    corner->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy2 = new PhysXObject();
    wallCopy2->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy2, application->defaultShader);
    wallCopy2->name = "Wall 2";
    wallCopy2->transform.SetPosition(glm::vec3(-88.50, 4.00, 101.20));
    wallCopy2->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy2->transform.SetScale(glm::vec3(0.015));
    wallCopy2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);


    PhysXObject* corner2 = new PhysXObject();
    corner2->LoadModel("Models/Graveyard/Fences/CornerSmall.fbx");
    corner2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(corner2, application->defaultShader);
    corner2->name = "Corner";
    corner2->transform.SetPosition(glm::vec3(-67.60, 2.95, 105.90));
    corner2->transform.SetRotation(glm::vec3(0, 363.10, 0));
    corner2->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy3 = new PhysXObject();
    wallCopy3->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy3, application->defaultShader);
    wallCopy3->name = "Wall 3";
    wallCopy3->transform.SetPosition(glm::vec3(-89.70, 4.00, 96.90));
    wallCopy3->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy3->transform.SetScale(glm::vec3(0.015));
    wallCopy3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy4 = new PhysXObject();
    wallCopy4->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy4, application->defaultShader);
    wallCopy4->name = "Wall 4";
    wallCopy4->transform.SetPosition(glm::vec3(-90.80, 4.00, 92.50));
    wallCopy4->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy4->transform.SetScale(glm::vec3(0.015));
    wallCopy4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy5 = new PhysXObject();
    wallCopy5->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy5, application->defaultShader);
    wallCopy5->name = "Wall 5";
    wallCopy5->transform.SetPosition(glm::vec3(-92.00, 4.00, 88.20));
    wallCopy5->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy5->transform.SetScale(glm::vec3(0.015));
    wallCopy5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy6 = new PhysXObject();
    wallCopy6->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy6, application->defaultShader);
    wallCopy6->name = "Wall 6";
    wallCopy6->transform.SetPosition(glm::vec3(-93.20, 4.10, 83.90));
    wallCopy6->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy6->transform.SetScale(glm::vec3(0.015));
    wallCopy6->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy7 = new PhysXObject();
    wallCopy7->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy7, application->defaultShader);
    wallCopy7->name = "Wall 7";
    wallCopy7->transform.SetPosition(glm::vec3(-94.40, 5.70, 79.80));
    wallCopy7->transform.SetRotation(glm::vec3(0, 107.40, 0));
    wallCopy7->transform.SetScale(glm::vec3(0.015));
    wallCopy7->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy8 = new PhysXObject();
    wallCopy8->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy8, application->defaultShader);
    wallCopy8->name = "Wall 8";
    wallCopy8->transform.SetPosition(glm::vec3(-95.70, 6.60, 75.70));
    wallCopy8->transform.SetRotation(glm::vec3(0, 107.40, 0));
    wallCopy8->transform.SetScale(glm::vec3(0.015));
    wallCopy8->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy10 = new PhysXObject();
    wallCopy10->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy10, application->defaultShader);
    wallCopy10->name = "Wall 10";
    wallCopy10->transform.SetPosition(glm::vec3(-66.20, 4.00, 102.30));
    wallCopy10->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy10->transform.SetScale(glm::vec3(0.015));
    wallCopy10->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy11 = new PhysXObject();
    wallCopy11->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy11, application->defaultShader);
    wallCopy11->name = "Wall 11";
    wallCopy11->transform.SetPosition(glm::vec3(-66.00, 4.00, 97.70));
    wallCopy11->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy11->transform.SetScale(glm::vec3(0.015));
    wallCopy11->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy12 = new PhysXObject();
    wallCopy12->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy12, application->defaultShader);
    wallCopy12->name = "Wall 12";
    wallCopy12->transform.SetPosition(glm::vec3(-65.80, 4.00, 93.10));
    wallCopy12->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy12->transform.SetScale(glm::vec3(0.015));
    wallCopy12->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Rocks = new PhysXObject();
    Rocks->LoadModel("Models/Graveyard/Fences/Rocks.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(Rocks, application->defaultShader);
    Rocks->name = "Rocks";
    Rocks->transform.SetPosition(glm::vec3(-70.00, 3.10, 88.80));
    Rocks->transform.SetRotation(glm::vec3(-30.70, -26.30, -7.70));
    Rocks->transform.SetScale(glm::vec3(0.007));
    Rocks->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Rocks2 = new PhysXObject();
    Rocks2->LoadModel("Models/Graveyard/Fences/RocksTwo.fbx");
    Rocks2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Rocks2, application->defaultShader);
    Rocks2->name = "Rocks";
    Rocks2->transform.SetPosition(glm::vec3(-84.00, 5.70, 53.90));
    Rocks2->transform.SetRotation(glm::vec3(-90.00, 0, 0));
    Rocks2->transform.SetScale(glm::vec3(1.50));
    Rocks2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* FenceBig = new PhysXObject();
    FenceBig->LoadModel("Models/Graveyard/Fences/FenceBig.fbx");
    FenceBig->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(FenceBig, application->defaultShader);
    FenceBig->name = "Fence Big";
    FenceBig->transform.SetPosition(glm::vec3(-53.80, 7.10, 84.10));
    FenceBig->transform.SetRotation(glm::vec3(-90.00, 0, 0));
    FenceBig->transform.SetScale(glm::vec3(1));
    FenceBig->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    //try to bring in the Cathedral
    PhysXObject* BigHouse = new PhysXObject();
    BigHouse->LoadModel("Models/Graveyard/Fences/BigHouse.fbx");
    BigHouse->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(BigHouse, application->defaultShader);
    BigHouse->name = "Big House";
    BigHouse->transform.SetPosition(glm::vec3(-52.70, 6.70, 72.50));
    BigHouse->transform.SetRotation(glm::vec3(0, -125.10, 0));
    BigHouse->transform.SetScale(glm::vec3(0.03,0.03,0.04));
    BigHouse->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

   




    
}

void SceneFive::Update()
{
}

void SceneFive::Render()
{
}
