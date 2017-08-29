// includes
#include <vector>
#include <algorithm>

// header
#include "GeneratedGraph.h"

// library includes
#include "Engine/TPGEContext.h"
#include "GeneratedData.h"
#include "GeneratedNode.h"
#include "Generation/ModelGenerator.h"

namespace TPGE
{
	//===============================================================
	// O P E R A T O R
	//===============================================================
	bool GeneratedGraph::operator==(const GeneratedGraph& other) const
	{
		return parent_ == other.GetParentConst() && GetNumChildren() == other.GetNumChildren() && name_ == other.GetName();
	}
	
	bool GeneratedGraph::operator!=(const GeneratedGraph& other) const
	{
		return !(*this == other);
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	GeneratedGraph::GeneratedGraph(std::shared_ptr<TPGEContext> context) :
		Attributed(context)
	{
		Initialize();
	}

	GeneratedGraph::~GeneratedGraph()
	{

	}

	void GeneratedGraph::AddChild(unsigned index, std::string name, std::shared_ptr<GeneratedGraph> graph)
	{
		children_.Insert(index, name, graph);
	}
	
	void GeneratedGraph::AddChild(unsigned index, std::shared_ptr<GeneratedGraph> graph)
	{
		children_.Insert(index, graph);
	}
	
	void GeneratedGraph::AddChild(std::string name, std::shared_ptr<GeneratedGraph> graph)
	{
		children_.Insert(name, graph);
	}

	void GeneratedGraph::AddData(unsigned index, std::string name, std::shared_ptr<GeneratedData> data)
	{
		data_.Insert(index, name, data);
	}
	
	void GeneratedGraph::AddData(unsigned index, std::shared_ptr<GeneratedData> data)
	{
		data_.Insert(index, data);
	}
	
	void GeneratedGraph::AddData(std::string name, std::shared_ptr<GeneratedData> data)
	{
		data_.Insert(name, data);
	}
	
	void GeneratedGraph::AddNode(unsigned index, std::string name, std::shared_ptr<GeneratedNode> node)
	{
		nodes_.Insert(index, name, node);
	}
	
	void GeneratedGraph::AddNode(unsigned index, std::shared_ptr<GeneratedNode> node)
	{
		nodes_.Insert(index, node);
	}
	
	void GeneratedGraph::AddNode(std::string name, std::shared_ptr<GeneratedNode> node)
	{
		nodes_.Insert(name, node);
	}

	void GeneratedGraph::ClearChildren()
	{
		children_.Clear();
	}

	void GeneratedGraph::ClearData()
	{
		data_.Clear();
	}

	void GeneratedGraph::ClearNodes()
	{
		std::shared_ptr<GeneratedNode> node;
		for (IndexedMap<GeneratedNode>::Iterator it = nodes_.Begin(); it != nodes_.End(); it++)
		{
			node = it->second;
			node->ClearEdges();
		}
		nodes_.Clear();
	}

	void GeneratedGraph::Initialize()
	{
		
	}
	
	bool GeneratedGraph::RemoveChild(unsigned index)
	{
		return children_.Erase(index);
	}
	
	bool GeneratedGraph::RemoveChild(std::string name)
	{
		return children_.Erase(name);
	}

	bool GeneratedGraph::RemoveData(unsigned index)
	{
		return data_.Erase(index);
	}
	
	bool GeneratedGraph::RemoveData(std::string name)
	{
		return data_.Erase(name);
	}

	bool GeneratedGraph::RemoveNode(unsigned index)
	{
		std::shared_ptr<GeneratedNode> node = nodes_.At(index);
		if(node)
		{
			node->ClearEdges();
			return nodes_.Erase(index);
		}
		else return false;
	}
	
	bool GeneratedGraph::RemoveNode(std::string name)
	{
		std::shared_ptr<GeneratedNode> node = nodes_.Get(name);
		if (node)
		{
			node->ClearEdges();
			return nodes_.Erase(name);
		}
		else return false;
	}
	
	void GeneratedGraph::RemoveParent()
	{
		parent_ = nullptr;
	}

	std::shared_ptr<GeneratedGraph> GeneratedGraph::GetChild(unsigned index)
	{
		std::shared_ptr<GeneratedGraph> retVal = children_[index];
		if (!retVal)
		{
			std::deque<unsigned> temp = GetPathUnsigned();
			std::vector<unsigned> indices;
			std::copy(temp.begin(), temp.end(), std::back_inserter(indices));
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			retVal = generator->GetGeneratedGraph(indices);
			AddChild(retVal->GetIndex(), retVal->GetName(), retVal);
		}
		return retVal;
	}
	
	std::shared_ptr<GeneratedGraph> GeneratedGraph::GetChild(std::string name)
	{
		std::shared_ptr<GeneratedGraph> retVal = children_[name];
		if (!retVal)
		{
			std::deque<std::string> temp = GetPathString();
			std::vector<std::string> names;
			std::copy(temp.begin(), temp.end(), std::back_inserter(names));
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			retVal = generator->GetGeneratedGraph(names);
			AddChild(retVal->GetIndex(), retVal->GetName(), retVal);
		}
		return retVal;
	}

	std::shared_ptr<GeneratedData> GeneratedGraph::GetData(unsigned index)
	{
		std::shared_ptr<GeneratedData> retVal = data_[index];
		if (!retVal)
		{
			std::deque<unsigned> temp = GetPathUnsigned();
			std::vector<unsigned> indices;
			std::copy(temp.begin(), temp.end(), std::back_inserter(indices));
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			retVal = generator->GetGeneratedData(indices, index);
			AddData(index, retVal->GetName(), retVal);
		}
		return retVal;
	}
	
	std::shared_ptr<GeneratedData> GeneratedGraph::GetData(std::string name)
	{
		std::shared_ptr<GeneratedData> retVal = data_[name];
		if (!retVal)
		{
			std::deque<unsigned> temp = GetPathUnsigned();
			std::vector<unsigned> indices;
			std::copy(temp.begin(), temp.end(), std::back_inserter(indices));
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			retVal = generator->GetGeneratedData(indices, name);
			AddData(retVal->GetIndex(), name, retVal);
		}
		return retVal;
	}

	std::deque<std::string> GeneratedGraph::GetPathString()
	{
		if (parent_)
		{
			std::deque<std::string> ret = parent_->GetPathString();
			ret.push_front(name_);
			return ret;
		}
		else
		{
			return { name_ };
		}
	}

	std::deque<unsigned> GeneratedGraph::GetPathUnsigned()
	{
		if (parent_)
		{
			std::deque<unsigned> ret = parent_->GetPathUnsigned();
			ret.push_front(index_);
			return ret;
		}
		else
		{
			return { index_ };
		}
	}

	std::shared_ptr<GeneratedNode> GeneratedGraph::GetNode(unsigned index)
	{
		std::shared_ptr<GeneratedNode> retVal = nodes_[index];
		if (!retVal)
		{
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			generator->GenerateNodes(this);
			retVal = nodes_[index];
		}
		return retVal;
	}

	std::shared_ptr<GeneratedNode> GeneratedGraph::GetNode(std::string name)
	{
		std::shared_ptr<GeneratedNode> retVal = nodes_[name];
		if (!retVal)
		{
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			generator->GenerateNodes(this);
			retVal = nodes_[name];
		}
		return retVal;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
}