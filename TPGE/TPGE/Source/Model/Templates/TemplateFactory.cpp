// header
#include "TemplateFactory.h"

// library inludes
#include "AgentTemplate.h"
#include "ComboTemplate.h"
#include "DataTemplate.h"
#include "Engine/TPGEContext.h"
#include "Filesystem/FileSystem.h"
#include "Filesystem/IFileLoader.h"
#include "Filesystem/XmlLoader.h"
#include "GraphTemplate.h"
#include "PassTemplate.h"
#include "TechniqueTemplate.h"
#include "Template.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	TemplateFactory::TemplateFactory(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context),
		loadFinished_(false),
		projectPath_()
	{
	}

	TemplateFactory::~TemplateFactory()
	{

	}

	void TemplateFactory::Load()
	{
		std::string projectType = GetPathEnding(projectPath_);
		std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(projectType);
		if (fileLoader)
		{
			template_ = fileLoader->LoadTemplate(projectPath_, combosToLoad_);
			LoadCombos();
			LoadData();
			LoadGraphs();
			LoadPasses();
			LoadTechniques();
		}
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

	void TemplateFactory::LoadCombos()
	{
		std::map<std::string, std::shared_ptr<ComboTemplate> >::iterator it;
		for (it = combosToLoad_.begin(); it != combosToLoad_.end(); it++)
		{
			std::shared_ptr<ComboTemplate> combo = std::get<1>(*it);
			std::string path = combo->GetFile();
			std::string fleType = GetPathEnding(path);

			std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(fleType);
			if(fileLoader)
				fileLoader->LoadCombo(combo, dataToLoad_, graphToLoad_);
		}

		combosToLoad_.clear();
	}

	void TemplateFactory::LoadData()
	{
		std::map<std::string, std::shared_ptr<DataTemplate> >::iterator it;
		for (it = dataToLoad_.begin(); it != dataToLoad_.end(); it++)
		{
			std::shared_ptr<DataTemplate> data = std::get<1>(*it);
			std::string path = data->GetFile();
			std::string fleType = GetPathEnding(path);

			std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(fleType);
			if (fileLoader)
				fileLoader->LoadData(data, passesToLoad_);
		}

		dataToLoad_.clear();
	}

	void TemplateFactory::LoadGraphs()
	{
		std::map<std::string, std::shared_ptr<GraphTemplate> >::iterator it;
		for (it = graphToLoad_.begin(); it != graphToLoad_.end(); it++)
		{
			std::shared_ptr<GraphTemplate> graph = std::get<1>(*it);
			std::string path = graph->GetFile();
			std::string fleType = GetPathEnding(path);

			std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(fleType);
			if (fileLoader)
				fileLoader->LoadGraph(graph, passesToLoad_);
		}

		graphToLoad_.clear();
	}

	void TemplateFactory::LoadPasses()
	{
		std::map<std::string, std::shared_ptr<PassTemplate> >::iterator it;
		for (it = passesToLoad_.begin(); it != passesToLoad_.end(); it++)
		{
			std::shared_ptr<PassTemplate> pass = std::get<1>(*it);
			std::string path = pass->GetFile();
			std::string fleType = GetPathEnding(path);

			std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(fleType);
			if (fileLoader)
				fileLoader->LoadPass(pass, techniqueToLoad_);
		}

		passesToLoad_.clear();
	}

	void TemplateFactory::LoadTechniques()
	{
		std::map<std::string, std::shared_ptr<TechniqueTemplate> >::iterator it;
		for (it = techniqueToLoad_.begin(); it != techniqueToLoad_.end(); it++)
		{
			std::shared_ptr<TechniqueTemplate> technique = std::get<1>(*it);
			std::string path = technique->GetFile();
			std::string fleType = GetPathEnding(path);

			std::shared_ptr<IFileLoader> fileLoader = context_->GetSubsystem<FileSystem>()->GetFileLoader(fleType);
			if (fileLoader)
				fileLoader->LoadTechnique(technique);
		}

		techniqueToLoad_.clear();
	}
}