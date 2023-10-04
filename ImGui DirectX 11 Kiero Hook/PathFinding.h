#pragma once
#include "il2cpp-appdata.h"
#include <chrono>
#include <unordered_map>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/imgui_internal.h"
#include "Globals.h"
#include "Util.h"
#include "Functions.h"
#include "Console.h"
static Il2CppArrayT<bool>* ConfigData_doesBlockHaveCollider = nullptr;
static Il2CppArrayT<bool>* ConfigData_doesBlockHaveColliderOneWay = nullptr;
#define GetBlockAtMapPoint(point, blockLayer) blockLayer->vector[point.x]->vector[point.y]
#define DoesBlockTypeHaveCollider(blockType) ConfigData_doesBlockHaveCollider->vector[blockType]
#define DoesMapPointHaveColider(point, blockLayer) ConfigData_doesBlockHaveCollider->vector[blockLayer->vector[point.x]->vector[point.y].blockType]
#define DoesBlockInstaKill(point, blockLayer) IsBlockInstaKill(blockLayer->vector[point.x]->vector[point.y].blockType)
#define DoesBlockHaveColliderOneWay(blockType) ConfigData_doesBlockHaveColliderOneWay->vector[blockType]

struct node : Vector2i
{
public:
	node* parent;
	int gCost = 0;
	int hCost = 0;
	int getFCost()
	{
		return this->gCost + this->hCost;
	}
	node(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->parent = nullptr;
	}
	node(Vector2i pos)
	{
		this->x = pos.x;
		this->y = pos.y;
		this->parent = nullptr;
	}
	node(int x, int y, node* parent)
	{
		this->x = x;
		this->y = y;
		this->parent = parent;
	}
	node()
	{
		this->x = 0;
		this->y = 0;
		this->parent = nullptr;
	}
	int GetDistance(node nodeB)
	{
		int dstX = abs(this->x - nodeB.x);
		int dstY = abs(this->y - nodeB.y);

		if (dstX > dstY)
			return 14 * dstY + 10 * (dstX - dstY);
		return 14 * dstX + 10 * (dstY - dstX);
	}
	~node() {}
};
namespace std
{
	template <> struct hash<Vector2i>
	{
		typedef Vector2i argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const Vector2i& id) const noexcept
		{
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};

