#include "SceneManager.h"
#include "SceneNode.h"
#include "Engine.h"

//Actor
#include "../Actor.h"


//other
#include <stack>

SceneManager::SceneManager()
{
	m_pRootNode = std::make_unique<SceneNode>();
	m_pQuadTree = std::make_shared<QuadTree>(0,
		Bounds(0, 0, Engine::getInstance().GetWindowsWidth(), Engine::getInstance().GetWindowsHeight()));
}


SceneManager::~SceneManager()
{
}


ISceneNode* SceneManager::AddChild(uint32_t ActorId, ISceneNode * pActor)
{
	auto& pIter = m_ActorMap.find(ActorId);
	if(pIter == m_ActorMap.end())
	{
		m_ActorMap.insert(std::make_pair(ActorId, pActor));
		m_pRootNode->VAddChildren(pActor);
		return pActor;
	}
	else
	{
		//hmmmmmmm
		delete pActor;
		pActor = nullptr;
	}
	return nullptr;
}

ISceneNode*  SceneManager::GetChild(uint32_t ActorId)
{
	auto& pIter = m_ActorMap.find(ActorId);
	if (pIter != m_ActorMap.end())
	{
		return pIter->second;
	}

	return nullptr;
}

void SceneManager::DrawNode(const QuadTree* m_root)
{
	std::stack<const QuadTree*> stack;
	stack.push(m_root);

	while (!stack.empty())
	{
		auto quad = stack.top();
		if (quad == nullptr)continue;

		stack.pop();
		for (auto& pNode : quad->nodes)
		{
			if (pNode == nullptr)continue;
			stack.push(pNode.get());
		}

		const Bounds& pBounds = quad->bounds;
		Engine::getInstance().GetRenderer()->DrawRectangular(pBounds.x, pBounds.y, pBounds.width, pBounds.height);
	}
}

void SceneManager::Render()
{
	//Draw Quad
	DrawNode(m_pQuadTree.get());

	//Draw Scene
	m_pRootNode->VRender();
}

void SceneManager::Update(long timestamp)
{
	//Update quadtree
	m_pQuadTree->clear();
	for (auto& pSceneNode : m_pRootNode->m_Children)
	{
		auto& pActors = pSceneNode->GetActors();
		if (pActors.size() > 0)
			if (pActors[0].m_actorType == enumObjectsId::Bullet)continue;

		for (auto& pActor : pActors)
		{
 			if (pActor.m_alive)
			{
				m_pQuadTree->insert(&pActor);
			}
		}
	}

	m_pRootNode->VUpdate(timestamp);
}
