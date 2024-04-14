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
    terrain->occulsionState = eOcculsionState::NO_OCCULSION;
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
    FenceBig->transform.SetPosition(glm::vec3(-65.16, 7.12, 83.13));
    FenceBig->transform.SetRotation(glm::vec3(-90.00, 0, 0));
    FenceBig->transform.SetScale(glm::vec3(1, 1, 1.1));
    FenceBig->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    //try to bring in the Cathedral
    PhysXObject* BigHouse = new PhysXObject();
    BigHouse->LoadModel("Models/Graveyard/Fences/BigHouse.fbx");
    BigHouse->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(BigHouse, application->defaultShader);
    BigHouse->name = "Big House";
    BigHouse->transform.SetPosition(glm::vec3(-47.18, 7.35, 80.54));
    BigHouse->transform.SetRotation(glm::vec3(0, -125.10, 0));
    BigHouse->transform.SetScale(glm::vec3(0.02,0.014,0.02));
    BigHouse->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

   

    PhysXObject* wallCopy13 = new PhysXObject();
    wallCopy13->LoadModel("Models/Graveyard/Fences/Wall.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy13, application->defaultShader);
    wallCopy13->name = "Wall 13";
    wallCopy13->transform.SetPosition(glm::vec3(-37.94, 6.40, 86.14));
    wallCopy13->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy13->transform.SetScale(glm::vec3(0.015));
    wallCopy13->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);


    PhysXObject* wallCopy14 = new PhysXObject();
    wallCopy14->LoadModel(*wallCopy13);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy14, application->defaultShader);
    wallCopy14->name = "Wall 14";
    wallCopy14->transform.SetPosition(glm::vec3(-34.92, 5.38, 86.14));
    wallCopy14->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy14->transform.SetScale(glm::vec3(0.015, 0.015,0.015));
    wallCopy14->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy15 = new PhysXObject();
    wallCopy15->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy15, application->defaultShader);
    wallCopy15->name = "Wall 15";
    wallCopy15->transform.SetPosition(glm::vec3(-30.03, 5.52, 86.14));
    wallCopy15->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy15->transform.SetScale(glm::vec3(0.015, 0.015,0.015));
    wallCopy15->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);


    PhysXObject* wallCopy16 = new PhysXObject();
    wallCopy16->LoadModel(*wallCopy13);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy16, application->defaultShader);
    wallCopy16->name = "Wall 16";
    wallCopy16->transform.SetPosition(glm::vec3(-27.69, 4.46, 86.14));
    wallCopy16->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy16->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy16->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* corner3 = new PhysXObject();
    corner3->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner3, application->defaultShader);
    corner3->name = "Corner 3";
    corner3->transform.SetPosition(glm::vec3(-24.97, 4.27, 86.15));
    corner3->transform.SetRotation(glm::vec3(0, 0, 0));
    corner3->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* corner4 = new PhysXObject();
    corner4->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner4, application->defaultShader);
    corner4->name = "Corner 4";
    corner4->transform.SetPosition(glm::vec3(-23.55, 3.94, 84.94));
    corner4->transform.SetRotation(glm::vec3(0, 80.10, 0));
    corner4->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    corner4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* corner5 = new PhysXObject();
    corner5->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner5, application->defaultShader);
    corner5->name = "Corner 5";
    corner5->transform.SetPosition(glm::vec3(-21.77, 3.57, 83.75));
    corner5->transform.SetRotation(glm::vec3(0, 10.10, 0));
    corner5->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);
    

    PhysXObject* corner6 = new PhysXObject();
    corner6->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner6, application->defaultShader);
    corner6->name = "Corner 6";
    corner6->transform.SetPosition(glm::vec3(-16.07, 2.84, 81.92));
    corner6->transform.SetRotation(glm::vec3(0, 0, 0));
    corner6->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner6->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy17 = new PhysXObject();
    wallCopy17->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy17, application->defaultShader);
    wallCopy17->name = "Wall 17";
    wallCopy17->transform.SetPosition(glm::vec3(-18.62, 4.23, 81.94));
    wallCopy17->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy17->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy17->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy18 = new PhysXObject();
    wallCopy18->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy18, application->defaultShader);
    wallCopy18->name = "Wall 18";
    wallCopy18->transform.SetPosition(glm::vec3(-53.53, 7.74, 48.31));
    wallCopy18->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy18->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy18->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy19 = new PhysXObject();
    wallCopy19->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy19, application->defaultShader);
    wallCopy19->name = "Wall 19";
    wallCopy19->transform.SetPosition(glm::vec3(-49.18, 6.54, 48.31));
    wallCopy19->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy19->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy19->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy20 = new PhysXObject();
    wallCopy20->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy20, application->defaultShader);
    wallCopy20->name = "Wall 20";
    wallCopy20->transform.SetPosition(glm::vec3(-44.68, 6.23, 48.31));
    wallCopy20->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy20->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy20->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy21 = new PhysXObject();
    wallCopy21->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy21, application->defaultShader);
    wallCopy21->name = "Wall 21";
    wallCopy21->transform.SetPosition(glm::vec3(-40.19, 6.22, 48.31));
    wallCopy21->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy21->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy21->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy22 = new PhysXObject();
    wallCopy22->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy22, application->defaultShader);
    wallCopy22->name = "Wall 22";
    wallCopy22->transform.SetPosition(glm::vec3(-35.64, 6.23, 48.31));
    wallCopy22->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy22->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy22->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy23 = new PhysXObject();
    wallCopy23->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy23, application->defaultShader);
    wallCopy23->name = "Wall 23";
    wallCopy23->transform.SetPosition(glm::vec3(-31.11, 6.19, 48.31));
    wallCopy23->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy23->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy23->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Tree = new PhysXObject();
    Tree->LoadModel("Models/Graveyard/TreeTwo.fbx");
    Tree->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Tree, application->defaultShader);
    Tree->name = "Tree";
    Tree->transform.SetPosition(glm::vec3(-68.67, 3.16, 99.81));
    Tree->transform.SetRotation(glm::vec3(0, -26.20, 0));
    Tree->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree2 = new PhysXObject();
    Tree2->LoadModel(*Tree);
    GraphicsRender::GetInstance().AddModelAndShader(Tree2, application->defaultShader);
    Tree2->name = "Tree2";
    Tree2->transform.SetPosition(glm::vec3(-42.05, 7.28, 85.52));
    Tree2->transform.SetRotation(glm::vec3(0, 31.00, 0));
    Tree2->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree3 = new PhysXObject();
    Tree3->LoadModel(*Tree);
    GraphicsRender::GetInstance().AddModelAndShader(Tree3, application->defaultShader);
    Tree3->name = "Tree3";
    Tree3->transform.SetPosition(glm::vec3(-92.69, 4.98, 71.95));
    Tree3->transform.SetRotation(glm::vec3(7.40, 40.10, 0));
    Tree3->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree4 = new PhysXObject();
    Tree4->LoadModel(*Tree);
    GraphicsRender::GetInstance().AddModelAndShader(Tree4, application->defaultShader);
    Tree4->name = "Tree4";
    Tree4->transform.SetPosition(glm::vec3(-61.58, 8.83, 50.88));
    Tree4->transform.SetRotation(glm::vec3(0, 40.10, 0));
    Tree4->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* TreeOne = new PhysXObject();
    TreeOne->LoadModel("Models/Graveyard/TreeOne.fbx");
    TreeOne->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(TreeOne, application->defaultShader);
    TreeOne->name = "TreeOne";
    TreeOne->transform.SetPosition(glm::vec3(-64.96, 7.06, 85.66));
    TreeOne->transform.SetRotation(glm::vec3(0, -26.20, 0));
    TreeOne->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    TreeOne->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* TreeOne1 = new PhysXObject();
    TreeOne1->LoadModel(*TreeOne);
    GraphicsRender::GetInstance().AddModelAndShader(TreeOne1, application->defaultShader);
    TreeOne1->name = "TreeOne1";
    TreeOne1->transform.SetPosition(glm::vec3(-47.46, 7.47, 88.37));
    TreeOne1->transform.SetRotation(glm::vec3(0, -26.20, 0));
    TreeOne1->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    TreeOne1->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    MeshInstance* instanceMesh = new MeshInstance();
    instanceMesh->LoadModel("Models/Graveyard/TreeThree.fbx");
    instanceMesh->name = "InstancedTree";
    instanceMesh->AddTransformData(glm::vec3(-98.32, 1.77, 101.94), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 1.77, 97.47), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 1.77, 102.73), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 1.77, 108.11), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-90.26, 1.77, 108.11), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-98.09, 1.77, 93.41), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 3.07, 93.41), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 3.07, 93.41), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 3.07, 88.94), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-94.99, 1.97, 91.27), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-98.82, 1.97, 87.12), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-102.19, 3.53, 83.21), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-97.01, 3.53, 83.21), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-82.33, 1.97, 110.49), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-80.46, 1.97, 113.56), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-77.43, 1.97, 111.13), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-72.91, 1.97, 117.52), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-71.19, 1.97, 113.00), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-68.77, 1.97, 115.72), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-68.77, 1.97, 118.15), glm::vec3(0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-65.35, 1.97, 118.15), glm::vec3(0), glm::vec3(0.015));



    GraphicsRender::GetInstance().AddModelAndShader(instanceMesh, application->defaultInstanceShader);

    Model* dummy = new Model();
    dummy->LoadModel("Models/Graveyard/TreeThree.fbx");
    dummy->name = "dummy";
    dummy->transform.SetPosition(glm::vec3(-98.32, 1.97, 101.94));
    dummy->transform.SetRotation(glm::vec3(0));
    dummy->transform.SetScale(glm::vec3(0.015));
    GraphicsRender::GetInstance().AddModelAndShader(dummy, application->defaultShader);

    OcculsionManager::GetInstance().InitializeOcculusion();
}

//TreeThree

void SceneFive::Update()
{
}

void SceneFive::Render()
{
}
