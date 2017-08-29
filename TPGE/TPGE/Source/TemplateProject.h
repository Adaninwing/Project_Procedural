#pragma once
/// ProceduralGenerator.h

/// includes
#include <memory>
#include <string>

namespace TPGE
{
	class GeneratedGraph;
	class TechniqueInvoker;
	class Template;
	class TemplateFactory;
	class TPGEContext;

	enum ProjectState 
	{
		PS_IDLE = 0,
		PS_INITIALIZED = 1,
		PS_LOADING = 2,
		PS_LOADED = 3,
	};

	class TemplateProject
	{
	public:
		TemplateProject();
		TemplateProject(const std::string& projectDir);
		TemplateProject(const TemplateProject& toCopy);
		~TemplateProject();

		/// Initialize a project
		void InitializeProject();
		/// Load a tempate file in a project
		void LoadProject(const std::string& file);

		/// Get the library context
		TPGEContext* GetContext() { return context_.get(); }
		/// Get the appication directory (exe location)
		std::string GetCurrentDir();
		/// Get if any given path exists
		bool GetPathExists(const std::string& path);
		/// Get the project directory
		std::string& GetProjectDir() const { return const_cast<std::string&>(projectDir_); }
		/// Get generated root graph
		GeneratedGraph* GetRootGraph();
		/// Get the loaded template
		Template* GetTemplate() { return template_.get(); }
		/// Get the project state
		ProjectState GetProjectState() const { return projectState_; }

		/// Set the project directory
		void SetProjectDir(const std::string& projectDir);

	private:
		/// Initialize vital library components
		void PreInitialization();

		/// The engine context
		std::shared_ptr<TPGEContext> context_;
		/// The project directory 
		std::string projectDir_;
		/// The generated root graph
		std::shared_ptr<GeneratedGraph> rootGraph_;
		/// The loaded template tree
		std::shared_ptr<Template> template_;
		/// The project state
		ProjectState projectState_;
	};
}