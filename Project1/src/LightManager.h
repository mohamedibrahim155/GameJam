#pragma once

#include "Light.h"

class LightManager 
{
public:
    LightManager();
	~LightManager();
    static LightManager& GetInstance();
   

    void SetUniforms(GLuint shaderID);
    void AddLight(Light* light);
    void RemoveLight(Light* light);
    void AddShader(Shader* shader);
    void RemoveShader(Shader* shader);

    // This is called every frame
    void UpdateUniformValues(GLuint shaderID);
    void UpdateUniformValuesToShader(Shader* shader);
    void  RenderLights();
    static const unsigned int MAX_LIGHT = 11;
    
     Light* GetDirectionalLight();

    const std::vector<Light*>& GetLightList();
private:
    std::vector<Light*> lightList;
    std::vector<Shader*> listOfShaders;
	Light* directionalLight = nullptr;
};



