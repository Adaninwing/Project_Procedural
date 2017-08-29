// includes
#include <memory>

// header
#include "TechniqueBase.h"

// library includes
#include "Generation/Agent.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	TechniqueBase::TechniqueBase(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context)
	{

	}

	TechniqueBase::~TechniqueBase()
	{

	}

	void TechniqueBase::InitializeConstants()
	{
		constantAttributesMap_ = IndexedVariantMap();
	}

	void TechniqueBase::Start()
	{
		// nothing to do: override
	}
	
	void TechniqueBase::Stop()
	{
		// nothing to do: override
	}

	bool TechniqueBase::SetConstant(std::string key, const Variant& attr)
	{
		std::shared_ptr<Variant> var = constantAttributesMap_[key];
		if (var)
			return var->Set(attr);
		else
			return false;
	}
	
	bool TechniqueBase::SetConstant(int index, const Variant& attr)
	{
		std::shared_ptr<Variant> var = constantAttributesMap_[index];
		if (var)
			return var->Set(index);
		else
			return false;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}