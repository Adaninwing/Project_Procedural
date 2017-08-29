// includes

// header
#include "Quantization.h"

// library includes
#include "Generation/Agent.h"
#include "Model/Generated/GeneratedNode.h"

namespace TPGE
{
	/// the variables used by the technique
	const std::string _variables[1]{
		"value"
	};

	//===============================================================
	// G L O B A L
	//===============================================================
	QuantizationAlgorithm GetQuantizationAlgorithmType(std::string type)
	{
		std::map<std::string, QuantizationAlgorithm> _map = std::map<std::string, QuantizationAlgorithm>();
		_map.insert(std::make_pair("Uniform", QuantizationAlgorithm::Uniform));

		auto it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return QuantizationAlgorithm::Uniform;
		}
	}

	QuantizationRegionValue GetQuantizationRegionValue(std::string type)
	{
		std::map<std::string, QuantizationRegionValue> _map = std::map<std::string, QuantizationRegionValue>();
		_map.insert(std::make_pair("Minimum", QuantizationRegionValue::Minimum));
		_map.insert(std::make_pair("Average", QuantizationRegionValue::Average));
		_map.insert(std::make_pair("Maximum", QuantizationRegionValue::Maximum));

		auto it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return QuantizationRegionValue::Minimum;
		}
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	Quantization::Quantization(std::shared_ptr<TPGEContext> context) :
		TechniqueBase(context),
		whichType_(3)
	{
		
	}

	Quantization::~Quantization()
	{
	}

	void Quantization::BindAgent(std::shared_ptr<Agent> agent)
	{
		// parse initialization
		TPGE_PARSE_INIT;

		// parse all attributes
		TPGE_PARSE_CONSTANT(agent, "Algorithm", string);
		TPGE_PARSE_CONSTANT(agent, "MinimumValue", float);
		TPGE_PARSE_CONSTANT(agent, "MaximumValue", float);

		TPGE_PARSE_CONSTANT(agent, "NumRegions", unsigned);
		TPGE_PARSE_CONSTANT(agent, "RegionValue", string);

		// bind the variable
		value_ = agent->GetDataVariable(_variables[0]);
		whichType_ = value_->GetElement(0).Which();
	}

	void Quantization::InitializeConstants()
	{
		// initialize base
		TPGE_INITIALIZE_TECHNIQUE_BASE(TechniqueBase);

		// initialize new members
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(0, "Algorithm", string, "Uniform");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(1, "MinimumValue", float, 0.0f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(2, "MaximumValue", float, 1.0f);

		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(3, "NumRegions", unsigned, 5);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(4, "RegionValue", string, "Minimum");
	}

	void Quantization::ProcessDataPoint(unsigned processIndex)
	{
		Variant& var = value_->GetElement(processIndex);
		GetValue(var);
	}

	bool Quantization::ProcessNode(std::shared_ptr<GeneratedNode> node, EdgeType edgeType)
	{
		// nothing to do, since this is a data only technique
		return true;
	}

	void Quantization::Start()
	{
		TechniqueBase::Start();

		switch (GetQuantizationAlgorithmType(constantAttributesMap_["Algorithm"]->GetString()))
		{
		case QuantizationAlgorithm::Uniform:
			SetupRegions();
			break;
		}
	}

	void Quantization::Stop()
	{
		TechniqueBase::Stop();
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	void Quantization::SetupRegions()
	{
		QuantizationRegionValue regionValue = GetQuantizationRegionValue(constantAttributesMap_["RegionValue"]->GetString());
		unsigned regions = constantAttributesMap_["NumRegions"]->GetUInt();
		float min = constantAttributesMap_["MinimumValue"]->GetFloat();
		float max = constantAttributesMap_["MaximumValue"]->GetFloat();
		for (unsigned i = 0; i < regions; i++)
		{
			float chunk = (max - min) / regions;
			regionMin_.push_back(chunk * i + min);
			regionMax_.push_back(chunk * (i + 1) + min);

			switch (regionValue)
			{
			case QuantizationRegionValue::Minimum:
				regionValue_.push_back(regionMin_.back());
				break;
			case QuantizationRegionValue::Average:
				regionValue_.push_back((regionMin_.back() + regionMax_.back()) / 2);
				break;
			case QuantizationRegionValue::Maximum:
				regionValue_.push_back(regionMax_.back());
				break;
			}
		}
	}

	void Quantization::GetValue(Variant& var)
	{
		switch (GetQuantizationAlgorithmType(constantAttributesMap_["Algorithm"]->GetString()))
		{
		case QuantizationAlgorithm::Uniform:
			GetValueFromRegion(var);
			break;
		default: break;
		}
	}

	void Quantization::GetValueFromRegion(Variant& var)
	{
		switch (whichType_)
		{
		case 0:
			var.Set(var.GetBool());
			break;
		case 1:
			for (unsigned i = 0; i < regionMin_.size(); i++)
			{
				if (var.GetInt() >= (int)regionMin_[i] && var.GetInt() < (int)regionMax_[i])
					var.Set((int)regionValue_[i]);
			}
			break;
		case 2:
			for (unsigned i = 0; i < regionMin_.size(); i++)
			{
				if (var.GetUInt() >= (unsigned)regionMin_[i] && var.GetUInt() < (unsigned)regionMax_[i])
					var.Set((unsigned)regionValue_[i]);
			}
			break;
		case 3:
			for (unsigned i = 0; i < regionMin_.size(); i++)
			{
				if (var.GetFloat() >= regionMin_[i] && var.GetFloat() < regionMax_[i])
					var.Set(regionValue_[i]);
			}
			break;
		case 4:
			for (unsigned i = 0; i < regionMin_.size(); i++)
			{
				if (var.GetDouble() >= (double)regionMin_[i] && var.GetDouble() < (double)regionMax_[i])
					var.Set((double)regionValue_[i]);
			}
			break;
		}
	}

}