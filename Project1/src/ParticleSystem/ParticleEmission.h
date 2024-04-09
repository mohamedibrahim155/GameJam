#pragma once
#include "EmitterProperty.h"
#include "../model.h"
#include <vector>

struct Burst
{
	Burst(float time, float count, float cycles, float interval, float probability)
	{
		this->time = time;
		this->count = count;
		this->cycles = cycles;
		this->interval = interval;
		this->probability = probability;
	}

	float time = 0;					
	int count = 10;					
	int cycles = 1;					
	float interval = 1;				
	float probability = 1;			
	int currentCycle = 0;
};



class ParticleEmission : public EmitterProperty
{

public:

	struct ParticleModel
	{
		ParticleModel()
		{
			particleModel = new Model("Models/DefaultQuad/DefaultQuad.fbx");

		}


		float minParticleSize = 0.0f;
		float maxParticleSize = 1.0f;

		Model* particleModel = nullptr;

	};


	ParticleEmission();

	float rateOverTime = 10;

	void AddBurst(Burst burstInfo);
	void RemoveBurst(int index);

	
	void BurstProperties(Burst& infor, int index);

	std::vector<Burst> m_ListOfBursts;

	ParticleModel* m_ParticleModel = nullptr;

	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;
};

