#pragma once
#include "EmitterProperty.h"
#include "BaseEmitterShape.h"
#include <unordered_map>

enum class EmitterShape
{
	BOX = 0,
	CONE = 1,
	SPHERE = 2

};

class ConeEmitter;
class BoxEmitter;
class SphereEmitter;

class EmitterShapeManager : public EmitterProperty
{
public:

	EmitterShapeManager();
	~EmitterShapeManager();

	void SetShape(EmitterShape shape);
	EmitterShape GetShape();
	EmitterShape GetCurrentShape();

	BaseEmitterShape* GetEmitterShape();

	void AddShape(EmitterShape shapeType, BaseEmitterShape* shape);
	void RemoveShape(EmitterShape shapeType);

	void Render(glm::vec3& parentPos);

	void GetParticlePosAndDir(glm::vec3& pos, glm::vec3& dir);


	// Inherited via EmitterProperty
	void DrawProperties() override;

	void SceneDraw() override;

	ConeEmitter* AsConeEmitter();
	BoxEmitter* AsBoxEmitter();
	SphereEmitter* AsSphereEmitter();

private :

	const char* shapeString[3] = { "BOX", "CONE", "SPHERE" };
	std::unordered_map< EmitterShape, BaseEmitterShape*> m_ListOfShapes;

	int m_CurrentEmitterShape = 0;
	EmitterShape m_EmitterShape = EmitterShape::CONE;

};

