#pragma once

/// includes
#include "TemplateItem.h"
#include <memory>
#include <string>

#include "Util/IndexedMap.h"

namespace TPGE
{
	// forward declaration of classes
	class ComboTemplate;


	class Template : public TemplateItem
	{
	public:
		Template();
		~Template();

		/// Add a combo template
		void AddComboTemplate(std::string name, std::shared_ptr<ComboTemplate> combo);

		/// Get a combo template
		std::shared_ptr<ComboTemplate> GetComboTemplate(std::string name);
		/// access the map at index to get the combo
		std::shared_ptr<ComboTemplate> GetComboTemplateAt(unsigned index);

	protected:
		/// the map of combos in the template
		IndexedMap<ComboTemplate> combos_;

	private:

	};
}