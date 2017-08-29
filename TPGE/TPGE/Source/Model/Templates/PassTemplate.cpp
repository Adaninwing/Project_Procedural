// library includes
#include "AgentTemplate.h"

// header
#include "PassTemplate.h"

namespace TPGE
{

	//===============================================================
	// O P E R A T O R S
	//===============================================================
	bool PassTemplate::operator==(const PassTemplate& rhs) const
	{
		return false;
	}
	
	bool PassTemplate::operator!=(const PassTemplate& rhs) const
	{
		return false;
	}

	//===============================================================
	// P U B L I C
	//===============================================================
	PassTemplate::PassTemplate() :
		TemplateItem()
	{

	}

	PassTemplate::~PassTemplate()
	{

	}

	void PassTemplate::AddAgentTemplate(std::string name, std::shared_ptr<AgentTemplate> agent)
	{
		agentsMap_.Insert(agentsMap_.Size(), name, agent);
	}

	std::shared_ptr<AgentTemplate> PassTemplate::GetAgentTemplate(unsigned index)
	{
		return agentsMap_[index];
	}

	std::shared_ptr<AgentTemplate> PassTemplate::GetAgentTemplate(std::string name)
	{
		return agentsMap_[name];
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}