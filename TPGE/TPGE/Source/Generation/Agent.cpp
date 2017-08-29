// includes
#include <limits>

// header
#include "Agent.h"

// library includes
#include "Engine/TPGEContext.h"
#include "Model/Generated/GeneratedEdge.h"
#include "Model/Generated/GeneratedNode.h"
#include "Techniques/TechniqueBase.h"

namespace TPGE
{
	//===============================================================
	// P U B L I C
	//===============================================================
	Agent::Agent(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context),
		agentType_(AgentType::SINGULAR),
		cursor_(0),
		edgeType_(EdgeType::UNDIRECTED),
		name_(""),
		state_(AS_UNSTARTED),
		tokens_(std::numeric_limits<unsigned>::max())
	{
	}

	Agent::~Agent()
	{

	}

	void Agent::AddDataVariable(std::string name, std::shared_ptr<NArray<Variant> > var)
	{
		dataVariables_.Insert(dataVariables_.Size(), name, var);
	}

	void Agent::AddEdgeVariable(std::string name, std::shared_ptr<Variant> var)
	{
		edgeVariables_.Insert(edgeVariables_.Size(), name, var);
	}

	void Agent::AddNodeVariable(std::string name, std::shared_ptr<Variant> var)
	{
		nodeVariables_.Insert(nodeVariables_.Size(), name, var);
	}

	void Agent::AddTechniqueConstant(unsigned index, std::string name, std::shared_ptr<Variant> constant)
	{
		techniqueConstants_.Insert(index, name, constant);
	}
	
	void Agent::AddTechniqueConstant(unsigned index, std::shared_ptr<Variant> constant)
	{
		techniqueConstants_.Insert(index, constant);
	}
	
	void Agent::AddTechniqueConstant(std::string name, std::shared_ptr<Variant> constant)
	{
		techniqueConstants_.Insert(name, constant);
	}

	void Agent::ExecuteStep(std::shared_ptr<TechniqueBase> technique)
	{
		// general termination criteria
		if (!technique)
		{
			state_ = AS_FINISHED;
			return;
		}
		else
		{
			bool finished = false;
			switch (state_)
			{
			case AS_UNSTARTED:
				technique->Start();
				if (agentType_ != AgentType::GRAPH)
				{
					cursor_ = GetNextCursorPosition(true);
				}
				state_ = AS_RUNNING;
				break;
			case AS_RUNNING:
				if (agentType_ != AgentType::GRAPH)
				{
					technique->ProcessDataPoint(cursor_);
					cursor_ = GetNextCursorPosition();
				}
				else
				{
					std::shared_ptr<GeneratedNode> node = std::make_shared<GeneratedNode>(context_);
					node->SetIndex(nodes_->Size());
					node->SetName("Node" + std::to_string(nodes_->Size()));
					for (IndexedVariantMap::Iterator it = nodeVariables_.Begin(); it != nodeVariables_.End(); it++)
					{
						node->AddAttribute(it->first.id_, it->first.key_, Variant(*it->second));
					}
					finished = technique->ProcessNode(node, edgeType_);
					nodes_->Insert(node->GetIndex(), node->GetName(), node);
				}
				tokens_--;
				// only need to check first variable as all have to be the same length
				if (cursor_ >= dataVariables_.Begin()->second->GetLength() || tokens_ == 0 || finished)
					state_ = AS_FINISHING;
				break;
			case AS_FINISHING:
				technique->Stop();
				state_ = AS_FINISHED;
				break;
			default:
				break;
			}
		}
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	size_t Agent::GetNextCursorPosition(bool first)
	{
		size_t ret = cursor_;
		switch (agentType_)
		{
		case SINGULAR:
			if (!first)
				ret++;
			break;
		case MASKED:
			for (ret = first ? 0 : cursor_ + 1; ret < mask_->GetLength(); ret++)
			{
				if (mask_->GetElement(ret) == *maskValue_)
					break;
			}
			break;
		default:
			break;
		}

		return ret;
	}
}