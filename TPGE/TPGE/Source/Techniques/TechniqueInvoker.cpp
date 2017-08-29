// header
#include "TechniqueInvoker.h"

// library includes
#include "Classifier.h"
#include "Generation/Pass.h"
#include "Noise.h"
#include "Quantization.h"
#include "TechniqueBase.h"
#include "Util/Variant.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	TechniqueInvoker::TechniqueInvoker(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context)
	{
		InitializeTechniques();
	}

	TechniqueInvoker::~TechniqueInvoker()
	{

	}

	void TechniqueInvoker::ExecutePass(std::shared_ptr<Pass> pass)
	{
		// for now execute passes individually
		std::shared_ptr<Agent> agent;
		std::shared_ptr<Variant> techniqueConstant;
		std::shared_ptr<TechniqueBase> technique;
		std::vector<std::shared_ptr<TechniqueBase> > techniques;
		for (unsigned i = 0; i < pass->agents_.size(); i++)
		{
			agent = pass->agents_[i];

			// first get the technique type to use, if none given, or technique not found -> abbort
			techniqueConstant = agent->GetTechniqueConstant("Type");
			if (!techniqueConstant)
			{
				techniques.push_back(nullptr);
				continue;
			}
			technique = GetTechnique(techniqueConstant->GetString());
			if (!technique)
			{
				techniques.push_back(nullptr);
				continue;
			}

			technique->BindAgent(agent);
			techniques.push_back(technique);
		}

		// exectue untill agents are done
		while (!AllAgentsDone(pass->agents_))
		{
			for (unsigned i = 0; i < pass->agents_.size(); i++)
			{
				pass->agents_[i]->ExecuteStep(techniques[i]);
			}
		}
	}

	std::shared_ptr<TechniqueBase> TechniqueInvoker::GetTechnique(const std::string& techniqueName)
	{
		TechniqueBase* instance = nullptr;

		// find name in the registry and call factory method. 
		auto it = techniquesRegistry_.find(techniqueName);
		if (it != techniquesRegistry_.end())
			instance = it->second(context_);

		instance->InitializeConstants();

		// wrap instance in a shared ptr and return
		if (instance != nullptr)
			return std::shared_ptr<TechniqueBase>(instance);
		else
			return nullptr;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	bool TechniqueInvoker::AllAgentsDone(std::vector<std::shared_ptr<Agent> >& agents)
	{
		bool ret = true;
		for (unsigned i = 0; i < agents.size(); i++)
			ret &= agents[i]->IsFinished();
		return ret;
	}

	void TechniqueInvoker::InitializeTechniques()
	{
		RegisterTechnique<Classifier>("Classifier");
		RegisterTechnique<Noise>("Noise");
		RegisterTechnique<Quantization>("Quantization");
	}

}