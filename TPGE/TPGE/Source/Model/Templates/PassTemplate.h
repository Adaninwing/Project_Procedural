#pragma once

/// includes
#include <memory>
#include <string>

/// base
#include "TemplateItem.h"

/// library includes
#include "Util/IndexedMap.h"

namespace TPGE
{
	// forward declaration of classes
	class AgentTemplate;


	class PassTemplate : public TemplateItem
	{
	public:
		PassTemplate();
		~PassTemplate();

		/// Add an agent template
		void AddAgentTemplate(std::string name, std::shared_ptr<AgentTemplate> agent);

		/// Get an agent template
		std::shared_ptr<AgentTemplate> GetAgentTemplate(unsigned index);
		/// Get an agent template
		std::shared_ptr<AgentTemplate> GetAgentTemplate(std::string name);
		/// Get the index of the pass
		unsigned GetNumAgents() const { return agentsMap_.Size(); }

		/// operator for comparison
		bool operator==(const PassTemplate& rhs) const;
		/// operator for comparison
		bool operator!=(const PassTemplate& rhs) const;

	protected:
		/// the map of agents in the template
		IndexedMap<AgentTemplate> agentsMap_;

	private:

	};
}