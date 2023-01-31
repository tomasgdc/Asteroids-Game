#pragma once
#include <vector>
#include <array>
#include <memory>
#include  "Physics.h"

class QuadTree
{
	int MAX_OBJECTS = 5;
	int MAX_LEVELS = 5;

	int level;
	std::vector<Actor*> objects;
	Bounds bounds;
	std::array<std::unique_ptr<QuadTree>, 4> nodes;

	friend class SceneManager;
public:
	QuadTree(int iLevel, const Bounds& pBounnds)
	{
		level = iLevel;
		bounds = pBounnds;
	}

	void clear()
	{
		objects.clear();
		for (auto& node : nodes)
		{
			if (node != nullptr)
			{
				node->clear();
				node = nullptr;
			}
		}
	}

	void insert(Actor* pBounds)
	{
		//Check for null pointer
		if (pBounds == nullptr) { return; }

		if (nodes[0] != nullptr)
		{
			int index = getIndex(pBounds);
			if (index != -1)
			{
				nodes[index]->insert(pBounds);
				return;
			}
		}

		objects.push_back(pBounds);
		if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
		{
			if (nodes[0] == nullptr)
			{
				split();
			} 

			int i = objects.size() - 1;
			while (i >= 0)
			{
				int index = getIndex(objects[i]);
				if (index != -1)
				{
					nodes[index]->insert(objects[i]);
					objects.erase(objects.begin() + i);
				}
				{
					i--;
				}
			}
		}
	}


	/*
		Retrieve all objects that could collide with given object
	*/
	void retrieve(std::vector<Actor*>& returnedObjects, const Actor* pBounds)
	{
		int index = getIndex(pBounds);
		if (index != -1 && nodes[0] != nullptr)
		{
			nodes[index]->retrieve(returnedObjects, pBounds);

			for (auto &object : objects)
				returnedObjects.push_back(object);
		}
	}

private:
	//Split node into 4 subnodes
	void split()
	{
		float subWidth = bounds.width / 2.0f;
		float subHeight = bounds.height / 2.0f;

		float x = bounds.x;
		float y = bounds.y;

		nodes[0] = std::make_unique<QuadTree>(level + 1, Bounds(x + subWidth, y, subWidth, subHeight));
		nodes[1] = std::make_unique<QuadTree>(level + 1, Bounds(x, y, subWidth, subHeight));
		nodes[2] = std::make_unique<QuadTree>(level + 1, Bounds(x, y + subHeight, subWidth, subHeight));
		nodes[3] = std::make_unique<QuadTree>(level + 1, Bounds(x + subWidth, y + subHeight, subWidth, subHeight));
	}

	/*
		Determine which node the objects belongs to.
		-1 means object cannot completely fit within a child node and is part
		of the parrent node
	*/
	int getIndex(const Actor* pBounds)
	{
		int index = -1;
		if (pBounds == nullptr)return index;
		
		double verticalMidPoint = bounds.x + (bounds.width / 2.0f);
		double horizontalMidPoint = bounds.y + (bounds.height / 2.0f);

		//Object can completely fit within top quadrants
		//m.y + m.height;
		bool topQuadrant = (pBounds->m_y < horizontalMidPoint  && pBounds->m_y  + pBounds->m_size < horizontalMidPoint);

		//Object can completely fit within left quadrants
		bool bottomQuadrant = (pBounds->m_y > horizontalMidPoint);

		//m.x + m.width
		if (pBounds->m_x < verticalMidPoint && pBounds->m_x + pBounds->m_size < verticalMidPoint)
		{
			if (topQuadrant)
				index = 1;
			else if (bottomQuadrant)
				index = 2;
		}
		else if (pBounds->m_x > verticalMidPoint)
		{
			if (topQuadrant)
				index = 0;
			else if (bottomQuadrant)
				index = 3;
		}
		return index;
	}
};