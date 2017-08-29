// library includes
#include "PassTemplate.h"

// header
#include "DataTemplate.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	DataTemplate::DataTemplate() :
		TemplateItem()
	{

	}

	DataTemplate::~DataTemplate()
	{

	}

	void DataTemplate::AddAttribute(unsigned index, std::string name, std::shared_ptr<Attribute> attr)
	{
		attributes_.Insert(index, name, attr);
	}
	
	void DataTemplate::AddAttribute(unsigned index, std::shared_ptr<Attribute> attr)
	{
		attributes_.Insert(index, attr);
	}
	
	void DataTemplate::AddAttribute(std::string name, std::shared_ptr<Attribute> attr)
	{
		attributes_.Insert(name, attr);
	}

	void DataTemplate::AddPassTemplate(unsigned index, std::string name, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(index, name, combo);
	}
	
	void DataTemplate::AddPassTemplate(unsigned index, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(index, combo);
	}
	
	void DataTemplate::AddPassTemplate(std::string name, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(name, combo);
	}

	std::shared_ptr<Attribute> DataTemplate::GetAttribute(std::string name)
	{
		return attributes_[name];
	}
	
	std::shared_ptr<Attribute> DataTemplate::GetAttribute(unsigned index)
	{
		return attributes_[index];
	}

	std::shared_ptr<PassTemplate> DataTemplate::GetPassTemplate(std::string name)
	{
		return passes_[name];
	}

	std::shared_ptr<PassTemplate> DataTemplate::GetPassTemplate(unsigned index)
	{
		return passes_[index];
	}


	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}