	template <> struct hash<node>
	{
		typedef node argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const node& id) const noexcept
		{
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}
bool IsBlockInstaKill(int blockType)
{
	switch (blockType)
	{
	case 0xCA3:
	case 0xCA2:
	case 0x1143:
	case 0x1170:
	case 0xBE4:
	case 0x53C:
	case 0xA7B:
	case 0x1C5:
	case 0x3BF:
		return true;
	}
	return false;
}
static bool IsPlatformCanPass(Vector2i curPos, Vector2i targetPos, Vector2i worldSize, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks)
{
	if (InBounds(curPos, worldSize) && InBounds(targetPos, worldSize))
	{
		LayerBlock targetBlock = GetBlockAtMapPoint(targetPos, worldBlocks);
		bool targethasColliderOneWay = DoesBlockHaveColliderOneWay(targetBlock.blockType);
		if (targethasColliderOneWay)
		{
			if (curPos.y < targetPos.y)
			{
				return true;
			}
			if ((curPos.y < targetPos.y || curPos.y == targetPos.y) && (curPos.x < targetPos.x || curPos.x > targetPos.x))
			{
				return true;
			}
			Vector2i l = { targetPos.x - 1, targetPos.y };
			Vector2i r = { targetPos.x - 1, targetPos.y };
			if (InBounds(l, worldSize))
			{
				Vector2i lu = { targetPos.x - 1, targetPos.y + 1 };
				targetBlock = worldBlocks->vector[l.x]->vector[l.y];
				//if (!InBounds(lu, worldSize))
				//{
				//	if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType))
				//		return true;
				//}
				//else
				//{
				LayerBlock blockU = worldBlocks->vector[lu.x]->vector[lu.y];
				if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType) && !DoesBlockTypeHaveCollider(blockU.blockType))
					return true;
				//}
			}
			if (InBounds(r, worldSize))
			{
				Vector2i ru = { targetPos.x - 1, targetPos.y + 1 };
				targetBlock = worldBlocks->vector[r.x]->vector[r.y];
				//if (!InBounds(ru, worldSize))
				//{
				//	if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType))
				//		return true;
				//}
				//else
				//{
				LayerBlock blockU = worldBlocks->vector[ru.x]->vector[ru.y];
				if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType) && !DoesBlockTypeHaveCollider(blockU.blockType))
					return true;
				//}
			}
		}
	}
	return false;
}
static bool IsPlatformCanPassNether(Vector2i curPos, Vector2i targetPos, Vector2i worldSize, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks)
{
	if (InBounds(curPos, worldSize) && InBounds(targetPos, worldSize))
	{
		LayerBlock targetBlock = GetBlockAtMapPoint(targetPos, worldBlocks);
		bool targethasColliderOneWay = DoesBlockHaveColliderOneWay(targetBlock.blockType);
		if (targethasColliderOneWay)
		{
			if (curPos.y < targetPos.y)
			{
				return true;
			}
			if ((curPos.y < targetPos.y || curPos.y == targetPos.y) && (curPos.x < targetPos.x || curPos.x > targetPos.x))
			{
				return true;
			}
			//Vector2i l = { targetPos.x - 1, targetPos.y };
			//Vector2i r = { targetPos.x - 1, targetPos.y };
			//if (InBounds(l, worldSize))
			//{
			//	Vector2i lu = { targetPos.x - 1, targetPos.y + 1 };
			//	targetBlock = worldBlocks->vector[l.x]->vector[l.y];
			//	LayerBlock blockU = worldBlocks->vector[lu.x]->vector[lu.y];
			//	if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType) && !DoesBlockTypeHaveCollider(blockU.blockType))
			//		return true;
			//}
			//if (InBounds(r, worldSize))
			//{
			//	Vector2i ru = { targetPos.x - 1, targetPos.y + 1 };
			//	targetBlock = worldBlocks->vector[r.x]->vector[r.y];
			//	LayerBlock blockU = worldBlocks->vector[ru.x]->vector[ru.y];
			//	if (!DoesBlockHaveColliderOneWay(targetBlock.blockType) && !DoesBlockTypeHaveCollider(targetBlock.blockType) && !DoesBlockTypeHaveCollider(blockU.blockType))
			//		return true;
			//}
		}
	}
	return false;
}
static bool IsDoorLocked(Vector2i point, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* itemDataLayer)
{
	WorldItemBase* base = itemDataLayer->vector[point.x]->vector[point.y]; //il2cpp_array_get(il2cpp_array_get(itemDataLayer, Il2CppArray*, point.x), Il2CppObject*, point.y);
	if (base)
	{
		FieldInfo* f = il2cpp_class_get_field_from_name(base->klass, "isLocked");
		if (f)
		{
			return il2cpp_object_get_field_value(base, bool, f);
		}
		FieldInfo* f2 = il2cpp_class_get_field_from_name(base->klass, "isOpen");
		if (f2)
		{
			return !il2cpp_object_get_field_value(base, bool, f2);

		}
	}
	return true;
}
template<typename T> static size_t VectorFind(std::vector<T>& vec, T item)
{
	size_t s = vec.size();
	for (int i = 0; i < s; i++)
	{
		if (vec[i] == item)
		{
			return i;
		}
	}
	return -1;
}
template<typename T> static bool VectorContains(std::vector<T>& vec, T item)
{
	size_t s = vec.size();
	for (int i = 0; i < s; i++)
	{
		if (vec[i] == item)
		{
			return true;
		}
	}
	return false;
}
std::vector<node> GetNodeNeighbors(node TargetNode, Vector2i worldSize, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlockLayer, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer)
{
	std::vector<node> result = {};
	// up
	node u = { TargetNode.x, TargetNode.y + 1 };
	// down
	node d = { TargetNode.x, TargetNode.y - 1 };
	// left
	node l = { TargetNode.x - 1, TargetNode.y };
	// right
	node r = { TargetNode.x + 1, TargetNode.y };

	// up left
	node ul = { TargetNode.x - 1, TargetNode.y + 1 };
	// up right
	node ur = { TargetNode.x + 1, TargetNode.y + 1 };
	// down left
	node dl = { TargetNode.x - 1, TargetNode.y - 1 };
	// down right
	node dr = { TargetNode.x + 1, TargetNode.y - 1 };


	// the s is supposed to mean solid, but it actually means the opposite here
	// if us is true, that means that the block above isn't solid
	bool us = InBounds(u, worldSize) && ((!DoesMapPointHaveColider(u, worldBlockLayer) || !IsDoorLocked(u, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, u, worldSize, worldBlockLayer) || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 656);
	bool ds = InBounds(d, worldSize) && ((!DoesMapPointHaveColider(d, worldBlockLayer) || !IsDoorLocked(d, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, d, worldSize, worldBlockLayer) || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 656);
	bool ls = InBounds(l, worldSize) && ((!DoesMapPointHaveColider(l, worldBlockLayer) || !IsDoorLocked(l, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, l, worldSize, worldBlockLayer) || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 656);
	bool rs = InBounds(r, worldSize) && ((!DoesMapPointHaveColider(r, worldBlockLayer) || !IsDoorLocked(r, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, r, worldSize, worldBlockLayer) || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 656);

	bool uls = InBounds(ul, worldSize) && ((DoesBlockInstaKill(ul, worldBlockLayer) || (!DoesMapPointHaveColider(ul, worldBlockLayer) || !IsDoorLocked(ul, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ul, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 656);
	bool urs = InBounds(ur, worldSize) && ((DoesBlockInstaKill(ur, worldBlockLayer) || (!DoesMapPointHaveColider(ur, worldBlockLayer) || !IsDoorLocked(ur, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ur, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 656);
	bool dls = InBounds(dl, worldSize) && ((DoesBlockInstaKill(dl, worldBlockLayer) || (!DoesMapPointHaveColider(dl, worldBlockLayer) || !IsDoorLocked(dl, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dl, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 656);
	bool drs = InBounds(dr, worldSize) && ((DoesBlockInstaKill(dr, worldBlockLayer) || (!DoesMapPointHaveColider(dr, worldBlockLayer) || !IsDoorLocked(dr, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dr, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 656);

	if (us)
		result.push_back(u);
	if (ds)
	{
		if (GetBlockAtMapPoint(TargetNode, worldBlockLayer).blockType != 110)
			result.push_back(d);
	}
	if (ls)
		result.push_back(l);
	if (rs)
		result.push_back(r);

	if (uls && (us || ls))
		result.push_back(ul);
	if (urs && (us || rs))
		result.push_back(ur);
	if (dls && (ds || ls))
		result.push_back(dl);
	if (drs && (ds || rs))
		result.push_back(dr);



	return result;
}
std::vector<Vector2i> retracePath(node start, node end)
{
	std::vector<Vector2i> path = {};
	node curNode = end;
	while (curNode != start && curNode.parent)
	{
		path.push_back(curNode);
		curNode = *curNode.parent;
	}
	std::reverse(path.begin(), path.end());

	return path;
}
std::vector<Vector2i> FindPath(Vector2i start, Vector2i end, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer)
{
	Vector2i worldSize = { worldBlocks->max_length, worldBlocks->vector[0]->max_length };
	if (start == end)
	{
		return {};
	}
	if (!InBounds(start, worldSize) || !InBounds(end, worldSize))
	{
		return {};
	}
	if (DoesMapPointHaveColider(end, worldBlocks) && !DoesBlockInstaKill(end, worldBlocks) && !DoesBlockHaveColliderOneWay(il2cpp_array_get(il2cpp_array_get(worldBlocks, Il2CppArray*, end.x), LayerBlock, end.y).blockType) && IsDoorLocked(end, worldItemDataLayer))
	{
		return {};
	}

	std::unordered_map<node, bool> closedSet = { };
	std::vector<node> openSet = { start };
	node startNode = start;
	node targetNode = end;
	while (!openSet.empty())
	{
		node curNode = openSet[0];
		int oss = openSet.size();
		for (int i = 1; i < oss; i++)
		{
			float curF = curNode.getFCost();
			float nodeF = openSet[i].getFCost();
			if (nodeF < curF || (nodeF == curF && openSet[i].hCost < curNode.hCost))
			{
				curNode = openSet[i];
			}
		}
		int indx = VectorFind<node>(openSet, curNode);
		if (indx > -1)
			openSet.erase(openSet.begin() + indx);
		closedSet[curNode] = true;
		if (curNode == end)
			return retracePath(start, curNode);

		std::vector<node> nodeNeighbors = GetNodeNeighbors(curNode, worldSize, worldBlocks, worldItemDataLayer);
		for (int i = 0; i < nodeNeighbors.size(); i++)
		{
			node curNodeNeighbor = nodeNeighbors[i];
			if (closedSet[curNodeNeighbor])
				continue;
			int newMoveCost = curNode.gCost + curNode.GetDistance(curNodeNeighbor);
			if (newMoveCost < curNode.gCost || !VectorContains<node>(openSet, curNodeNeighbor))
			{
				curNodeNeighbor.gCost = newMoveCost;
				curNodeNeighbor.hCost = curNodeNeighbor.GetDistance(targetNode);
				if (!VectorContains<node>(openSet, curNodeNeighbor))
				{
					// sex? please never do this again
					node* allocatedNode = (node*)alloca(sizeof(node));
					*allocatedNode = curNode;
					curNodeNeighbor.parent = allocatedNode;
					openSet.push_back(curNodeNeighbor);
				}
			}
		}

	}

	return {};
}
static bool CanSetBlocks(Il2CppObject* pThis, bool isSpeshalWorld, Vector2i/*BasicTypes.Vector2i*/ mapPoint, bool/*System.Boolean*/ checkLimit, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlockLayer)
{
	const static auto WorldController_CanSetCheckByLocks3 = reinterpret_cast<bool(*)(Il2CppObject * pThis, Vector2i/*BasicTypes.Vector2i*/ mapPoint, int/*World.BlockType*/ blockType, bool/*System.Boolean*/ checkLimit)>(Globals::Methods["System.Boolean Assembly-CSharp.WorldController.CanSetCheckByLocks(BasicTypes.Vector2i,World.BlockType,System.Boolean,)"]->methodPointer);
	if (isSpeshalWorld) return true;
	return WorldController_CanSetCheckByLocks3(pThis, mapPoint, GetBlockAtMapPoint(mapPoint, worldBlockLayer).blockType, checkLimit);
}
std::vector<node> GetNodeNeighborsThroughBlocks(node TargetNode, Vector2i worldSize, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlockLayer, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer, Il2CppObject* worldController, bool isSpeshalWorld)
{


	std::vector<node> result = {};
	// up
	node u = { TargetNode.x, TargetNode.y + 1 };
	// down
	node d = { TargetNode.x, TargetNode.y - 1 };
	// left
	node l = { TargetNode.x - 1, TargetNode.y };
	// right
	node r = { TargetNode.x + 1, TargetNode.y };

	// up left
	node ul = { TargetNode.x - 1, TargetNode.y + 1 };
	// up right
	node ur = { TargetNode.x + 1, TargetNode.y + 1 };
	// down left
	node dl = { TargetNode.x - 1, TargetNode.y - 1 };
	// down right
	node dr = { TargetNode.x + 1, TargetNode.y - 1 };


	// the s is supposed to mean solid, but it actually means the opposite here
	// if us is true, that means that the block above isn't solid
	bool us = InBounds(u, worldSize) && (!DoesMapPointHaveColider(u, worldBlockLayer) /*|| !IsDoorLocked(u, worldItemDataLayer))*/ || IsPlatformCanPass(TargetNode, u, worldSize, worldBlockLayer) || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 656);
	bool ds = InBounds(d, worldSize) && (!DoesMapPointHaveColider(d, worldBlockLayer) /*|| !IsDoorLocked(d, worldItemDataLayer))*/ || IsPlatformCanPass(TargetNode, d, worldSize, worldBlockLayer) || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 656);
	bool ls = InBounds(l, worldSize) && (!DoesMapPointHaveColider(l, worldBlockLayer) /*|| !IsDoorLocked(l, worldItemDataLayer))*/ || IsPlatformCanPass(TargetNode, l, worldSize, worldBlockLayer) || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 656);
	bool rs = InBounds(r, worldSize) && (!DoesMapPointHaveColider(r, worldBlockLayer) /*|| !IsDoorLocked(r, worldItemDataLayer))*/ || IsPlatformCanPass(TargetNode, r, worldSize, worldBlockLayer) || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 656);

	bool ub = InBounds(u, worldSize) && ((DoesMapPointHaveColider(u, worldBlockLayer) && CanSetBlocks(worldController, isSpeshalWorld, u, true, worldBlockLayer) && GetBlockAtMapPoint(u, worldBlockLayer).blockType != 3) /*|| !IsDoorLocked(u, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, u, worldSize, worldBlockLayer) || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 656)*/);
	bool db = InBounds(d, worldSize) && ((DoesMapPointHaveColider(d, worldBlockLayer) && CanSetBlocks(worldController, isSpeshalWorld, d, true, worldBlockLayer) && GetBlockAtMapPoint(d, worldBlockLayer).blockType != 3) /*|| !IsDoorLocked(d, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, d, worldSize, worldBlockLayer) || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 656)*/);
	bool lb = InBounds(l, worldSize) && ((DoesMapPointHaveColider(l, worldBlockLayer) && CanSetBlocks(worldController, isSpeshalWorld, l, true, worldBlockLayer) && GetBlockAtMapPoint(l, worldBlockLayer).blockType != 3) /*|| !IsDoorLocked(l, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, l, worldSize, worldBlockLayer) || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 656)*/);
	bool rb = InBounds(r, worldSize) && ((DoesMapPointHaveColider(r, worldBlockLayer) && CanSetBlocks(worldController, isSpeshalWorld, r, true, worldBlockLayer) && GetBlockAtMapPoint(r, worldBlockLayer).blockType != 3) /*|| !IsDoorLocked(r, worldItemDataLayer)) || IsPlatformCanPass(TargetNode, r, worldSize, worldBlockLayer) || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 656)*/);

	//bool uls = InBounds(ul, worldSize) && ((DoesBlockInstaKill(ul, worldBlockLayer) || (!DoesMapPointHaveColider(ul, worldBlockLayer) || !IsDoorLocked(ul, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ul, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 656);
	//bool urs = InBounds(ur, worldSize) && ((DoesBlockInstaKill(ur, worldBlockLayer) || (!DoesMapPointHaveColider(ur, worldBlockLayer) || !IsDoorLocked(ur, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ur, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 656);
	//bool dls = InBounds(dl, worldSize) && ((DoesBlockInstaKill(dl, worldBlockLayer) || (!DoesMapPointHaveColider(dl, worldBlockLayer) || !IsDoorLocked(dl, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dl, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 656);
	//bool drs = InBounds(dr, worldSize) && ((DoesBlockInstaKill(dr, worldBlockLayer) || (!DoesMapPointHaveColider(dr, worldBlockLayer) || !IsDoorLocked(dr, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dr, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 656);



	if (us)
		result.push_back(u);
	else if (ub)
		result.push_back(u);
	if (ds)
	{
		if (GetBlockAtMapPoint(TargetNode, worldBlockLayer).blockType != 110)
			result.push_back(d);
	}
	else if (db)
		result.push_back(d);
	if (ls)
		result.push_back(l);
	else if (lb)
		result.push_back(l);
	if (rs)
		result.push_back(r);
	else if (rb)
		result.push_back(r);
	//if (uls && (us || ls))
	//	result.push_back(ul);
	//if (urs && (us || rs))
	//	result.push_back(ur);
	//if (dls && (ds || ls))
	//	result.push_back(dl);
	//if (drs && (ds || rs))
	//	result.push_back(dr);



	return result;
}
std::vector<Vector2i> FindPathThroughBlocks(Vector2i start, Vector2i end, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer, Il2CppObject* worldController, bool inSpeshialWorld)
{
	const static auto WorldController_CanSetCheckByLocks3 = reinterpret_cast<bool(*)(Il2CppObject * pThis, Vector2i/*BasicTypes.Vector2i*/ mapPoint, int/*World.BlockType*/ blockType, bool/*System.Boolean*/ checkLimit)>(Globals::Methods["System.Boolean Assembly-CSharp.WorldController.CanSetCheckByLocks(BasicTypes.Vector2i,World.BlockType,System.Boolean,)"]->methodPointer);


	Vector2i worldSize = { worldBlocks->max_length, worldBlocks->vector[0]->max_length };
	if (start == end)
	{
		return {};
	}
	if (!InBounds(start, worldSize) || !InBounds(end, worldSize))
	{
		return {};
	}
	if (!CanSetBlocks(worldController, inSpeshialWorld, end, true, worldBlocks))
	{
		return {};
	}

	std::unordered_map<node, bool> closedSet = { };
	std::vector<node> openSet = { start };
	node startNode = start;
	node targetNode = end;
	while (!openSet.empty())
	{
		node curNode = openSet[0];
		int oss = openSet.size();
		for (int i = 1; i < oss; i++)
		{
			float curF = curNode.getFCost();
			float nodeF = openSet[i].getFCost();
			if (nodeF < curF || (nodeF == curF && openSet[i].hCost < curNode.hCost))
			{
				curNode = openSet[i];
			}
		}
		int indx = VectorFind<node>(openSet, curNode);
		if (indx > -1)
			openSet.erase(openSet.begin() + indx);
		closedSet[curNode] = true;
		if (curNode == end)
			return retracePath(start, curNode);

		std::vector<node> nodeNeighbors = GetNodeNeighborsThroughBlocks(curNode, worldSize, worldBlocks, worldItemDataLayer, worldController, inSpeshialWorld);
		for (int i = 0; i < nodeNeighbors.size(); i++)
		{
			node curNodeNeighbor = nodeNeighbors[i];
			if (closedSet[curNodeNeighbor])
				continue;
			int newMoveCost = curNode.gCost + curNode.GetDistance(curNodeNeighbor) + GetBlockAtMapPoint(curNodeNeighbor, worldBlocks).hitsRequired / 500;
			if (newMoveCost < curNode.gCost || !VectorContains<node>(openSet, curNodeNeighbor))
			{
				curNodeNeighbor.gCost = newMoveCost;
				curNodeNeighbor.hCost = curNodeNeighbor.GetDistance(targetNode);
				if (!VectorContains<node>(openSet, curNodeNeighbor))
				{
					// sex? please never do this again
					// too late i did it again!! :)))))))))))
					node* allocatedNode = (node*)alloca(sizeof(node));
					*allocatedNode = curNode;
					curNodeNeighbor.parent = allocatedNode;
					openSet.push_back(curNodeNeighbor);
				}
			}
		}

	}

	return {};
}

std::vector<node> GetNodeNeighborsInNether(node TargetNode, Vector2i worldSize, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlockLayer, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer)
{
	std::vector<node> result = {};
	// up
	node u = { TargetNode.x, TargetNode.y + 1 };
	// down
	node d = { TargetNode.x, TargetNode.y - 1 };
	// left
	node l = { TargetNode.x - 1, TargetNode.y };
	// right
	node r = { TargetNode.x + 1, TargetNode.y };

	// up left
	node ul = { TargetNode.x - 1, TargetNode.y + 1 };
	// up right
	node ur = { TargetNode.x + 1, TargetNode.y + 1 };
	// down left
	node dl = { TargetNode.x - 1, TargetNode.y - 1 };
	// down right
	node dr = { TargetNode.x + 1, TargetNode.y - 1 };


	// the s is supposed to mean solid, but it actually means the opposite here
	// if us is true, that means that the block above isn't solid
	bool us = InBounds(u, worldSize) && ((!DoesMapPointHaveColider(u, worldBlockLayer) || !IsDoorLocked(u, worldItemDataLayer)) || IsPlatformCanPassNether(TargetNode, u, worldSize, worldBlockLayer) || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(u, worldBlockLayer).blockType == 656);
	bool ds = InBounds(d, worldSize) && ((!DoesMapPointHaveColider(d, worldBlockLayer) || !IsDoorLocked(d, worldItemDataLayer)) || IsPlatformCanPassNether(TargetNode, d, worldSize, worldBlockLayer) || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(d, worldBlockLayer).blockType == 656);
	bool ls = InBounds(l, worldSize) && ((!DoesMapPointHaveColider(l, worldBlockLayer) || !IsDoorLocked(l, worldItemDataLayer)) || IsPlatformCanPassNether(TargetNode, l, worldSize, worldBlockLayer) || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(l, worldBlockLayer).blockType == 656);
	bool rs = InBounds(r, worldSize) && ((!DoesMapPointHaveColider(r, worldBlockLayer) || !IsDoorLocked(r, worldItemDataLayer)) || IsPlatformCanPassNether(TargetNode, r, worldSize, worldBlockLayer) || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(r, worldBlockLayer).blockType == 656);

	//bool uls = InBounds(ul, worldSize) && ((DoesBlockInstaKill(ul, worldBlockLayer) || (!DoesMapPointHaveColider(ul, worldBlockLayer) || !IsDoorLocked(ul, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ul, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ul, worldBlockLayer).blockType == 656);
	//bool urs = InBounds(ur, worldSize) && ((DoesBlockInstaKill(ur, worldBlockLayer) || (!DoesMapPointHaveColider(ur, worldBlockLayer) || !IsDoorLocked(ur, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, ur, worldSize, worldBlockLayer) || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(ur, worldBlockLayer).blockType == 656);
	//bool dls = InBounds(dl, worldSize) && ((DoesBlockInstaKill(dl, worldBlockLayer) || (!DoesMapPointHaveColider(dl, worldBlockLayer) || !IsDoorLocked(dl, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dl, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dl, worldBlockLayer).blockType == 656);
	//bool drs = InBounds(dr, worldSize) && ((DoesBlockInstaKill(dr, worldBlockLayer) || (!DoesMapPointHaveColider(dr, worldBlockLayer) || !IsDoorLocked(dr, worldItemDataLayer))) || IsPlatformCanPass(TargetNode, dr, worldSize, worldBlockLayer) || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 956 || GetBlockAtMapPoint(dr, worldBlockLayer).blockType == 656);

	if (us)
		result.push_back(u);
	if (ds)
	{
		if (GetBlockAtMapPoint(TargetNode, worldBlockLayer).blockType != 110)
			result.push_back(d);
	}
	if (ls)
		result.push_back(l);
	if (rs)
		result.push_back(r);

	//if (uls && (us || ls))
	//	result.push_back(ul);
	//if (urs && (us || rs))
	//	result.push_back(ur);
	//if (dls && (ds || ls))
	//	result.push_back(dl);
	//if (drs && (ds || rs))
	//	result.push_back(dr);



	return result;
}
std::vector<Vector2i> FindPathThroughNether(Vector2i start, Vector2i end, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks, Il2CppArrayT<Il2CppArrayT<WorldItemBase*>*>* worldItemDataLayer)
{
	Vector2i worldSize = { worldBlocks->max_length, worldBlocks->vector[0]->max_length };
	if (start == end)
	{
		return {};
	}
	if (!InBounds(start, worldSize) || !InBounds(end, worldSize))
	{
		return {};
	}
	if (DoesMapPointHaveColider(end, worldBlocks) && !DoesBlockInstaKill(end, worldBlocks) && !DoesBlockHaveColliderOneWay(il2cpp_array_get(il2cpp_array_get(worldBlocks, Il2CppArray*, end.x), LayerBlock, end.y).blockType) && IsDoorLocked(end, worldItemDataLayer))
	{
		return {};
	}

	std::unordered_map<node, bool> closedSet = { };
	std::vector<node> openSet = { start };
	node startNode = start;
	node targetNode = end;
	while (!openSet.empty())
	{
		node curNode = openSet[0];
		int oss = openSet.size();
		for (int i = 1; i < oss; i++)
		{
			float curF = curNode.getFCost();
			float nodeF = openSet[i].getFCost();
			if (nodeF < curF || (nodeF == curF && openSet[i].hCost < curNode.hCost))
			{
				curNode = openSet[i];
			}
		}
		int indx = VectorFind<node>(openSet, curNode);
		if (indx > -1)
			openSet.erase(openSet.begin() + indx);
		closedSet[curNode] = true;
		if (curNode == end)
			return retracePath(start, curNode);

		std::vector<node> nodeNeighbors = GetNodeNeighborsInNether(curNode, worldSize, worldBlocks, worldItemDataLayer);
		for (int i = 0; i < nodeNeighbors.size(); i++)
		{
			node curNodeNeighbor = nodeNeighbors[i];
			if (closedSet[curNodeNeighbor])
				continue;
			int newMoveCost = curNode.gCost + curNode.GetDistance(curNodeNeighbor);
			if (newMoveCost < curNode.gCost || !VectorContains<node>(openSet, curNodeNeighbor))
			{
				curNodeNeighbor.gCost = newMoveCost;
				curNodeNeighbor.hCost = curNodeNeighbor.GetDistance(targetNode);
				if (!VectorContains<node>(openSet, curNodeNeighbor))
				{
					// sex? please never do this again
					node* allocatedNode = (node*)alloca(sizeof(node));
					//memcpy(allocatedNode, &curNode, sizeof(node));
					*allocatedNode = curNode;
					curNodeNeighbor.parent = allocatedNode;
					openSet.push_back(curNodeNeighbor);
				}
			}
		}

	}

	return {};
}
std::vector<Vector2i> FindPathDown(Vector2i point, Il2CppArrayT<Il2CppArrayT<LayerBlock>*>* worldBlocks)
{
	Vector2i worldSize = { worldBlocks->max_length, worldBlocks->vector[0]->max_length };
	std::vector<Vector2i> result = {};
	while (true)
	{
		if (InBounds(point, worldSize) && !DoesMapPointHaveColider(point, worldBlocks))
		{
			result.push_back(point);
		}
		else
			break;
		point.y--;
	}
	return result;
}
void SetupPathfinding()
{
	ConfigData_doesBlockHaveCollider = il2cpp_object_get_field_value_static_by_name((Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"]->static_fields, Il2CppArrayT<bool>*, (Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"], "doesBlockHaveCollider");// Il2Cpp::Helpers::GetStaticFieldValue<Il2CppArray*>(il2cpp_class_get_field_from_name((Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"], "doesBlockHaveCollider"));
	ConfigData_doesBlockHaveColliderOneWay = il2cpp_object_get_field_value_static_by_name((Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"]->static_fields, Il2CppArrayT<bool>*, (Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"], "isBlockColliderOneWay");;//Il2Cpp::Helpers::GetStaticFieldValue<Il2CppArray*>(il2cpp_class_get_field_from_name((Il2CppClass*)Globals::Classes["Assembly-CSharp.ConfigData"], "isBlockColliderOneWay"));
}