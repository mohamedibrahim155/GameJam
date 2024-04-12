#include "SceneOne.h"
#include "../../ApplicationRenderer.h"
#include "../../Player/PlayerController.h"
#include "../../PostProcessing bounds/CubeVolume.h"
SceneOne::SceneOne(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
	
}

void SceneOne::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    PlayerController* player = new PlayerController(application);
    player->transform.SetPosition(glm::vec3(-40.53, 23.10, 75.10));

    PhysXObject* terrain = new PhysXObject();
    /*std::string difPath = "Models/Terrain/Terrain.png";
    Texture* dif = new Texture(difPath);*/

    terrain->LoadModel("Models/Terrain/Terrain.obj");
   // terrain->meshes[0]->meshMaterial->material()->diffuseTexture = dif;
    GraphicsRender::GetInstance().AddModelAndShader(terrain, application->defaultShader);
    terrain->name = "Terrain";
    terrain->transform.SetPosition(glm::vec3(0, -2, 0));
    terrain->transform.SetRotation(glm::vec3(0, 0, 0));
    terrain->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    CubeVolume* cube = new CubeVolume();
    cube->transform.SetPosition(glm::vec3(0, -1, 5));
    cube->transform.SetScale(glm::vec3(0.5f));
    cube->Intialize(application->gameScenecamera);

    //PhysXObject* cathedral = new PhysXObject();
  
    /*cathedral->LoadModel("Models/Cathedral/Cath.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(cathedral, application->defaultShader);
    cathedral->name = "Cathedral";
    cathedral->transform.SetPosition(glm::vec3(-61.7, 21.00, 83.40));
    cathedral->transform.SetRotation(glm::vec3(0, 0, 0));
    cathedral->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    cathedral->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);*/
}

void SceneOne::Update()
{
}

void SceneOne::Render()
{
}
