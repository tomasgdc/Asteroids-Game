#pragma once
#include "ISceneNode.h"
#include <vector>
#include "../Actor.h"

//////////////////////////////////////////////////////////////
//
// SceneNodeList
//
//   Every scene node has a list of its children - this 
//   is implemented as a vector since it is expected that
//   we won't add/delete nodes very often, and we'll want 
//   fast random access to each child.
//
//////////////////////////////////////////////////////////////
typedef std::vector<ISceneNode*> SceneNodeList;
struct Actor;

/*
	Each SceneNode manages it's own memory by calling DeleteNode
*/
class SceneNode : public ISceneNode
{
	friend class SceneManager;
protected:
	SceneNodeList m_Children;
	virtual std::vector<Actor>& GetActors() { return m_Actors; }

public:
	SceneNode();
	virtual ~SceneNode();

	virtual void VUpdate(long miliseconds);
	virtual void VRender();
	virtual void VAddChildren(ISceneNode* pSceneNode);
private:
	//Will always be empty
	std::vector<Actor> m_Actors;
};