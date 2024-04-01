#pragma once
#include<glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include <vector>
#include "Camera.h"

class LightManager;
class GraphicsRender;

enum LightType
{
    DIRECTION_LIGHT =0,
    POINT_LIGHT=1,
    SPOT_LIGHT =2
};

class Light : public Model
{
public:
    Light();
    void Initialize(const LightType& type);
    void Initialize(const LightType& type = LightType::POINT_LIGHT, const float& intensity =0.5f );
    void SetColor(const float x, const float y ,const float z ,const float w);
    void SetColor(const glm::vec4& color);
    void SetAmbientColor(const glm::vec4& ambient);
    void SetAttenuation(const float&  constant, const float&  linear, const float&  quadratic);
    void SetIntensity(const float& intensity);
    void SetCutoffAngle(float cutOffAngle);
    void SetOuterCutoffAngle(float OutercutOffAngle);
    void SetInnerAndOuterCutoffAngle(float cuttOffAngle,float OutercutOffAngle);
    void SetLightType(const LightType& type = LightType::POINT_LIGHT);
    void SetNameBaseOnType();

    float xExtents = 10.0f;
    float yExtents = 10.0f;
    float nearPlane = 1.0f;
    float farPlane = 7.5f;
    float shadowCaptureDistance = 100.0f;
    bool enableShadows = false;

   



    glm::vec4& GetLightColor();
    glm::vec4& GetAmbientColor();
    glm::vec3& GetAttenuation();
    float& GetIntensityValue();
    glm::vec2& GetInnerAndOuterAngle();

    glm::mat4 GetViewMatrix(Camera* cam);
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetLightMatrix(Camera* cam);


    ~Light() { };

    void DrawProperties() override;
    void SceneDraw() override;

    void Start() override;
    void Update(float deltaTime) override;
    void OnDestroy() override;
    void Render() override;

    LightType lightType;
private:
    Material material;


    glm::mat4 projectionMatrix = glm::mat4(1.0f);


    glm::vec4 ambient;

    glm::vec4 color;
    

     //for pointLight
    float constant;
    float linear;
    float quadratic;
    float intensity = 0.5f;

    //spot Lights
    float cutOffAngle;
    float outerCutOffAngle;

    float lightTransformScale = 0.25f;
};







