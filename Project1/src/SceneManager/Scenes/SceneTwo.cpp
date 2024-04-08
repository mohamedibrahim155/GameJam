#include "SceneTwo.h"
#include "../../ApplicationRenderer.h"
#include "../../Player/PlayerController.h"
#include "../../PostProcessing bounds/CubeVolume.h"
SceneTwo::SceneTwo(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{

}

void SceneTwo::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


    MeshInstance* instanceMesh = new MeshInstance();
    instanceMesh->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
    instanceMesh->name = "InstancedSphere";
    TransformData data;
    data.position = glm::vec3(0, 5, 1);
    data.rotation = glm::vec3(0);
    data.scale = glm::vec3(0.5f);

    for (size_t i = 0; i < 10; i++)
    {
        data.position.x += i;
        instanceMesh->AddTransformData(data);

    }

    GraphicsRender::GetInstance().AddModelAndShader(instanceMesh, application->defaultInstanceShader);

    Model* modelSphere = new Model();
    modelSphere->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
    modelSphere->name = "Sphere";
    GraphicsRender::GetInstance().AddModelAndShader(modelSphere, application->defaultShader);


}

void SceneTwo::Update()
{
}

void SceneTwo::Render()
{
}
