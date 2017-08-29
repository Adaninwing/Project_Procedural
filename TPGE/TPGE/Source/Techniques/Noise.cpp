// includes
#include <chrono>

// header
#include "Noise.h"

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

	FastNoiseSIMD::NoiseType GetNoiseType(std::string type)
	{
		std::map<std::string, FastNoiseSIMD::NoiseType> _map = std::map<std::string, FastNoiseSIMD::NoiseType>();
		_map.insert(std::make_pair(_noiseType[0], FastNoiseSIMD::NoiseType::Value));
		_map.insert(std::make_pair(_noiseType[1], FastNoiseSIMD::NoiseType::ValueFractal));
		_map.insert(std::make_pair(_noiseType[2], FastNoiseSIMD::NoiseType::Perlin));
		_map.insert(std::make_pair(_noiseType[3], FastNoiseSIMD::NoiseType::PerlinFractal));
		_map.insert(std::make_pair(_noiseType[4], FastNoiseSIMD::NoiseType::Simplex));
		_map.insert(std::make_pair(_noiseType[5], FastNoiseSIMD::NoiseType::SimplexFractal));
		_map.insert(std::make_pair(_noiseType[6], FastNoiseSIMD::NoiseType::WhiteNoise));
		_map.insert(std::make_pair(_noiseType[7], FastNoiseSIMD::NoiseType::Cellular));
		_map.insert(std::make_pair(_noiseType[8], FastNoiseSIMD::NoiseType::Cubic));
		_map.insert(std::make_pair(_noiseType[9], FastNoiseSIMD::NoiseType::CubicFractal));

		std::map<std::string, FastNoiseSIMD::NoiseType>::iterator it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return FastNoiseSIMD::NoiseType::Value;
		}
	}

	FastNoiseSIMD::FractalType GetFractalType(std::string type)
	{
		std::map<std::string, FastNoiseSIMD::FractalType> _map = std::map<std::string, FastNoiseSIMD::FractalType>();
		_map.insert(std::make_pair(_fractalType[0], FastNoiseSIMD::FractalType::FBM));
		_map.insert(std::make_pair(_fractalType[1], FastNoiseSIMD::FractalType::Billow));
		_map.insert(std::make_pair(_fractalType[2], FastNoiseSIMD::FractalType::RigidMulti));

		std::map<std::string, FastNoiseSIMD::FractalType>::iterator it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return FastNoiseSIMD::FractalType::FBM;
		}
	}

	FastNoiseSIMD::PerturbType GetPerturbType(std::string type)
	{
		std::map<std::string, FastNoiseSIMD::PerturbType> _map = std::map<std::string, FastNoiseSIMD::PerturbType>();
		_map.insert(std::make_pair(_perturbType[0], FastNoiseSIMD::PerturbType::None));
		_map.insert(std::make_pair(_perturbType[1], FastNoiseSIMD::PerturbType::Gradient));
		_map.insert(std::make_pair(_perturbType[2], FastNoiseSIMD::PerturbType::GradientFractal));
		_map.insert(std::make_pair(_perturbType[3], FastNoiseSIMD::PerturbType::Normalise));
		_map.insert(std::make_pair(_perturbType[4], FastNoiseSIMD::PerturbType::Gradient_Normalise));
		_map.insert(std::make_pair(_perturbType[5], FastNoiseSIMD::PerturbType::GradientFractal_Normalise));

		std::map<std::string, FastNoiseSIMD::PerturbType>::iterator it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return FastNoiseSIMD::PerturbType::None;
		}
	}

	FastNoiseSIMD::CellularDistanceFunction GetDistanceFunctionType(std::string type)
	{
		std::map<std::string, FastNoiseSIMD::CellularDistanceFunction> _map = std::map<std::string, FastNoiseSIMD::CellularDistanceFunction>();
		_map.insert(std::make_pair(_cellularDistanceFunction[0], FastNoiseSIMD::CellularDistanceFunction::Euclidean));
		_map.insert(std::make_pair(_cellularDistanceFunction[1], FastNoiseSIMD::CellularDistanceFunction::Manhattan));
		_map.insert(std::make_pair(_cellularDistanceFunction[2], FastNoiseSIMD::CellularDistanceFunction::Natural));

		std::map<std::string, FastNoiseSIMD::CellularDistanceFunction>::iterator it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return FastNoiseSIMD::CellularDistanceFunction::Euclidean;
		}
	}

	FastNoiseSIMD::CellularReturnType GetCellularReturnType(std::string type)
	{
		std::map<std::string, FastNoiseSIMD::CellularReturnType> _map = std::map<std::string, FastNoiseSIMD::CellularReturnType>();
		_map.insert(std::make_pair(_cellularReturnType[0], FastNoiseSIMD::CellularReturnType::CellValue));
		_map.insert(std::make_pair(_cellularReturnType[1], FastNoiseSIMD::CellularReturnType::Distance));
		_map.insert(std::make_pair(_cellularReturnType[2], FastNoiseSIMD::CellularReturnType::Distance2));
		_map.insert(std::make_pair(_cellularReturnType[3], FastNoiseSIMD::CellularReturnType::Distance2Add));
		_map.insert(std::make_pair(_cellularReturnType[4], FastNoiseSIMD::CellularReturnType::Distance2Sub));
		_map.insert(std::make_pair(_cellularReturnType[5], FastNoiseSIMD::CellularReturnType::Distance2Mul));
		_map.insert(std::make_pair(_cellularReturnType[6], FastNoiseSIMD::CellularReturnType::Distance2Div));
		_map.insert(std::make_pair(_cellularReturnType[7], FastNoiseSIMD::CellularReturnType::NoiseLookup));

		std::map<std::string, FastNoiseSIMD::CellularReturnType>::iterator it = _map.find(type);
		if (it != _map.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return FastNoiseSIMD::CellularReturnType::CellValue;
		}
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	Noise::Noise(std::shared_ptr<TPGEContext> context) : 
		TechniqueBase(context),
		whichType_(3)
	{
		noise_ = FastNoiseSIMD::NewFastNoiseSIMD();
	}

	Noise::~Noise()
	{
		delete noise_;
	}

	void Noise::BindAgent(std::shared_ptr<Agent> agent)
	{
		// parse initialization
		TPGE_PARSE_INIT;

		// parse all attributes
		TPGE_PARSE_CONSTANT(agent, "NoiseType", string);
		TPGE_PARSE_CONSTANT(agent, "Seed", int);
		TPGE_PARSE_CONSTANT(agent, "Frequency", float);

		TPGE_PARSE_CONSTANT(agent, "FractalType", string);
		TPGE_PARSE_CONSTANT(agent, "FractalOctaves", int);
		TPGE_PARSE_CONSTANT(agent, "FractalLacunarity", float);
		TPGE_PARSE_CONSTANT(agent, "FractalGain", float);

		TPGE_PARSE_CONSTANT(agent, "CellularDistanceFunction", string);
		TPGE_PARSE_CONSTANT(agent, "CellularReturnType", string);
		TPGE_PARSE_CONSTANT(agent, "CellularNoiseLookupType", string);
		TPGE_PARSE_CONSTANT(agent, "CellularNoiseLookupFrequency", float);

		TPGE_PARSE_CONSTANT(agent, "PerturbType", string);
		TPGE_PARSE_CONSTANT(agent, "PerturbAmp", float);
		TPGE_PARSE_CONSTANT(agent, "PerturbFrequency", float);
		TPGE_PARSE_CONSTANT(agent, "PerturbFractalOctaves", int);
		TPGE_PARSE_CONSTANT(agent, "PerturbFractalLacunarity", float);
		TPGE_PARSE_CONSTANT(agent, "PerturbFractalGain", float);
		TPGE_PARSE_CONSTANT(agent, "PerturbNormaliseLength", float);

		TPGE_PARSE_CONSTANT(agent, "BoolThreshold", float);
		TPGE_PARSE_CONSTANT(agent, "IntConversionMultiplyer", int);

		// bind the variable
		value_ = agent->GetDataVariable(_variables[0]);
		whichType_ = value_->GetElement(0).Which();

		/// parse the dimensions of the variable
		std::vector<size_t> dims = agent->GetDataVariable(_variables[0])->GetSize();
		for (unsigned i = 0; i < dims.size() && i < dims_.size(); i++)
			dims_[i] = dims[i];
	}

	void Noise::InitializeConstants()
	{
		// initialize base
		TPGE_INITIALIZE_TECHNIQUE_BASE(TechniqueBase);

		// initialize new members
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(0, "NoiseType", string, "Simplex");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(1, "Seed", int, (int)std::chrono::system_clock::now().time_since_epoch().count());
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(2, "Frequency", float, 0.01f);

		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(3, "FractalType", string, "FBM");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(4, "FractalOctaves", int, 3);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(5, "FractalLacunarity", float, 2.0);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(6, "FractalGain", float, 0.5);

		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(7, "CellularDistanceFunction", string, "Euclidean");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(8, "CellularReturnType", string, "Distance");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(9, "CellularNoiseLookupType", string, "Simplex");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(10, "CellularNoiseLookupFrequency", float, 0.2f);

		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(11, "PerturbType", string, "None");
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(12, "PerturbAmp", float, 1.0f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(13, "PerturbFrequency", float, 0.5f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(14, "PerturbFractalOctaves", int, 3);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(15, "PerturbFractalLacunarity", float, 2.0f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(16, "PerturbFractalGain", float, 0.5f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(17, "PerturbNormaliseLength", float, 1.0f);

		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(18, "BoolThreshold", float, 0.5f);
		TPGE_INITIALIZE_TECHNIQUE_CONSTANT(19, "IntConversionMultiplyer", int, 256);

		// initialize dimensions
		for (unsigned i = 0; i < 3; i++)
			dims_.push_back(1);
	}

	void Noise::ProcessDataPoint(unsigned processIndex)
	{
		if (!noiseSet_)
		{
			InitializeNoiseSet();
		}

		if (processIndex < GetSetLength())
		{
			float value = noiseSet_[processIndex];
			switch (whichType_)
			{
			case 0:
				value_->GetElement(processIndex).Set(value > constantAttributesMap_["BoolThreshold"]->GetFloat());
				break;
			case 1:
				value_->GetElement(processIndex).Set((int)(value * constantAttributesMap_["IntConversionMultiplyer"]->GetInt()));
				break;
			case 2:
				value_->GetElement(processIndex).Set((unsigned)((1 + value) / 2 * constantAttributesMap_["IntConversionMultiplyer"]->GetInt()));
				break;
			case 3:
				value_->GetElement(processIndex).Set(value);
				break;
			case 4:
				value_->GetElement(processIndex).Set((double)value);
				break;
			}
		}
	}

	bool Noise::ProcessNode(std::shared_ptr<GeneratedNode> node, EdgeType edgeType)
	{
		// nothing to do, since this is a data only technique
		return true;
	}

	void Noise::Start()
	{
		TechniqueBase::Start();

		FastNoiseSIMD::NoiseType noiseType = GetNoiseType(constantAttributesMap_["NoiseType"]->GetString());
		noise_->SetNoiseType(noiseType);
		noise_->SetSeed(constantAttributesMap_["Seed"]->GetInt());
		noise_->SetFrequency(constantAttributesMap_["Frequency"]->GetFloat());

		noise_->SetFractalType(GetFractalType(constantAttributesMap_["FractalType"]->GetString()));
		noise_->SetFractalOctaves(constantAttributesMap_["FractalOctaves"]->GetInt());
		noise_->SetFractalLacunarity(constantAttributesMap_["FractalLacunarity"]->GetFloat());
		noise_->SetFractalGain(constantAttributesMap_["FractalGain"]->GetFloat());

		noise_->SetCellularDistanceFunction(GetDistanceFunctionType(constantAttributesMap_["CellularDistanceFunction"]->GetString()));
		noise_->SetCellularReturnType(GetCellularReturnType(constantAttributesMap_["CellularReturnType"]->GetString()));
		noise_->SetCellularNoiseLookupType(noiseType);
		noise_->SetCellularNoiseLookupFrequency(constantAttributesMap_["CellularNoiseLookupFrequency"]->GetFloat());

		noise_->SetPerturbType(GetPerturbType(constantAttributesMap_["PerturbType"]->GetString()));
		noise_->SetPerturbAmp(constantAttributesMap_["PerturbAmp"]->GetFloat());
		noise_->SetPerturbFrequency(constantAttributesMap_["PerturbFrequency"]->GetFloat());
		noise_->SetPerturbFractalOctaves(constantAttributesMap_["PerturbFractalOctaves"]->GetInt());
		noise_->SetPerturbFractalLacunarity(constantAttributesMap_["PerturbFractalLacunarity"]->GetFloat());
		noise_->SetPerturbFractalGain(constantAttributesMap_["PerturbFractalGain"]->GetFloat());
		noise_->SetPerturbNormaliseLength(constantAttributesMap_["PerturbNormaliseLength"]->GetFloat());
	}

	void Noise::Stop()
	{
		TechniqueBase::Stop();

		noise_->FreeNoiseSet(noiseSet_);
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================
	void Noise::InitializeNoiseSet()
	{
		FastNoiseSIMD::NoiseType noiseType = GetNoiseType(constantAttributesMap_["NoiseType"]->GetString());
		switch (noiseType)
		{
		case FastNoiseSIMD::NoiseType::Value:
			noiseSet_ = noise_->GetValueSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::ValueFractal:
			noiseSet_ = noise_->GetValueFractalSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::Perlin:
			noiseSet_ = noise_->GetPerlinSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::PerlinFractal:
			noiseSet_ = noise_->GetPerlinFractalSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::Simplex:
			noiseSet_ = noise_->GetSimplexSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::SimplexFractal:
			noiseSet_ = noise_->GetSimplexFractalSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::WhiteNoise:
			noiseSet_ = noise_->GetWhiteNoiseSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::Cellular:
			noiseSet_ = noise_->GetCellularSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::Cubic:
			noiseSet_ = noise_->GetCubicSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		case FastNoiseSIMD::NoiseType::CubicFractal:
			noiseSet_ = noise_->GetCubicFractalSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		default:
			noiseSet_ = noise_->GetSimplexSet(0, 0, 0, dims_[0], dims_[1], dims_[2]); break;
		}
	}

	//===============================================================
	// P R I V A T E
	//===============================================================
	size_t Noise::GetSetLength() const
	{
		size_t ret = dims_[0];
		for (unsigned i = 1; i < dims_.size(); i++)
		{
			ret *= dims_[i];
		}
		return ret;
	}
}