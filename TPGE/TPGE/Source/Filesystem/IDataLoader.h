#pragma once

/// includes
#include <memory>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"
#include "Util/NArray.h"
#include "Util/Variant.h"

namespace TPGE
{
	/// forward declarations

	class IDataLoader : public TPGEObject
	{
	public:

		TPGE_BASE_OBJECT(IDataLoader)

		IDataLoader(std::shared_ptr<TPGEContext> context);
		~IDataLoader();
		
		/// load a file and fill into NArray
		virtual std::shared_ptr<NArray<Variant>> LoadData(const std::string& path) = 0;

	protected:

	private:
	};
}

