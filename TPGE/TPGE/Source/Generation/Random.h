#pragma once

/// includes
#include <map>
#include <memory>
#include <random>
#include <string>

namespace TPGE {

	const std::string _generators[5] =
	{
		"Minimal Standard",
		"Mersenne Twister 19937",
		"Ranlux 24",
		"Ranlux 48",
		"Knuth-B"
	};
	const std::string _distributions[16] = 
	{
		"Uniform",
		"Bernoulli",
		"Binomial",
		"Geometric",
		"Negative Binomial",
		"Poisson",
		"Exponential",
		"Gamma",
		"Weibull",
		"Extreme Value",
		"Normal",
		"Lognormal",
		"Chi-Squared",
		"Cauchy",
		"Fisher F",
		"Student T"
	};

	struct RNGBase {
		RNGBase() {};
		RNGBase(unsigned seed) {};

		virtual float operator()() = 0;
		virtual float operator()(const std::string& distribution, float first = 0.0f, float second = 0.0f) = 0;
	};

	template< class RNG >
	struct SmartRNG : RNGBase {
		SmartRNG() : RNGBase() {}
		SmartRNG(unsigned seed) : RNGBase() 
		{
			gen = RNG();
		};

		RNG gen;

		/// basic generation method
		virtual float operator()()
		{
			return (float)gen();
		}

		/// helper to access template function with set parameters from base class
		virtual float operator()(const std::string& distribution, float first = 0.0, float second = 0.0f)
		{
			if (distribution == _distributions[0]) return Generate(std::uniform_real_distribution<float>(first, second));
			else if (distribution == _distributions[1]) return Generate(std::bernoulli_distribution(first));
			else if (distribution == _distributions[2]) return Generate(std::binomial_distribution<int>((int)first, second));
			else if (distribution == _distributions[3]) return Generate(std::geometric_distribution<int>(first));
			else if (distribution == _distributions[4]) return Generate(std::negative_binomial_distribution<int>((int)first, second));
			else if (distribution == _distributions[5]) return Generate(std::poisson_distribution<int>(first));
			else if (distribution == _distributions[6]) return Generate(std::exponential_distribution<float>(first));
			else if (distribution == _distributions[7]) return Generate(std::gamma_distribution<float>(first, second));
			else if (distribution == _distributions[8]) return Generate(std::weibull_distribution<float>(first, second));
			else if (distribution == _distributions[9]) return Generate(std::extreme_value_distribution<float>(first, second));
			else if (distribution == _distributions[10]) return Generate(std::normal_distribution<float>(first, second));
			else if (distribution == _distributions[11]) return Generate(std::lognormal_distribution<float>(first, second));
			else if (distribution == _distributions[12]) return Generate(std::chi_squared_distribution<float>(first));
			else if (distribution == _distributions[13]) return Generate(std::cauchy_distribution<float>(first, second));
			else if (distribution == _distributions[14]) return Generate(std::fisher_f_distribution<float>(first, second));
			else if (distribution == _distributions[15]) return Generate(std::student_t_distribution<float>(first));
			else return (float)gen();
		}

		/// generation method with template class as a distribution from <random>
		template<class Distribution> float Generate(Distribution dist)
		{
			return (float)dist(gen);
		}
	};

	class Random
	{
	public:
		Random();
		Random(unsigned seed);
		~Random();

		/// get a Random float based on distribution and generation
		float GetRandomFloat(const std::string& distribution, const std::string& generator);
		/// get a Random float based on distribution
		float GetRandomFloat(const std::string& distribution) { return GetRandomFloat(distribution, "Mersenne Twister 19937"); }
		/// get a Random float 
		float GetRandomFloat() { return GetRandomFloat("", "Mersenne Twister 19937"); }
		/// get a Random int based on distribution and generation
		int GetRandomInt(const std::string& distribution, const std::string& generator);
		/// get a Random int based on distribution
		int GetRandomInt(const std::string& distribution) { return GetRandomInt(distribution, "Mersenne Twister 19937"); }
		/// get a Random int 
		int GetRandomInt() { return GetRandomInt("", "Mersenne Twister 19937"); }
		/// get a Random uint based on distribution and generation
		unsigned GetRandomUint(const std::string& distribution, const std::string& generator);
		/// get a Random uint based on distribution
		unsigned GetRandomUint(const std::string& distribution) { return GetRandomUint(distribution, "Mersenne Twister 19937"); }
		/// get a Random uint 
		unsigned GetRandomUint() { return GetRandomUint("", "Mersenne Twister 19937"); }
		
		/// Get alpha/a of distribution
		float GetAlpha() { return alpha_; };
		/// Get beta/b of distribution
		float GetBeta() { return beta_; };
		/// Get the deterministic mode flag
		bool GetetDerministic() { return deterministic_; }
		/// Get devition of distribution
		float GetDev() { return dev_; };
		/// Get lambda of distribution
		float GetLambda() { return lambda_; };
		/// Get Degrees of freedom 
		float GetM() { return m_; };
		/// Get max value
		float GetMax() { return max_; };
		/// Get the mean of distribution
		float GetMean() { return mean_; };
		/// Get min value
		float GetMin() { return min_; };
		/// Get Degrees of freedom 
		float GetN() { return n_; };
		/// Get probability of distribution
		float GetProbabilityP() { return probabilityP_; };
		/// Get variable k of distribution
		float GetK() { return k_; };
		/// Get variable s of distribution
		float GetS() { return s_; };
		/// Get the seed
		unsigned GetSeed() { return seed_; }		

		/// Set alpha/a of distribution
		void SetAlpha(float alpha) {  alpha_ = alpha; };
		/// Set beta/b of distribution
		void SetBeta(float beta) {  beta_ = beta; };
		/// Set the deterministic mode flag
		void SetetDerministic(bool deterministic) { deterministic_ = deterministic; }
		/// Set devition of distribution
		void SetDev(float dev) {  dev_ = dev; };
		/// Set lambda of distribution
		void SetLambda(float lambda) {  lambda_ = lambda; };
		/// Set Degrees of freedom 
		void SetM(float m) {  m_ = m; };
		/// Set max value
		void SetMax(float max) {  max_ = max; };
		/// Set the mean of distribution
		void SetMean(float mean) {  mean_ = mean; };
		/// Set min value
		void SetMin(float min) {  min_ = min; };
		/// Set Degrees of freedom 
		void SetN(float n) {  n_ = n; };
		/// Set probability of distribution
		void SetProbabilityP(float p) { probabilityP_ = p; };
		/// Set variable k of distribution
		void SetK(float k) { k_ = k; };
		/// Set variable s of distribution
		void SetS(float s) { s_ = s; };

	private:
		/// alpha/a of distribution
		float alpha_;
		/// beta/b of distribution
		float beta_;
		/// deterministic mode flag
		bool deterministic_;			/// TODO
		/// devition of distribution
		float dev_;
		/// the map of rngs
		std::map<std::string, std::shared_ptr<RNGBase> > rngMap_;
		/// lambda of distribution
		float lambda_;
		/// Degrees of freedom 
		float m_;
		/// max value
		float max_;
		/// the mean of distribution
		float mean_;
		/// min value
		float min_;
		/// Degrees of freedom 
		float n_;
		/// probability of distribution
		float probabilityP_;
		/// variable k of distribution
		float k_;
		/// variable s of distribution
		float s_;
		/// the seed
		unsigned seed_;

	};
}
