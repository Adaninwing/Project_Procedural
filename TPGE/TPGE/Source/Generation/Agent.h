#pragma once

/// includes
#include <memory>
#include <string>

/// header
#include "Engine/TPGEObject.h"

/// library includes
#include "Model/AgentType.h"
#include "Model/Edge.h"
#include "Util/IndexedMap.h"
#include "Util/NArray.h"
#include "Util/Variant.h"

namespace TPGE {

	/// forward declarations
	class GeneratedNode;
	class TechniqueBase;
	class TPGEContext;

	/// enum for the agent's state
	enum AgentState { 
		AS_UNSTARTED, 
		AS_RUNNING,
		AS_FINISHING,
		AS_FINISHED 
	};

	class Agent : public TPGEObject
	{
	public:
		TPGE_OBJECT(Agent, TPGEObject)

		Agent(std::shared_ptr<TPGEContext> context);
		~Agent();

		/// Add a variable to be used
		void AddDataVariable(std::string name, std::shared_ptr<NArray<Variant> > var);
		/// Add a variable to be used
		void AddEdgeVariable(std::string name, std::shared_ptr<Variant> var);
		/// Add a variable to be used
		void AddNodeVariable(std::string name, std::shared_ptr<Variant> var);
		/// Add a technique constant
		void AddTechniqueConstant(unsigned index, std::string name, std::shared_ptr<Variant> constant);
		/// Add a technique constant
		void AddTechniqueConstant(unsigned index, std::shared_ptr<Variant> constant);
		/// Add a technique constant
		void AddTechniqueConstant(std::string name, std::shared_ptr<Variant> constant);
		/// Execute a technique call step
		void ExecuteStep(std::shared_ptr<TechniqueBase> technique);

		/// Get the agent type
		AgentType GetAgentType() const { return agentType_; };
		/// Get a variable by name
		std::shared_ptr<NArray<Variant> > GetDataVariable(std::string name) { return dataVariables_[name]; }
		/// Get the edge type of the generated edges
		EdgeType GetEdgeType() const { return edgeType_; };
		/// Set the mask
		std::shared_ptr<NArray<Variant> > GetMask() { return mask_; }
		/// Get the value taken as mask parameter
		std::shared_ptr<Variant> GetMaskValue() const { return maskValue_; };
		/// Get the name of the agent
		std::string& GetName() const { return const_cast<std::string&>(name_); }
		/// Get the pointer to the nodes to generate
		std::shared_ptr<IndexedMap<GeneratedNode> > GetNodes() { return nodes_; };
		/// Get a technique constant
		std::shared_ptr<Variant> GetTechniqueConstant(unsigned index) { return techniqueConstants_[index]; }
		/// Get a technique constant
		std::shared_ptr<Variant> GetTechniqueConstant(std::string name) { return techniqueConstants_[name]; }
		/// Get the number of tokens left
		unsigned GetTokens() const { return tokens_; }
		/// Get the name of the agent
		bool IsFinished() const { return state_ == AS_FINISHED; }

		/// Get the agent type
		void SetAgentType(AgentType type) { agentType_ = type; };
		/// Set the edge type of the generated edges
		void SetEdgeType(EdgeType edgeType) { edgeType_ = edgeType; };
		/// Set the mask
		void SetMask(std::shared_ptr<NArray<Variant> > mask) { mask_ = mask; }
		/// Get the value taken as mask parameter
		void SetMaskValue(std::shared_ptr<Variant> value) { maskValue_ = value; };
		/// Set the name of the agent
		void SetName(const std::string& name) { name_ = name; }
		/// Set the pointer to the nodes to generate
		void SetNodes(std::shared_ptr<IndexedMap<GeneratedNode> > nodes) { nodes_ = nodes; };
		/// Get the number of tokens left
		void SetTokens(unsigned tokens) { tokens_ = tokens; }

	private:
		/// Get the next possible position of the cursor
		size_t GetNextCursorPosition(bool first = false);

		/// the agent type
		AgentType agentType_;
		/// the current position of the cursor
		size_t cursor_;
		/// The data variables to fill
		IndexedMap<NArray<Variant> > dataVariables_;
		/// The edge type of the generated edges
		EdgeType edgeType_;
		/// The edge variables to fill
		IndexedVariantMap edgeVariables_;
		/// The mask to use
		std::shared_ptr<NArray<Variant> > mask_;
		/// The mask variable
		std::shared_ptr<Variant> maskValue_;
		/// the name of the agent
		std::string name_;
		/// a pointer to the nodes to generate
		std::shared_ptr<IndexedMap<GeneratedNode> > nodes_;
		/// The node variables to fill
		IndexedVariantMap nodeVariables_;
		/// flag to signal if the agent's state
		AgentState state_;
		/// the constants of the technique to execute
		IndexedVariantMap techniqueConstants_;
		/// the number of tokens left
		unsigned tokens_;

	};
}
