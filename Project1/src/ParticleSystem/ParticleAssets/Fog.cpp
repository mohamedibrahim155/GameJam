#include "Fog.h"

Fog::Fog()
{
	name = "Fog";
	startVelocity = { 0,0 };
	particleEmission.rateOverTime = 100;

	rotationOverLifetime.isEnabled = true;
	rotationOverLifetime.endRotation = glm::vec3(0, 0, 100);

	colorOverLifetime.isEnabled = true;
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   0 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.1 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.2 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.3 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.8), 0.4 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,1),   0.5 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.8), 0.6});
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.7 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.8 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.9 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   1 });

	shapeManager.GetEmitterShape()->scale = glm::vec3(7, 2, 7);

	InitializeParticles();

}
