// library includes
#include "GeneratedNode.h"

// header
#include "GeneratedEdge.h"

namespace TPGE
{
	//===============================================================
	// O P E R A T O R
	//===============================================================
	bool GeneratedEdge::operator==(const GeneratedEdge& other) const
	{
		return (eType_ == other.GetEdgeType() && lNode_ == other.GetLeftConst() && rNode_ == other.GetRightConst());
	}
	
	bool GeneratedEdge::operator!=(const GeneratedEdge& other) const
	{
		return !(*this == other);
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	GeneratedEdge::GeneratedEdge(std::shared_ptr<TPGEContext> context) :
		GeneratedEdge(context, UNDIRECTED)
	{

	}

	GeneratedEdge::GeneratedEdge(std::shared_ptr<TPGEContext> context, EdgeType etype) :
		Attributed(context),
		eType_(etype)
	{

	}

	GeneratedEdge::~GeneratedEdge()
	{

	}

	void GeneratedEdge::SetEdgeType(EdgeType type)
	{
		eType_ = type;
	}

	void GeneratedEdge::SetLeft(std::shared_ptr<GeneratedNode> left)
	{
		lNode_ = left;
	}
	
	void GeneratedEdge::SetRight(std::shared_ptr<GeneratedNode> right)
	{
		rNode_ = right;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
}
