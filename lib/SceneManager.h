#pragma once
#include <map>
#include <vector>
#include "QuadTree.h"


//forward declaration
class ISceneNode;
class SceneNode;

//First is actorId
typedef std::map<uint32_t, ISceneNode*> SceneActorMap;

/*
	Scene manager provides adding, rendering and update via root node.
	Also provides fast lookup for specific actor by it's id
*/
class SceneManager
{
protected:
	void DrawNode(const QuadTree* m_root);
public:
	SceneManager();
	~SceneManager();

	ISceneNode*  AddChild(uint32_t ActorId, ISceneNode* pActor);
	ISceneNode*  GetChild(uint32_t ActorId);

	void Render();
	void Update(long timestamp);
	QuadTree* GetQuadTree() { return m_pQuadTree.get(); }
private:
	SceneActorMap m_ActorMap;
	std::unique_ptr<SceneNode>	  m_pRootNode;
	std::shared_ptr<QuadTree>	  m_pQuadTree;
};