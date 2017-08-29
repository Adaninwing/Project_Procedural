// includes
#include <chrono>

// header
#include "Random.h"

// library includes
// -

namespace TPGE
{
	//===============================================================
	// O P E R A T O R
	//===============================================================


	//===============================================================
	// P U B L I C
	//===============================================================
	Random::Random() :
		Random((unsigned)std::chrono::system_clock::now().time_since_epoch().count())
	{
	}

	Random::Random(unsigned seed) :
		alpha_(0.0f),
		beta_(0.0f),
		dev_(0.1f),
		deterministic_(false),
		lambda_(),
		m_(900.0f),
		max_(1.0f),
		mean_(0.5f),
		min_(0.0f),
		n_(100.0f),
		probabilityP_(0.1f),
		k_(0.0f),
		s_(0.0f),
		seed_(seed)
	{
		rngMap_.insert(std::make_pair(_generators[0], std::make_shared<SmartRNG<std::minstd_rand> >(seed)));
		rngMap_.insert(std::make_pair(_generators[1], std::make_shared<SmartRNG<std::mt19937> >(seed)));
		rngMap_.insert(std::make_pair(_generators[2], std::make_shared<SmartRNG<std::ranlux24> >(seed)));
		rngMap_.insert(std::make_pair(_generators[3], std::make_shared<SmartRNG<std::ranlux48> >(seed)));
		rngMap_.insert(std::make_pair(_generators[4], std::make_shared<SmartRNG<std::knuth_b> >(seed)));
	}

	Random::~Random()
	{

	}

	float Random::GetRandomFloat(const std::string& distribution, const std::string& generator)
	{
		std::map<std::string, std::shared_ptr<RNGBase>>::const_iterator it = rngMap_.find(generator);
		if (it != rngMap_.end())
		{
			std::shared_ptr<RNGBase> gen = it->second;

			if (distribution == _distributions[0]) return gen->operator()(distribution, min_, max_);
			else if (distribution == _distributions[1]) return gen->operator()(distribution, probabilityP_);
			else if (distribution == _distributions[2]) return gen->operator()(distribution, max_, probabilityP_);
			else if (distribution == _distributions[3]) return gen->operator()(distribution, probabilityP_);
			else if (distribution == _distributions[4]) return gen->operator()(distribution, k_, probabilityP_);
			else if (distribution == _distributions[5]) return gen->operator()(distribution, mean_);
			else if (distribution == _distributions[6]) return gen->operator()(distribution, lambda_);
			else if (distribution == _distributions[7]) return gen->operator()(distribution, alpha_, beta_);
			else if (distribution == _distributions[8]) return gen->operator()(distribution, alpha_, beta_);
			else if (distribution == _distributions[9]) return gen->operator()(distribution, alpha_, beta_);
			else if (distribution == _distributions[10]) return gen->operator()(distribution, mean_, dev_);
			else if (distribution == _distributions[11]) return gen->operator()(distribution, m_, s_);
			else if (distribution == _distributions[12]) return gen->operator()(distribution, n_);
			else if (distribution == _distributions[13]) return gen->operator()(distribution, alpha_, beta_);
			else if (distribution == _distributions[14]) return gen->operator()(distribution, m_, n_);
			else if (distribution == _distributions[15]) return gen->operator()(distribution, n_);
			else return gen->operator()();
		}
		
		srand(seed_);
		return rand() % (int)max_ + min_;
	}
	
	int Random::GetRandomInt(const std::string& distribution, const std::string& generator)
	{
		return (int)GetRandomFloat(distribution, generator);
	}
	
	unsigned Random::GetRandomUint(const std::string& distribution, const std::string& generator)
	{
		return (unsigned)GetRandomFloat(distribution, generator);
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	
}