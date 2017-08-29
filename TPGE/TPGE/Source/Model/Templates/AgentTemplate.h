#pragma once

/// includes
#include <map>
#include <memory>
#include <string>

/// header
#include "TemplateItem.h"

/// library includes
#include "Model/Attributes.h"
#include "Model/AgentType.h"

namespace TPGE
{
	// forward declaration of classes
	class TechniqueTemplate;


	class AgentTemplate : public TemplateItem
	{
	public:
		AgentTemplate();
		~AgentTemplate();

		/// Get the agent type
		AgentType GetAgentType() const { return agentType_; };
		/// Get the mask to work on
		std::string& GetMask() const { return const_cast<std::string&>(mask_); };
		/// Get the value taken as mask parameter
		std::shared_ptr<Attribute> GetMaskValue() const { return maskValue_; };
		/// Get an agent template
		std::shared_ptr<TechniqueTemplate> GetTechniqeTemplate() { return technique_; }
		/// Get the number of tokens of this agent
		std::shared_ptr<Attribute> GetTokens() const { return tokens_; };

		/// Get the agent type
		void SetAgentType(AgentType type) { agentType_ = type; };
		/// Set the mask to work on
		void SetMask(const std::string& mask) { mask_ = mask; };
		/// Set the value taken as mask parameter
		void SetMaskValue(std::shared_ptr<Attribute> value) { maskValue_ = value; };
		/// Add an agent template
		void SetTechniqueTemplate(std::shared_ptr<TechniqueTemplate> technique) { technique_ = technique; }
		/// Set the number of tokens of this agent
		void SetTokens(std::shared_ptr<Attribute> tokens) { tokens_ = tokens; };

	protected:
		/// the agent type
		AgentType agentType_;
		/// the mask to work on
		std::string mask_;
		/// the value taken as mask parameter
		std::shared_ptr<Attribute> maskValue_;
		/// the technique of the template
		std::shared_ptr<TechniqueTemplate> technique_;
		/// the number of tokens of this agent
		std::shared_ptr<Attribute> tokens_;

	private:

	};
}