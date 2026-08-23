#version 330 core

layout (location = 0) in vec3 position;
layout (location = 4) in vec4 aBoneID;
layout (location = 5) in vec4 aBoneWeight;

const int MAX_BONES = 200;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform bool isBones;
uniform mat4 BoneMatrices[MAX_BONES];

void main()
{
    vec4 totalPosition = vec4(position, 1.0);

    if (isBones)
    {
        mat4 boneTransform = BoneMatrices[int(aBoneID[0])] * aBoneWeight[0];
        boneTransform += BoneMatrices[int(aBoneID[1])] * aBoneWeight[1];
        boneTransform += BoneMatrices[int(aBoneID[2])] * aBoneWeight[2];
        boneTransform += BoneMatrices[int(aBoneID[3])] * aBoneWeight[3];

        totalPosition = boneTransform * vec4(position, 1.0);
    }

    gl_Position = lightSpaceMatrix * model * totalPosition;
}
