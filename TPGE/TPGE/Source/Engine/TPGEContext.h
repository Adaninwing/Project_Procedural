#pragma once

/// includes
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <map>
#include <memory>

namespace TPGE
{
	/// forward declaration
	class TPGEObject;

	class TPGEContext
	{
	public:
		TPGEContext();
		~TPGEContext();

		/// Register a subsystem
		void RegisterSubsystem(std::shared_ptr<TPGEObject> system);
		/// Register a subsystem
		template<typename T> void RegisterSubsystem();

		/// Get a subsystem
		std::shared_ptr<TPGEObject> GetSubsystem(const std::string& name) { return subsystems_[name]; }
		/// Get a subsystem
		template<typename T> std::shared_ptr<T> GetSubsystem();

	protected:

	private:
		/// The fileLoaders
		std::map<std::string, std::shared_ptr<TPGEObject> > subsystems_;
	};

	template<typename T> void TPGEContext::RegisterSubsystem()
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<TPGEObject, T>::value),
			"The subsystem T must be a descendant of TPGE::TPGEObject"
			);
		std::shared_ptr<TPGEObject> ptr = std::make_shared<T>();
		subsystems_.insert(std::pair<std::string, std::shared_ptr<TPGEObject> >(ptr->GetTypeName(), ptr));
	}

	template<typename T> std::shared_ptr<T> TPGEContext::GetSubsystem()
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<TPGEObject, T>::value),
			"The subsystem T must be a descendant of TPGE::TPGEObject"
			);
		return std::static_pointer_cast<T>(subsystems_[T::GetTypeNameStatic()]);
	}
}