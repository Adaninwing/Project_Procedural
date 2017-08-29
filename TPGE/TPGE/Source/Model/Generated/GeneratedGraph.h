#pragma once

/// include
#include <memory>
#include <string>
#include <deque>

/// base includes
#include "Attributed.h"

/// Library includes
#include "Util/IndexedMap.h"

namespace TPGE
{
	/// forward declaration
	class GeneratedData;
	class GeneratedNode;

	class GeneratedGraph : public Attributed
	{
	public:
		TPGE_OBJECT(GeneratedGraph, Attributed)

		GeneratedGraph(std::shared_ptr<TPGEContext> context);
		~GeneratedGraph();

		/// comparison operator for removal from IndexedMap
		bool operator==(const GeneratedGraph& other) const;
		/// comparison operator for removal from IndexedMap
		bool operator!=(const GeneratedGraph& other) const;

		/// Initialize class
		virtual void Initialize();

		/// Add a child graph
		void AddChild(unsigned index, std::string name, std::shared_ptr<GeneratedGraph> graph);
		/// Add a child graph
		void AddChild(unsigned index, std::shared_ptr<GeneratedGraph> graph);
		/// Add a child graph
		void AddChild(std::string name, std::shared_ptr<GeneratedGraph> graph);
		/// Add a data reference
		void AddData(unsigned index, std::string name, std::shared_ptr<GeneratedData> data);
		/// Add a data reference
		void AddData(unsigned index, std::shared_ptr<GeneratedData> data);
		/// Add a data reference
		void AddData(std::string name, std::shared_ptr<GeneratedData> data);
		/// Add a node
		void AddNode(unsigned index, std::string name, std::shared_ptr<GeneratedNode> node);
		/// Add a child graph
		void AddNode(unsigned index, std::shared_ptr<GeneratedNode> node);
		/// Add a node
		void AddNode(std::string name, std::shared_ptr<GeneratedNode> node);
		/// Clear all children
		void ClearChildren();
		/// Clear all data references
		void ClearData();
		/// Clear all node references
		void ClearNodes();
		/// Remove a child graph
		bool RemoveChild(unsigned index);
		/// Remove a child graph
		bool RemoveChild(std::string name);
		/// Remove a data reference
		bool RemoveData(unsigned index);
		/// Remove a data reference
		bool RemoveData(std::string name);
		/// Remove a node reference
		bool RemoveNode(unsigned index);
		/// Remove a node reference
		bool RemoveNode(std::string name);
		/// Remove the parent rendering this graph an orphan
		void RemoveParent();

		/// Get a child graph, if not existent try to generate it
		std::shared_ptr<GeneratedGraph> GetChild(unsigned index);
		/// Get a child graph, if not existant try to generate it
		std::shared_ptr<GeneratedGraph> GetChild(std::string name);
		/// Get the generated data for the graph
		std::shared_ptr<GeneratedData> GetData(unsigned index);
		/// Get the generated data for the graph
		std::shared_ptr<GeneratedData> GetData(std::string name);
		/// Get a pointer to the nodes map
		std::shared_ptr<IndexedMap<GeneratedNode> > GetNodes() { return std::make_shared<IndexedMap<GeneratedNode> >(nodes_); }
		/// Get the current number of children
		size_t GetNumChildren() const { return children_.Size(); }
		/// Get the current number of children
		size_t GetNumData() const { return data_.Size(); }
		/// Get the parent graph
		std::shared_ptr<GeneratedGraph> GetParent() { return parent_; };
		/// Get the parent graph
		std::shared_ptr<GeneratedGraph> GetParentConst() const { return parent_; }
		/// Get a path of unsigned ints to this object in the hierarchy
		std::deque<std::string> GetPathString();
		/// Get a path of strings to this object in the hierarchy
		std::deque<unsigned> GetPathUnsigned();
		/// Get the generated node for the graph
		std::shared_ptr<GeneratedNode> GetNode(unsigned index);
		/// Get the generated node for the graph
		std::shared_ptr<GeneratedNode> GetNode(std::string name);

		/// Set the parent graph
		void SetParent(std::shared_ptr<GeneratedGraph> parent) { parent_ = parent; }

	private:
		/// The child graphs are referenced here
		IndexedMap<GeneratedGraph> children_;
		/// The generated data for the graph is referenced here
		IndexedMap<GeneratedData> data_;
		/// The generated nodes for the graph are referenced here
		IndexedMap<GeneratedNode> nodes_;
		/// The parent graph reference
		std::shared_ptr<GeneratedGraph> parent_;
	};
}
