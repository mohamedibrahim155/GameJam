#include "Fire.h"
#include "../ConeEmitter.h"

Fire::Fire()
{
	
	//std::string difPath = "Textures/Particles/Fire2.png";
	name = "Fire";
	isVisible = true;

	std::string difPath = "Textures/Particles/FogTexture1.png";
	Texture* diffuse = new Texture(difPath);
	particleEmission.m_ParticleModel->particleModel->meshes[0]->meshMaterial = new ParticleMaterial();
	particleEmission.m_ParticleModel->particleModel->meshes[0]->meshMaterial->particleMaterial()->diffuseTexture = diffuse;

	startLiftime = { 0,1 };
	duration = 1;
	startVelocity = { 1,3 };
	particleEmission.rateOverTime = 150;
	
	sizeOverLifetime.isEnabled = true;
	sizeOverLifetime.startScale = glm::vec3(1);
	sizeOverLifetime.endScale = glm::vec3(0);
	//shapeManager.SetEmitterShape(EmitterShape::)

	rotationOverLifetime.isEnabled = true;
	rotationOverLifetime.startRotation = { 0,0,-360 };
	rotationOverLifetime.endRotation = { 0,0,360 };


	// alter to match the yellow color of the flame
	colorOverLifetime.isEnabled = true;
	
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,0,1),   0 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,0,0.8), 0.2 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,0,0.6), 0.4 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.6 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.8 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   1 });

	shapeManager.SetEmitterShape(EmitterShape::CONE);
	shapeManager.asConeEmitter()->angle = 10.0f;
	shapeManager.asConeEmitter()->radius = 0.3f;
	shapeManager.asConeEmitter()->position = glm::vec3(0, 2, 15);

	InitializeParticles();
}
