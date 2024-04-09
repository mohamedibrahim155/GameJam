#include "ParticleSystem.h"
#include "../Random.h"
#include "../GraphicsRender.h"
#include "../ImGui/EditorLayout.h"
#include "ParticleSystemManager.h"
#include "Particle.h"


ParticleSystem::ParticleSystem()
{

	//LoadModel("Models/DefaultQuad/DefaultQuad.fbx");
	name = "Particle System";

	//GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().solidColorShader);
	ParticleSystemManager::GetInstance().AddParticleSystem(this);
	InitializeEntity(this);
	InitializeParticles();
	

}
void Particle::SetLifeTime(float lifeTime)
{
	this->currentLifetime = lifeTime;
	this->lifeTime = lifeTime;
}


ParticleSystem::~ParticleSystem()
{
	ParticleSystemManager::GetInstance().RemoveParticleSystem(this);

}

void ParticleSystem::UpdateSystem(float deltaTime)
{
	currentTime += deltaTime;

	if (particleEmission.rateOverTime == 0) return;

	float currentRate = (particleEmission.rateOverTime * deltaTime) + mRateOverTimeCarryOver ;
	int numOfParticlesThisFrame = (int)currentRate;


	mRateOverTimeCarryOver = currentRate - numOfParticlesThisFrame;

	SpawnParticles(numOfParticlesThisFrame,currentTime);


	BurstUpdate(deltaTime);
	ParticleUpdate(deltaTime);	
}

void ParticleSystem::RenderParticles()
{
	for (Particle& particle : mListOfParticles)
	{
		if (particle.currentLifetime <= 0) continue;

		particleEmission.m_ParticleModel->particleModel->transform.SetPosition(particle.position);
		particleEmission.m_ParticleModel->particleModel->transform.SetScale(particle.scale * sizeOverLifetime.ScaleParticle(particle));
		particleEmission.m_ParticleModel->particleModel->transform.SetRotation(startRotation * rotationOverLifetime.AngularVelocity(particle));
		//Find a Way to use this function colorOverLifetime.SendColorToMat(args..) inside material of the mesh.
		particleEmission.m_ParticleModel->particleModel->Draw(GraphicsRender::GetInstance().solidColorShader);
	}

}

void ParticleSystem::InitializeParticles()
{
	mListOfParticles.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		Particle newParticle;

		mListOfParticles.push_back(newParticle);
	}
}

void ParticleSystem::Render()
{
	/*std::vector<Object*> selectedObjects = EditorLayout::GetInstance().GetSelectedObjects();

	if (selectedObjects.size() == 0) return;

	if (selectedObjects[0] != this) return;*/


	shapeManager.Render();
}

void ParticleSystem::DrawProperties()
{

	Entity::DrawProperties();

	if (!ImGui::TreeNodeEx("Particle System", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}
	ParticleSystemProperties();

	DrawPropertyImGui("Emission", particleEmission);
	DrawPropertyImGui("Velocity Over Lifetime", velocityOverLifetime);
	DrawPropertyImGui("Size Over Lifetime", sizeOverLifetime);
	DrawPropertyImGui("Rotation Over Lifetime", rotationOverLifetime);
	DrawPropertyImGui("Color Over Lifetime", colorOverLifetime);
	DrawPropertyImGui("Shape", shapeManager);


	ImGui::TreePop();
}

void ParticleSystem::ParticleSystemProperties()
{
	if (!ImGui::TreeNodeEx("System Properties"))
	{
		return;
	}

	if (DrawIntImGui("MaxParticles", maxParticles))
	{
		mListOfParticles.clear();
		InitializeParticles();
	}

	DrawFloatImGui("CurrentTime", currentTime);
	DrawFloatImGui("Duration", duration);
	DrawFloatImGui("StartDelay", Startdelay);

	DrawTransformVector2ImGui("LifeTime", startLiftime, 0, columnWidth);
	DrawTransformVector2ImGui("Velocity", startVelocity, 0, columnWidth);

	DrawTransformVector3ImGui("Size", startScale, 0, columnWidth);
	DrawTransformVector3ImGui("Rotation", startRotation , 0, columnWidth);
	DrawTransformVector3ImGui("Gravity", gravity, 0, columnWidth);


	ImGui::TreePop();
}

void ParticleSystem::DrawPropertyImGui(std::string propertyName, EmitterProperty& property)
{
	if (!ImGui::TreeNodeEx(propertyName.c_str()))
	{
		return;
	}

	property.DrawProperties();

	ImGui::TreePop();
}



void ParticleSystem::BurstUpdate(float deltaTime)
{

	for (Burst& burst : particleEmission.m_ListOfBursts)
	{
		if (currentTime <= burst.time) continue;
		if (burst.cycles != 0 && burst.currentCycle >= burst.cycles) continue;


		if (burst.currentCycle == 0)
		{
			SpawnBurstParticles(burst);
		}
		else
		{
			float _currentTime = currentTime - burst.time;
			int numOfBursts = (int)(_currentTime / burst.interval);

			numOfBursts -= burst.currentCycle - 1;

			if (numOfBursts != 0)
			{
				SpawnBurstParticles(burst);
			}
		}

	}
}

void ParticleSystem::ParticleUpdate(float deltaTime)
{
	for (Particle& particle : mListOfParticles)
	{
		if (particle.currentLifetime <= 0) continue;

		particle.currentLifetime -= deltaTime;
		particle.velocity += gravity * deltaTime;
		particle.position += particle.velocity * deltaTime;
		particle.rotation += startRotation.z * rotationOverLifetime.AngularVelocity(particle) * deltaTime;
	}
}

void ParticleSystem::SpawnParticles(int count, float deltaTime)
{
	glm::vec3 pos;
	glm::vec3 dir;
	Particle* particle = nullptr;

	for (int i = 0; i < count; i++)
	{
		if (!GetDeadParticle(particle)) return;
		if (particle == nullptr) return;

		shapeManager.UpdateParticle(pos, dir);

		particle->position = transform.position + pos;
		particle->velocity = dir * GetRandomFloatNumber(startVelocity.x + velocityOverLifetime.particleSpeed, startVelocity.y + velocityOverLifetime.particleSpeed)   ;
		particle->SetLifeTime(GetRandomFloatNumber(startLiftime.x, startLiftime.y));
		particle->scale = startScale * GetRandomFloatNumber(particleEmission.m_ParticleModel->minParticleSize, particleEmission.m_ParticleModel->maxParticleSize);
		particle->rotation = startRotation;
		//particle->scale = sizeOverLifetime.ScaleOverLifetime(liftimeStartScale, startScale,deltaTime);
	}
	
}

void ParticleSystem::SpawnBurstParticles(Burst& burst)
{
	float probability = GetRandomFloatNumber(0, 1.0f);

	if (probability < burst.probability)
	{
		SpawnParticles(burst.count,currentTime);
		burst.currentCycle++;
	}
}

bool ParticleSystem::GetDeadParticle(Particle*& outParticle)
{
	for (Particle& particle : mListOfParticles)
	{
		if (particle.currentLifetime <= 0)
		{
			outParticle = &particle;
			return true;
		}
	}

	return false;
}
