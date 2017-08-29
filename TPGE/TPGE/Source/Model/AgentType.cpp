// includes
#include <map>

// include header
#include "AgentType.h"

namespace TPGE
{
	//===============================================================
	// G L O B A L
	//===============================================================
	AgentType GetAgentType(std::string string) {
		std::map<std::string, AgentType> _agentTypeMap = std::map<std::string, AgentType>();
		_agentTypeMap.insert(std::pair<std::string, AgentType>("Singlular", AgentType::SINGULAR));
		_agentTypeMap.insert(std::pair<std::string, AgentType>("Masked", AgentType::MASKED));
		_agentTypeMap.insert(std::pair<std::string, AgentType>("Graph", AgentType::GRAPH));

		std::map<std::string, AgentType>::iterator it = _agentTypeMap.find(string);
		if (it != _agentTypeMap.end())
		{
			return std::get<1>(*it);
		}
		else
		{
			return AgentType::SINGULAR;
		}
	}
}