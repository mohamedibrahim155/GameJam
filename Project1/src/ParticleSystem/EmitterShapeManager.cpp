#include "EmitterShapeManager.h"
#include "ConeEmitter.h"
#include "BoxEmitter.h"
#include "SphereEmitter.h"




EmitterShapeManager::EmitterShapeManager()
{
	AddShape(EmitterShape::CONE, new ConeEmitter());
	AddShape(EmitterShape::BOX, new BoxEmitter());
	AddShape(EmitterShape::SPHERE, new SphereEmitter());

	SetShape(EmitterShape::BOX);
}

EmitterShapeManager::~EmitterShapeManager()
{


}

void EmitterShapeManager::SetShape(EmitterShape shape)
{
	this->m_EmitterShape = shape;
	m_CurrentEmitterShape = (int)m_EmitterShape;
}

EmitterShape EmitterShapeManager::GetShape()
{
	return m_EmitterShape;
}

EmitterShape EmitterShapeManager::GetCurrentShape()
{
	return (EmitterShape)m_CurrentEmitterShape;
}

BaseEmitterShape* EmitterShapeManager::GetEmitterShape()
{
	return m_ListOfShapes[m_EmitterShape];
}

void EmitterShapeManager::AddShape(EmitterShape shapeType, BaseEmitterShape* shape)
{
	m_ListOfShapes[shapeType] = shape;
}

void EmitterShapeManager::RemoveShape(EmitterShape shapeType)
{
	m_ListOfShapes.erase(shapeType);
}

void EmitterShapeManager::Render(glm::vec3& parentPos)
{
	GetEmitterShape()->Render(parentPos);
}

void EmitterShapeManager::GetParticlePosAndDir(glm::vec3& pos, glm::vec3& dir)
{
	GetEmitterShape()->GetParticlePosAndDir(pos, dir);
}

ConeEmitter* EmitterShapeManager::AsConeEmitter()
{
	return (ConeEmitter*)GetShape();
}

BoxEmitter* EmitterShapeManager::AsBoxEmitter()
{
	return (BoxEmitter*)GetShape();
}

SphereEmitter* EmitterShapeManager::AsSphereEmitter()
{
	return (SphereEmitter*)GetShape();
}

void EmitterShapeManager::DrawProperties()
{
	if (DrawDropDownImGui("Shape", m_CurrentEmitterShape, shapeString, 3))
	{
		SetShape((EmitterShape)m_CurrentEmitterShape);
	}
	
	m_ListOfShapes[m_EmitterShape]->DrawProperties();

}

void EmitterShapeManager::SceneDraw()
{
}

