#pragma once

/// includes
#include <string>

namespace TPGE
{
	/// enum for types of agents
	enum AgentType
	{
		SINGULAR = 0,
		MASKED = 1,
		GRAPH = 2
	};
	AgentType GetAgentType(std::string string);

}
