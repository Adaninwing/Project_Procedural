#pragma once

/// includes
#include <memory>
#include <map>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"

namespace TPGE
{
	/// forward declarations
	class AgentTemplate;
	class ComboTemplate;
	class DataTemplate;
	class GraphTemplate;
	class PassTemplate;
	class TechniqueTemplate;
	class Template;

	class IFileLoader : public TPGEObject
	{
	public:

		TPGE_BASE_OBJECT(IFileLoader)

		IFileLoader(std::shared_ptr<TPGEContext> context);
		~IFileLoader();

		/// Load a combo template
		virtual void LoadCombo(std::shared_ptr<ComboTemplate> combo, std::map<std::string, std::shared_ptr<DataTemplate> >& dataToLoadRef, std::map<std::string, std::shared_ptr<GraphTemplate> >& graphToLoadRef) = 0;
		/// Load a data template
		virtual void LoadData(std::shared_ptr<DataTemplate> data, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef) = 0;
		/// Load a graph template
		virtual void LoadGraph(std::shared_ptr<GraphTemplate> graph, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef) = 0;
		/// Load a pass template
		virtual void LoadPass(std::shared_ptr<PassTemplate> pass, std::map<std::string, std::shared_ptr<TechniqueTemplate> >& techniquesToLoadRef) = 0;
		/// Load a technique template
		virtual void LoadTechnique(std::shared_ptr<TechniqueTemplate> technique) = 0;
		/// Load a template and return it
		virtual std::shared_ptr<Template> LoadTemplate(const std::string& path, std::map<std::string, std::shared_ptr<ComboTemplate> >& combosToLoadRef) = 0;

	private:
	};
}
