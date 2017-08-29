
// used for boost::split
#define _SCL_SECURE_NO_WARNINGS

// includes
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <climits>

// header
#include "GraphTemplate.h"

// library includes
#include "DataTemplate.h"
#include "PassTemplate.h"
#include "Util/IndexedMap.h"

namespace TPGE
{
	//===============================================================
	// P U B L I C
	//===============================================================
	GraphTemplate::GraphTemplate() :
		TemplateItem()
	{

	}

	GraphTemplate::~GraphTemplate()
	{

	}

	void GraphTemplate::AddDataUse(std::string data)
	{
		dataUses_.push_back(data);
	}

	void GraphTemplate::AddMutipleDataUses(std::string string)
	{
		boost::split(dataUses_, string, boost::is_any_of(","), boost::token_compress_on);
	}

	void GraphTemplate::AddPassTemplate(unsigned index, std::string name, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(index, name, combo);
	}

	void GraphTemplate::AddPassTemplate(unsigned index, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(index, combo);
	}

	void GraphTemplate::AddPassTemplate(std::string name, std::shared_ptr<PassTemplate> combo)
	{
		passes_.Insert(name, combo);
	}

	std::string& GraphTemplate::GetDataUse(unsigned index) const
	{
		return const_cast<std::string&>(dataUses_[index]);
	}

	unsigned GraphTemplate::GetDataUse(std::string name) const
	{
		unsigned retVal = UINT_MAX;
		for (unsigned i = 0; i < dataUses_.size(); i++)
		{
			if (dataUses_[i] == name)
				return i;
		}
		return retVal;
	}

	std::shared_ptr<PassTemplate> GraphTemplate::GetPassTemplate(std::string name)
	{
		return passes_[name];
	}

	std::shared_ptr<PassTemplate> GraphTemplate::GetPassTemplate(unsigned index)
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