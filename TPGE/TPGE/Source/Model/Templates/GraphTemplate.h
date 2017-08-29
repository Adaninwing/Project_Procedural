#pragma once

/// includes
#include <map>
#include <memory>
#include <string>
#include <vector>	

/// include base
#include "TemplateItem.h"

/// library includes
#include "Model/Attributes.h"
#include "Model/Edge.h"

namespace TPGE
{
	// forward declaration of classes
	class DataTemplate;
	class PassTemplate;

	/// struct to hold a node template
	struct GraphTemplateNode 
	{
		/// the attributes of this node
		AttributeMap attributes_;
	};

	/// struct to hold an edge template
	struct GraphTemplateEdge
	{
		/// the attributes of this edge
		AttributeMap attributes_;
		/// the type of this edge
		EdgeType type_;
	};

	class GraphTemplate : public TemplateItem
	{
	public:
		GraphTemplate();
		~GraphTemplate();

		/// Add used Data
		void AddDataUse(std::string data);
		/// Add multiple used Data
		void AddMutipleDataUses(std::string string);
		// Add a combo template
		void AddPassTemplate(unsigned index, std::string name, std::shared_ptr<PassTemplate> pass);
		/// Add a combo template
		void AddPassTemplate(unsigned index, std::shared_ptr<PassTemplate> pass);
		/// Add a combo template
		void AddPassTemplate(std::string name, std::shared_ptr<PassTemplate> pass);

		/// Get used data name
		std::string& GetDataUse(unsigned index) const;
		/// Get used data index
		unsigned GetDataUse(std::string name) const;
		/// Get used data vector
		std::vector<std::string>& GetDataUses() { return dataUses_; };
		/// Get the edge template of this Graph
		std::shared_ptr<GraphTemplateEdge> GetEdgeTemplate() { return edge_; }
		/// Get the node template of this Graph
		std::shared_ptr<GraphTemplateNode> GetNodeTemplate() { return node_; }
		/// Get the number of passes
		unsigned GetNumPassTemplates() { return passes_.Size(); }
		/// Get a combo template
		std::shared_ptr<PassTemplate> GetPassTemplate(std::string name);
		/// access the map at index
		std::shared_ptr<PassTemplate> GetPassTemplate(unsigned index);

		/// Get the edge template of this Graph
		void SetEdgeTemplate(std::shared_ptr<GraphTemplateEdge> edge) { edge_ = edge; }
		/// Get the node template of this Graph
		void SetNodeTemplate(std::shared_ptr<GraphTemplateNode> node) { node_ = node; }

	protected:
		/// the map of child passes in the template
		std::vector<std::string> dataUses_;
		/// The edge template of this Graph
		std::shared_ptr<GraphTemplateEdge> edge_;
		// The edge template of this Graph
		std::shared_ptr<GraphTemplateNode> node_;
		/// the map of child passes in the template
		IndexedMap<PassTemplate> passes_;

	private:

	};
}