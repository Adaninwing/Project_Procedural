#pragma once

/// includes
#include <vector>

/// base class
#include "TechniqueBase.h"

/// library includes
#include "Util/NArray.h"

namespace TPGE
{
	enum QuantizationAlgorithm {
		Uniform = 0,
	};
	QuantizationAlgorithm GetQuantizationAlgorithmType(std::string type);

	enum QuantizationRegionValue {
		Minimum = 0,
		Average = 1,
		Maximum = 2,
	};
	QuantizationRegionValue GetQuantizationRegionValue(std::string type);

	/// forward declaration
	class Agent;

	class Quantization : public TechniqueBase
	{
	public:
		TPGE_OBJECT(Quantization, TechniqueBase)

		Quantization(std::shared_ptr<TPGEContext> context);
		~Quantization();

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
		/// setup the regions for Uniform algorithm
		void SetupRegions();

		/// Quanify a value
		void GetValue(Variant& var);
		/// Quanify a value according to uniform algorithm
		void GetValueFromRegion(Variant& var);

		/// The regions' lower bound
		std::vector<float> regionMax_;
		/// The regions' upper bound
		std::vector<float> regionMin_;
		/// The regions' values
		std::vector<float> regionValue_;
		/// the Value structure
		std::shared_ptr<NArray<Variant> > value_;
		/// Variant type stored for efficiency
		int whichType_;
	};
}
