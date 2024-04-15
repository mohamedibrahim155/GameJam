#include "SceneFour.h"
#include "../../ApplicationRenderer.h"
#include "../../Grass/GrassMesh.h"
SceneFour::SceneFour(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneFour::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));






    GrassMesh* grassMeshInstance = new GrassMesh();

    float objectSpacing = 10;
    glm::vec3 center{ 0 };

    float radius = 5;
   

    for (size_t i = 0; i < 1; i++)
    {
        for (size_t j = 0; j < 1; j++)
        {

        }

    }
    grassMeshInstance->AddTransformData(glm::vec3(0, center.y, 0), glm::vec3(0), glm::vec3(0.015f));





    //grassMeshInstance->AddTransformData(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(0.025f));
    GraphicsRender::GetInstance().AddModelAndShader(grassMeshInstance, application->grassInstanceShader);


    Model* Plane = new Model();
    Plane->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");

    //Plane->transform.SetPosition(glm::vec3(0, -1, 0));
    Plane->transform.SetRotation(glm::vec3(90, 0, 0));
    Plane->transform.SetScale(glm::vec3(10));
    GraphicsRender::GetInstance().AddModelAndShader(Plane, application->defaultShader);


    Model* Plane2 = new Model();
    Plane2->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");

    Plane->transform.SetPosition(glm::vec3(0, 10, 0));
    Plane2->transform.SetRotation(glm::vec3(90, 0, 0));
    Plane2->transform.SetScale(glm::vec3(10));
    GraphicsRender::GetInstance().AddModelAndShader(Plane2, application->defaultShader);

    Fire* fire = new Fire();

}

void SceneFour::Update()
{
}

void SceneFour::Render()
{
}
