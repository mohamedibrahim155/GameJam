#include "CubeVolume.h"
#include "../PhysX/PhysXEngine.h"
#include "../GraphicsRender.h"
#include "../DebugModels.h"
CubeVolume::CubeVolume()
{
	LoadModel("Models/DefaultCube/DefaultCube.fbx");
	name = "Cube Volume";
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().alphaBlendShader);
	
	volumeType = eVolumeType::CUBE;
}

void CubeVolume::SetExtends(const glm::vec3& extends)
{
	this->extends = extends;
	collider->AsBoxCollider()->SetSize(this->extends);

}

void CubeVolume::DrawVolume()
{
	GraphicsRender::GetInstance().DrawBox(transform.position, this->extends,
		glm::vec4(0, 1, 0, 1), true);
}

void CubeVolume::OnTriggerEnter(PhysXObject* otherObject)
{

	if (otherObject->tag == "Player")
	{
		EnablePostProccesing(true);
	}
}

void CubeVolume::OnTriggerExit(PhysXObject* otherObject)
{
	if (otherObject->tag == "Player")
	{
		EnablePostProccesing(false);
	}
}


