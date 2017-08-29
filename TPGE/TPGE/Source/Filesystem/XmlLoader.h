#pragma once

/// include header
#include "IFileLoader.h"

/// library incues

/// forward declaration
namespace pugi 
{
	class xml_node;
}

namespace TPGE
{
	struct Attribute;
	class AgentTemplate;
	class ComboTemplate;
	class DataTemplate;
	class GraphTemplate;
	class PassTemplate;
	class TechniqueTemplate;
	class Template;

	class XmlLoader : public IFileLoader
	{
	public:
		TPGE_OBJECT(XmlLoader, IFileLoader)

		XmlLoader(std::shared_ptr<TPGEContext> context);
		~XmlLoader();

		/// Load a combo template
		virtual void LoadCombo(std::shared_ptr<ComboTemplate> combo, std::map<std::string, std::shared_ptr<DataTemplate> >& dataToLoadRef, std::map<std::string, std::shared_ptr<GraphTemplate> >& graphToLoadRef);
		/// Load a data template
		virtual void LoadData(std::shared_ptr<DataTemplate> data, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef);
		/// Load a graph template
		virtual void LoadGraph(std::shared_ptr<GraphTemplate> graph, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef);
		/// Load a pass template
		virtual void LoadPass(std::shared_ptr<PassTemplate> pass, std::map<std::string, std::shared_ptr<TechniqueTemplate> >& techniquesToLoadRef);
		/// Load a technique template
		virtual void LoadTechnique(std::shared_ptr<TechniqueTemplate> technique);
		/// Load a template and return it
		virtual std::shared_ptr<Template> LoadTemplate(const std::string& path, std::map<std::string, std::shared_ptr<ComboTemplate> >& combosToLoadRef);

	private:
		/// Load a attributes from template
		std::shared_ptr<Attribute> LoadAttribute(pugi::xml_node node);
		/// function called recursivey to create combo tree
		void RecursiveCreateComboTree(pugi::xml_node root, std::shared_ptr<ComboTemplate> attatchTo, std::map<std::string, std::shared_ptr<ComboTemplate> >& combosToLoadRef);

	};
}