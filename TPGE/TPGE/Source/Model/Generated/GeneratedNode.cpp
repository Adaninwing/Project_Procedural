// library includes
#include "GeneratedEdge.h"

// header
#include "GeneratedNode.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	GeneratedNode::GeneratedNode(std::shared_ptr<TPGEContext> context) :
		Attributed(context)
	{

	}

	GeneratedNode::~GeneratedNode()
	{

	}

	void GeneratedNode::AddEdge(unsigned index, std::string name, std::shared_ptr<GeneratedEdge> edge)
	{
		edges_.Insert(index, name, edge);
	}

	void GeneratedNode::AddEdge(unsigned index, std::shared_ptr<GeneratedEdge> edge)
	{
		edges_.Insert(index, edge);
	}

	void GeneratedNode::AddEdge(std::string name, std::shared_ptr<GeneratedEdge> edge)
	{
		edges_.Insert(name, edge);
	}

	bool GeneratedNode::RemoveEdge(unsigned index)
	{
		std::shared_ptr<GeneratedEdge> edge = edges_.At(index);
		if (edge)
		{
			if (edge->GetLeft().get() == this) edge->SetLeft(nullptr);
			else if (edge->GetRight().get() == this) edge->SetRight(nullptr);
			return edges_.Erase(index);
		}
		else return false;
	}

	bool GeneratedNode::RemoveEdge(std::string name)
	{
		std::shared_ptr<GeneratedEdge> edge = edges_.Get(name);
		if (edge)
		{
			if (edge->GetLeft().get() == this) edge->SetLeft(nullptr);
			else if (edge->GetRight().get() == this) edge->SetRight(nullptr);
			return edges_.Erase(name);
		}
		else return false;
	}

	void GeneratedNode::ClearEdges()
	{
		std::shared_ptr<GeneratedEdge> edge;
		for (IndexedMap<GeneratedEdge>::Iterator it = edges_.Begin(); it != edges_.End(); it++)
		{
			edge = it->second;
			if (edge->GetLeft().get() == this) edge->SetLeft(nullptr);
			else if (edge->GetRight().get() == this) edge->SetRight(nullptr);
		}
		edges_.Clear();
	}

	std::shared_ptr<GeneratedEdge> GeneratedNode::GetEdge(unsigned index)
	{
		return edges_[index];
	}

	std::shared_ptr<GeneratedEdge> GeneratedNode::GetEdge(std::string name)
	{
		return edges_[name];
	}


	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}