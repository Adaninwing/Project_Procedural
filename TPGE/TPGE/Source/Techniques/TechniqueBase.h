#pragma once

/// includes
#include <string>

/// Library includes
#include "Engine/TPGEObject.h"
#include "Model/Edge.h"
#include "Util/IndexedMap.h"

/// defines
#define TPGE_INITIALIZE_TECHNIQUE_BASE(baseClass)										\
	baseClass::InitializeConstants();													\
	Variant var;																		\
	using namespace std
#define TPGE_INITIALIZE_TECHNIQUE_CONSTANT(index, string, type, initValue)				\
	var = Variant(#type);																\
	var.Set<type>(initValue);															\
	constantAttributesMap_.Insert(index, string, var)
#define TPGE_PARSE_INIT																	\
	using namespace std;																\
	std::shared_ptr<Variant> var;														\
	std::shared_ptr<Variant> gotten;
#define TPGE_PARSE_CONSTANT(agent, string, type)										\
	var = agent->GetTechniqueConstant(string);											\
	if (var) {																			\
		gotten = constantAttributesMap_[string];										\
		type value = var->Get<type>();													\
		gotten->Set(value);																\
	}

namespace TPGE
{
	/// forward declarations
	class Agent;
	class GeneratedNode;

	class TechniqueBase : public TPGEObject
	{
	public:
		TPGE_BASE_OBJECT(TechniqueBase)

		TechniqueBase(std::shared_ptr<TPGEContext> context);
		~TechniqueBase();

		/// Bind the agent processing constants and values
		virtual void BindAgent(std::shared_ptr<Agent> agent) = 0;
		/// initialize all constants
		virtual void InitializeConstants();
		/// process a data point
		virtual void ProcessDataPoint(unsigned processIndex) = 0;
		/// process a node, return: true if finished otherwise false
		virtual bool ProcessNode(std::shared_ptr<GeneratedNode> node, EdgeType edgeType) = 0;
		/// start technique execution
		virtual void Start();
		/// stop technique execution
		virtual void Stop();

		/// set a constnts value returns false if types don't match or no constant is found
		bool SetConstant(std::string key, const Variant& attr);
		/// set a constnts value returns false if types don't match or no constant is found
		bool SetConstant(int index, const Variant& attr);

	protected:
		/// a map of constant attributes
		IndexedVariantMap constantAttributesMap_;
	private:
	};
}