// library includes
#include "ComboTemplate.h"

// header
#include "Template.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	Template::Template() : 
		TemplateItem()
	{

	}

	Template::~Template()
	{

	}

	void Template::AddComboTemplate(std::string name, std::shared_ptr<ComboTemplate> combo)
	{
		combo->SetIndex(combos_.Size());
		combos_.Insert(combos_.Size(), name, combo);
	}

	std::shared_ptr<ComboTemplate> Template::GetComboTemplate(std::string name)
	{
		return combos_[name];
	}
	
	std::shared_ptr<ComboTemplate> Template::GetComboTemplateAt(unsigned index)
	{
		return combos_[index];
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}