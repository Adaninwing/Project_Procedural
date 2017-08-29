// library includes
#include "DataTemplate.h"
#include "GraphTemplate.h"

// header
#include "ComboTemplate.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	ComboTemplate::ComboTemplate() : 
		TemplateItem()
	{

	}

	ComboTemplate::~ComboTemplate()
	{

	}

	void ComboTemplate::AddComboTemplate(std::string name, std::shared_ptr<ComboTemplate> combo)
	{
		combo->SetIndex(combos_.Size());
		combos_.Insert(combos_.Size(), name, combo);
	}

	
	void ComboTemplate::AddDataTemplate(std::string name, std::shared_ptr<DataTemplate> data)
	{
		data->SetIndex(data_.Size());
		data_.Insert(data_.Size(), name, data);
	}

	std::shared_ptr<ComboTemplate> ComboTemplate::GetComboTemplate(std::string name)
	{
		return combos_[name];
	}

	std::shared_ptr<ComboTemplate> ComboTemplate::GetComboTemplateAt(unsigned index)
	{
		return combos_[index];
	}

	std::shared_ptr<DataTemplate> ComboTemplate::GetDataTemplate(std::string name)
	{
		return data_[name];
	}

	std::shared_ptr<DataTemplate> ComboTemplate::GetDataTemplateAt(unsigned index)
	{
		return data_[index];
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}