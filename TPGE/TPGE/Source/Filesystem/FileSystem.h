#pragma once

/// includes
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <map>
#include <memory>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"

namespace TPGE
{
	/// forward declarations
	class IDataLoader;
	class IFileLoader;

	/// Get the ending of a path to decide which loader to use
	std::string GetPathEnding(const std::string& path);
	/// get the path relative to path
	std::string GetRelativePath(const std::string& path, const std::string& rel);

	class FileSystem : public TPGEObject
	{
	public:

		TPGE_BASE_OBJECT(FileSystem)

		FileSystem(std::shared_ptr<TPGEContext> context);
		~FileSystem();

		/// Initialize the Loaders
		void InitializeLoaders();
		/// Add a DataLoader to the list
		template<typename T> void RegisterDataLoader(const std::string& fileEnding);
		/// Add a fileLoader to the list
		template<typename T> void RegisterFileLoader(const std::string& fileEnding);

		/// Get a data loader by file ending
		std::shared_ptr<IDataLoader> GetDataLoader(const std::string& fileEnding);
		/// Get a file loader by file ending
		std::shared_ptr<IFileLoader> GetFileLoader(const std::string& fileEnding);

	protected:

	private:
		/// The fileLoaders
		std::map<std::string, std::shared_ptr<IDataLoader> > dataLoaders_;
		/// The fileLoaders
		std::map<std::string, std::shared_ptr<IFileLoader> > fileLoaders_;
	};

	template<typename T> void FileSystem::RegisterDataLoader(const std::string& fileEnding)
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<IDataLoader, T>::value),
			"The loader class T must be a descendant of TPGE::IDataLoader"
			);
		dataLoaders_.insert(std::pair<std::string, std::shared_ptr<IDataLoader> >(fileEnding, std::make_shared<T>(context_)));
	}

	template<typename T> void FileSystem::RegisterFileLoader(const std::string& fileEnding)
	{
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_base_of<IFileLoader, T>::value),
			"The loader class T must be a descendant of TPGE::IFileLoader"
			);
		fileLoaders_.insert(std::pair<std::string, std::shared_ptr<IFileLoader> >(fileEnding, std::make_shared<T>(context_)));
	}
}