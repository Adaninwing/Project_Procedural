
// header
#include "TPGEContext.h"

// library includes
#include "TPGEObject.h"

namespace TPGE
{
	//===============================================================
	// P U B L I C
	//===============================================================
	TPGEContext::TPGEContext()
	{
	}

	TPGEContext::~TPGEContext()
	{
	}

	void TPGEContext::RegisterSubsystem(std::shared_ptr<TPGEObject> system)
	{
		subsystems_.insert(std::pair<std::string, std::shared_ptr<TPGEObject> >(system->GetTypeName(), system));
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}