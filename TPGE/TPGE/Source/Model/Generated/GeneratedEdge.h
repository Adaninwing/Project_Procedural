#pragma once

/// includes
#include <memory>
#include <string>

/// base include
#include "Attributed.h"

/// library includes
#include "Model/Edge.h"

namespace TPGE
{
	/// forward declararation
	class GeneratedNode;
	enum EdgeType;

	class GeneratedEdge : public Attributed
	{
	public:
		TPGE_OBJECT(GeneratedEdge, Attributed)

		GeneratedEdge(std::shared_ptr<TPGEContext> context);
		GeneratedEdge(std::shared_ptr<TPGEContext> context, EdgeType etype);
		~GeneratedEdge();

		/// equals operator for indexed map
		bool operator==(const GeneratedEdge& other) const;
		/// not equals operator for indexed map
		bool operator!=(const GeneratedEdge& other) const;

		/// Get the left node
		EdgeType GetEdgeType() const { return eType_; }
		/// Get the left node
		std::shared_ptr<GeneratedNode> GetLeft() { return lNode_; }
		/// Get the right node
		std::shared_ptr<GeneratedNode> GetRight() { return rNode_; }
		/// Get the left node (const return)
		std::shared_ptr<GeneratedNode> GetLeftConst() const { return lNode_; }
		/// Get the right node (const return)
		std::shared_ptr<GeneratedNode> GetRightConst() const { return rNode_; }

		/// Set the left node
		void SetEdgeType(EdgeType type);
		/// Set the left node
		void SetLeft(std::shared_ptr<GeneratedNode> left);
		/// Set the right node
		void SetRight(std::shared_ptr<GeneratedNode> right);

	private:
		/// The type of the generated edge
		EdgeType eType_;
		/// the left node
		std::shared_ptr<GeneratedNode> lNode_;
		/// the right node
		std::shared_ptr<GeneratedNode> rNode_;
	};
}