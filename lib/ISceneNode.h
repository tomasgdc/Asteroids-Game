#pragma once
#include<vector>
struct Actor;

class ISceneNode
{
public:
	
	virtual ~ISceneNode() {}
	virtual void VUpdate(long miliseconds) = 0;
	virtual void VRender() = 0;
	virtual void VAddChildren(ISceneNode* pSceneNode) = 0;
	virtual std::vector<Actor>&  GetActors() = 0;
};