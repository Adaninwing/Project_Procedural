#pragma once

/// includes
#include <memory>
#include <map>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"

namespace TPGE
{
	/// Forward Declarations
	class AgentTemplate;
	class ComboTemplate;
	class DataTemplate;
	class GraphTemplate;
	class IFileLoader;
	class PassTemplate;
	class TechniqueTemplate;
	class Template;

	class TemplateFactory : public TPGEObject
	{
	public:
		TPGE_OBJECT(TemplateFactory, TPGEObject)

		TemplateFactory(std::shared_ptr<TPGEContext> context);
		~TemplateFactory();

		/// Start the project loading procedure
		void Load();

		/// Get the project directory
		std::string& GetProjectPath() const { return const_cast<std::string&>(projectPath_); }
		/// Get the loaded template tree
		std::shared_ptr<Template> GetLoadedTemplate() { return template_; };
		/// Get the project directory
		bool HasLoadFinished() const { return loadFinished_; }

		/// Get the project directory
		void SetProjectPath(const std::string& path) { projectPath_ = path; }

	private:
		/// Iterate over combos and load them
		void LoadCombos();
		/// Iterate over data and load them
		void LoadData();
		/// Iterate over graphs and load them
		void LoadGraphs();
		/// Iterate over passes and load them
		void LoadPasses();
		/// Iterate over techniques and load them
		void LoadTechniques();

		/// The combos to load
		std::map<std::string, std::shared_ptr<ComboTemplate> > combosToLoad_;
		/// The data to load
		std::map<std::string, std::shared_ptr<DataTemplate> > dataToLoad_;
		/// The graph to load
		std::map<std::string, std::shared_ptr<GraphTemplate> > graphToLoad_;
		/// A flag to signa if the oad has finished
		bool loadFinished_;
		/// The passes to load
		std::map<std::string, std::shared_ptr<PassTemplate> > passesToLoad_;
		/// The path of the project to load
		std::string projectPath_;
		/// The techniques to load
		std::map<std::string, std::shared_ptr<TechniqueTemplate> > techniqueToLoad_;
		/// The loaded template tree
		std::shared_ptr<Template> template_;
	};

}