#pragma once

/// includes
#include <FastNoiseSIMD.h>
#include <vector>

/// base class
#include "TechniqueBase.h"
#include "Util/NArray.h"

namespace TPGE
{
	const std::string _noiseType[10] { 
		"Value", 
		"ValueFractal", 
		"Perlin", 
		"PerlinFractal", 
		"Simplex", 
		"SimplexFractal", 
		"WhiteNoise", 
		"Cellular", 
		"Cubic", 
		"CubicFractal"
	};
	FastNoiseSIMD::NoiseType GetNoiseType(std::string type);

	const std::string _fractalType[3] { 
		"FBM", 
		"Billow", 
		"RigidMulti" 
	};
	FastNoiseSIMD::FractalType GetFractalType(std::string type);

	const std::string _perturbType[6] { 
		"None", 
		"Gradient", 
		"GradientFractal", 
		"Normalise", 
		"Gradient_Normalise", 
		"GradientFractal_Normalise" 
	};
	FastNoiseSIMD::PerturbType GetPerturbType(std::string type);

	const std::string _cellularDistanceFunction[3] { 
		"Euclidean", 
		"Manhattan", 
		"Natural"
	};
	FastNoiseSIMD::CellularDistanceFunction GetDistanceFunctionType(std::string type);

	const std::string _cellularReturnType[8] { 
		"CellValue", 
		"Distance", 
		"Distance2", 
		"Distance2Add", 
		"Distance2Sub", 
		"Distance2Mul", 
		"Distance2Div", 
		"NoiseLookup"
	};
	FastNoiseSIMD::CellularReturnType GetCellularReturnType(std::string type);

	/// forward declaration
	class Agent;

	class Noise : public TechniqueBase
	{
	public:
		TPGE_OBJECT(Noise, TechniqueBase)

		Noise(std::shared_ptr<TPGEContext> context);
		~Noise();

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
		/// Get a new set if no set was gotten yet yet
		void InitializeNoiseSet();

	private:
		/// Get total number of elements
		size_t GetSetLength() const;

		/// the dimensions of the set
		std::vector<unsigned> dims_;
		/// The noise Genertor from the library
		FastNoiseSIMD* noise_;
		/// The noise set gotten from the library
		float* noiseSet_;
		/// the Value structure
		std::shared_ptr<NArray<Variant> > value_;
		/// Variant type stored for efficiency
		int whichType_;
	};
}