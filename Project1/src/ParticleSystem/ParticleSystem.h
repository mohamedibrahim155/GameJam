#pragma once
#include "../model.h"
#include "../EntityManager/Entity.h"
#include "ParticleEmission.h"
#include "VelocityOverLifetime.h"
#include "EmitterShapeManager.h"
#include "SizeOverLifetime.h"
#include "RotationOverLifetime.h"
#include "ColorOverLifetime.h"

struct Particle
{
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);
	float lifeTime = 0;

}; 


class ParticleSystem : public Model
{
public:

	ParticleSystem();
	~ParticleSystem();

	void UpdateSystem(float deltaTime);
	void RenderParticles();
	void InitializeParticles();

	int maxParticles = 10000;


	float duration = 5;
	float Startdelay = 0;
	float currentTime = 0;


	glm::vec2 startLiftime = glm::vec2(3, 5);
	glm::vec3 startScale = glm::vec3(1.0f);
	glm::vec3 liftimeStartScale = glm::vec3(0.1f);
	glm::vec3 startRotation = glm::vec3(0.8f);

	glm::vec2 startVelocity = glm::vec2(3, 5);
	glm::vec3 gravity = glm::vec3(0);


	ParticleEmission particleEmission;
	EmitterShapeManager shapeManager;
	VelocityOverLifetime velocityOverLifetime;
	SizeOverLifetime sizeOverLifetime;
	RotationOverLifetime rotationOverLifetime;
	ColorOverLifetime colorOverLifetime;

private:


	Burst* burstParticle = nullptr;
	// Inherited via Entity
	void Start() override {}
	void Update(float deltaTime) override {}
	void Render() override;
	void OnDestroy() override {}


	virtual void DrawProperties();
	
	void ParticleSystemProperties();
	void DrawPropertyImGui(std::string propertyName, EmitterProperty& property);


	void BurstUpdate(float deltaTime);
	void ParticleUpdate(float deltaTime);
	void SpawnParticles(int count, float deltaTime);
	void SpawnBurstParticles(Burst& burst);
	bool GetDeadParticle(Particle*& outParticle);

	float columnWidth = 150;
	float mRateOverTimeCarryOver = 0;
	const float MAX_DELTATIME = 1.0f / 60.0f;
	std::vector<Particle> mListOfParticles;
	int count = 0;

};

