// library includes


// header
#include "TechniqueTemplate.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	TechniqueTemplate::TechniqueTemplate() :
		TemplateItem()
	{

	}

	TechniqueTemplate::~TechniqueTemplate()
	{

	}

	void TechniqueTemplate::AddAttribute(std::string name, std::shared_ptr<Attribute> attr)
	{
		attr->index_ = attributes_.Size();
		attributes_.Insert(attributes_.Size(), name, attr);
	}

	void TechniqueTemplate::AddValue(std::string variableName, std::string pathToAttribute)
	{
		valueMap_.Insert(valueMap_.Size(), variableName, std::make_pair(variableName, pathToAttribute));
	}

	std::shared_ptr<Attribute> TechniqueTemplate::GetAttribute(std::string name)
	{
		return attributes_[name];
	}

	std::shared_ptr<Attribute> TechniqueTemplate::GetAttribute(unsigned index)
	{
		return attributes_[index];
	}

	std::shared_ptr<std::pair<std::string, std::string> >  TechniqueTemplate::GetPathToAttribute(const std::string& name)
	{
		return valueMap_[name];
	}

	std::shared_ptr<std::pair<std::string, std::string> >  TechniqueTemplate::GetPathToAttribute(unsigned index)
	{
		return valueMap_[index];
	}


	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}