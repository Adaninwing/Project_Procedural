#pragma once

/// includes
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

/// library includes
#include "Engine/TPGEContext.h"
#include "Engine/TPGEObject.h"

namespace TPGE{

	/// forward declarations
	class Agent;
	struct Pass;
	class TechniqueBase;

	/// typedefs
	typedef std::function<TechniqueBase*(std::shared_ptr<TPGEContext>)> CreateFunction;

	class TechniqueInvoker : public TPGEObject
	{
	public:
		TPGE_OBJECT(TechniqueInvoker, TPGEObject)

		TechniqueInvoker(std::shared_ptr<TPGEContext> context);
		~TechniqueInvoker();

		/// execute a pass
		void ExecutePass(std::shared_ptr<Pass> pass);
		/// Register a technique
		template<typename T> void RegisterTechnique(const std::string& techniqueName);
		
		/// Get a technique
		std::shared_ptr<TechniqueBase> GetTechnique(const std::string& techniqueName);
		/// Get a technique
		template<typename T> std::shared_ptr<T> GetTechnique();

	private:
		/// helper to check if all agents are done
		bool AllAgentsDone(std::vector<std::shared_ptr<Agent> >& agents);
		/// Initialize all shipped techniques
		void InitializeTechniques();

		/// The techniques registered in the invoker
		std::map<std::string, CreateFunction> techniquesRegistry_;
	};

	template<typename T> void TechniqueInvoker::RegisterTechnique(const std::string& techniqueName)
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<TechniqueBase, T>::value),
			"The technique class T must be a descendant of TPGE::TechniqueBase"
			);
		techniquesRegistry_.insert(std::make_pair(techniqueName, &T::Create));
	}

	template<typename T> std::shared_ptr<T> TechniqueInvoker::GetTechnique()
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<TechniqueBase, T>::value),
			"The technique class T must be a descendant of TPGE::TechniqueBase"
			);
		return GetTechnique(T::GetTypeNameStatic());
	}
}