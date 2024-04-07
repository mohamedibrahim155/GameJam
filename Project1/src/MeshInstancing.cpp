//#include "MeshInstancing.h"
//
//
//// TODO find a way to send model matrix to shader.
//
//
//void MeshInstancing::Draw(Shader* shader)
//{
//	meshes[0]->meshMaterial->UpdateMaterial(shader);
//
//	meshes[0]->VAO->Bind();
//
//	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
//
//	GLCALL(glDrawElements(GL_TRIANGLES, meshes[0]->IBO->GetCount(), GL_UNSIGNED_INT, 0));
//
//	// Add Models Size to instance, keeping it 10 for now TODO Change Later
//
//	GLCALL(glDrawElementsInstanced(GL_TRIANGLES, meshes[0]->IBO->GetCount(), GL_UNSIGNED_INT, 0,10));
//
//	meshes[0]->VAO->Unbind();
//
//}
