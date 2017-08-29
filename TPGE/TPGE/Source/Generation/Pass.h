#pragma once

/// includes
#include <memory>
#include <string>
#include <vector>

/// Library includes
#include "Generation/Agent.h"

namespace TPGE
{
	struct Pass
	{
		std::string name_;
		std::vector<std::shared_ptr<Agent> > agents_;
	};
}
