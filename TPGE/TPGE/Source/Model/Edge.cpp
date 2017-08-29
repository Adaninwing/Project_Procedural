// includes
#include "Edge.h"
#include <map>

namespace TPGE
{
	//===============================================================
	// G L O B A L
	//===============================================================
	EdgeType GetEdgeType(std::string string) {
		std::map<std::string, EdgeType> _edgeTypeMap = std::map<std::string, EdgeType>();
		_edgeTypeMap.insert(std::pair<std::string, EdgeType>("Directed", EdgeType::DIRECTED));
		_edgeTypeMap.insert(std::pair<std::string, EdgeType>("Undirected", EdgeType::UNDIRECTED));

		std::map<std::string, EdgeType>::iterator it = _edgeTypeMap.find(string);
		if (it != _edgeTypeMap.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return EdgeType::UNDIRECTED;
		}
	}
}