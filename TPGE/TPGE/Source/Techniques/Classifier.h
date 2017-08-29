#pragma once

/// includes
#include <set>

/// base class
#include "TechniqueBase.h"

/// library includes
#include "Util/NArray.h"

namespace TPGE
{
	/// forward declaration
	class Agent;

	class Classifier : public TechniqueBase
	{
	public:
		TPGE_OBJECT(Classifier, TechniqueBase)

		Classifier(std::shared_ptr<TPGEContext> context);
		~Classifier();

		/// Bind the agent processing constants and values
		virtual void BindAgent(std::shared_ptr<Agent> agent);
		/// initialize all constants
		virtual void InitializeConstants();
		/// process a data point
		virtual void ProcessDataPoint(unsigned processIndex);
		/// process a node, return: true if finished otherwise false
		virtual bool ProcessNode(std::shared_ptr<GeneratedNode> node, EdgeType edgeType);
		/// start technique execution
		virtual void Start();
		/// stop technique execution
		virtual void Stop();

	protected:

	private:
		/// the different classes that exist
		std::set<Variant> classes_;
		/// the Value structure
		std::shared_ptr<NArray<Variant> > values_;
		/// Variant type stored for efficiency
		int whichType_;
	};
}
