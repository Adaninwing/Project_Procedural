#pragma once
/// includes
#include <vector>

/// library includes
#include "IDataLoader.h"

namespace TPGE
{
	/// forward declarations

	class RawDataLoader : public IDataLoader
	{
	public:

		TPGE_OBJECT(RawDataLoader, IDataLoader)

		RawDataLoader(std::shared_ptr<TPGEContext> context);
		~RawDataLoader();

		/// load a file and fill into NArray
		virtual std::shared_ptr<NArray<Variant> > LoadData(const std::string& path);

	protected:

	private:
		/// Transform a line of dims to a vector
		std::vector<size_t> GetDims(const std::string& string);
	};

}
