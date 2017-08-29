// includes
#include <stdio.h>  
#include <conio.h>  
#include <stdlib.h>  
#include <direct.h> 

// header
#include "FileSystem.h"

// Library includes
#include "IDataLoader.h"
#include "IFileLoader.h"
#include "RawDataLoader.h"
#include "XmlLoader.h"

namespace TPGE
{
	//===============================================================
	// G L O B A L
	//===============================================================
	std::string GetPathEnding(const std::string& path)
	{
		size_t index = path.find_last_of(".");
		return path.substr(index + 1, path.length());
	}

	std::string GetRelativePath(const std::string& path, const std::string& rel)
	{
		std::string relAssembled = path.substr(0, path.find_last_of("\\") + 1);
		relAssembled.append(rel);
		char full[_MAX_PATH];
		_fullpath(full, relAssembled.c_str(), _MAX_PATH);
		return std::string(full);
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	FileSystem::FileSystem(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context)
	{
		InitializeLoaders();
	}

	FileSystem::~FileSystem()
	{

	}

	void FileSystem::InitializeLoaders()
	{
		RegisterDataLoader<RawDataLoader>("rdat");

		RegisterFileLoader<XmlLoader>("xml");
	}

	std::shared_ptr<IDataLoader> FileSystem::GetDataLoader(const std::string& fileEnding)
	{
		return dataLoaders_[fileEnding];
	}
	
	std::shared_ptr<IFileLoader> FileSystem::GetFileLoader(const std::string& fileEnding)
	{
		return fileLoaders_[fileEnding];
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
}