#pragma once
/// includes
#include <memory>
#include <string>

/// base include
#include "Attributed.h"

namespace TPGE
{
	// orwr declaration
	class GeneratedEdge;

	class GeneratedNode : public Attributed
	{
	public:
		TPGE_OBJECT(GeneratedNode, Attributed)

		GeneratedNode(std::shared_ptr<TPGEContext> context);
		~GeneratedNode();

		// Add a node
		void AddEdge(unsigned index, std::string name, std::shared_ptr<GeneratedEdge> edge);
		/// Add a node
		void AddEdge(unsigned index, std::shared_ptr<GeneratedEdge> edge);
		/// Add a node
		void AddEdge(std::string name, std::shared_ptr<GeneratedEdge> edge);
		/// Remove a node
		bool RemoveEdge(unsigned index);
		/// Remove a node
		bool RemoveEdge(std::string name);
		/// Remove all edges
		void ClearEdges();

		/// Get the node at index
		std::shared_ptr<GeneratedEdge> GetEdge(unsigned index);
		/// Get the node by name
		std::shared_ptr<GeneratedEdge> GetEdge(std::string name);

	private:
		/// Egdes
		IndexedMap<GeneratedEdge> edges_;
	};
}