// includes
#include <set>

// header
#include "Classifier.h"

// library includes
#include "Generation/Agent.h"
#include "Model/Generated/GeneratedEdge.h"
#include "Model/Generated/GeneratedNode.h"

namespace TPGE
{
	/// the variables used by the technique
	const std::string _variables[2]{
		"class",
		"values"
	};

	//===============================================================
	// G L O B A L
	//===============================================================
	
	//===============================================================
	// P U B L I C
	//===============================================================
	Classifier::Classifier(std::shared_ptr<TPGEContext> context) :
		TechniqueBase(context),
		whichType_(3)
	{

	}

	Classifier::~Classifier()
	{
	}

	void Classifier::BindAgent(std::shared_ptr<Agent> agent)
	{
		// parse initialization
		TPGE_PARSE_INIT;

		// parse all attributes
		// -

		// bind the variable
		values_ = agent->GetDataVariable(_variables[1]);
		whichType_ = values_->GetElement(0).Which();
	}

	void Classifier::InitializeConstants()
	{
		// initialize base
		TPGE_INITIALIZE_TECHNIQUE_BASE(TechniqueBase);

		// initialize new members
		// -
	}

	void Classifier::ProcessDataPoint(unsigned processIndex)
	{
		/// nothing to do since not a data technique
	}

	bool Classifier::ProcessNode(std::shared_ptr<GeneratedNode> node, EdgeType edgeType)
	{
		auto it = classes_.begin();
		node->SetName("Class " + it->GetString());
		node->GetAttribute(_variables[0])->Set(*it);

		classes_.erase(it);
		return classes_.size() == 0;
	}

	void Classifier::Start()
	{
		TechniqueBase::Start();

		// Get number of different classes in the values list
		for (size_t i = 0; i < values_->GetLength(); i++)
			classes_.insert(values_->operator[](i));

	}

	void Classifier::Stop()
	{
		TechniqueBase::Stop();
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================


}