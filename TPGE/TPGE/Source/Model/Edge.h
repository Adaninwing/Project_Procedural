#pragma once

/// includes
#include <string>

namespace TPGE
{
	/// enum for types of edges
	enum EdgeType
	{
		DIRECTED = 0,
		UNDIRECTED = 1
	};
	EdgeType GetEdgeType(std::string string);
}