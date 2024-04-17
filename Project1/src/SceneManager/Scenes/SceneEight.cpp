#include "SceneEight.h"
#include "../../ApplicationRenderer.h"
#include "../../Physics/Softbody/SoftBody.h"
#include "../../Threading/SoftBodyThread.h"

SoftBodyThread* sbThread = sbInfo;

SceneEight::SceneEight(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{


}

SceneEight::~SceneEight()
{
}

void SceneEight::Start()
{
    StartThreadForSoftBody(0.01f);

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    std::string textureFile = "Models/Plane/Flag1.png";
    Texture* diffuse = new Texture(textureFile);

    std::string textureFile2 = "Models/Plane/Flag.png";
    Texture* diffuse2 = new Texture(textureFile2);

    std::string alphaText = "Models/Plane/BW1.png";
    Texture* modelAlpha = new Texture(alphaText);

    SoftBodyObjs* softBodyTest1 = new SoftBodyObjs();
    softBodyTest1->LoadModel("Models/Plane/Flag.ply");
    softBodyTest1->name = "MY PLANE";
    softBodyTest1->meshes[0]->meshMaterial->material()->diffuseTexture = diffuse2;
    //softBodyTest1->meshes[0]->meshMaterial->material()->alphaTexture = modelAlpha;
    softBodyTest1->meshes[0]->meshMaterial->material()->useMaskTexture = true;
    softBodyTest1->transform.SetPosition(glm::vec3(0, 1, 0));
    softBodyTest1->transform.SetRotation(glm::vec3(0, 90, 0));
    softBodyTest1->transform.SetScale(glm::vec3(10, 7, 5));
    GraphicsRender::GetInstance().AddModelAndShader(softBodyTest1, GraphicsRender::GetInstance().alphaCutoutShader);
    
    softBodyTest1->InitializeSoftBody();
    softBodyTest1->AddLockSphere(0, 0.01f);
}

void SceneEight::Update()
{
    sbThread->bRun = application->isPlayMode ? true : false;
}

void SceneEight::Render()
{
}
