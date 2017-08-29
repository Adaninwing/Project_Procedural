#pragma once

/// includes
#include "TemplateItem.h"
#include <memory>
#include <string>

#include "Util/IndexedMap.h"

namespace TPGE
{
	// forward declaration of classes
	class DataTemplate;
	class GraphTemplate;

	class ComboTemplate : public TemplateItem
	{
	public:
		ComboTemplate();
		~ComboTemplate();

		/// Add a combo template
		void AddComboTemplate(std::string name, std::shared_ptr<ComboTemplate> combo);
		/// Add a data template
		void AddDataTemplate(std::string name, std::shared_ptr<DataTemplate> data);

		/// Set the graph
		void SetGraph(std::shared_ptr<GraphTemplate> graph) { graph_ = graph; }

		/// Get a combo template
		std::shared_ptr<ComboTemplate> GetComboTemplate(std::string name);
		/// access the map at index to get the pair
		std::shared_ptr<ComboTemplate> GetComboTemplateAt(unsigned index);
		/// Get a data template
		std::shared_ptr<DataTemplate> GetDataTemplate(std::string name);
		/// access the map at index to get the pair
		std::shared_ptr<DataTemplate> GetDataTemplateAt(unsigned index);
		/// Get the graph of this template
		std::shared_ptr<GraphTemplate> GetGraph() const { return graph_; }

	protected:
		/// the map of child combos in the template
		IndexedMap<ComboTemplate> combos_;
		/// the map of data templates in the template
		IndexedMap<DataTemplate> data_;
		/// the data template in the template
		std::shared_ptr<GraphTemplate> graph_;

	private:

	};
}