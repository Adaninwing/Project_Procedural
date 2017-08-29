// includes
#include <iostream>
#include <fstream>
#include <sstream>

// header
#include "RawDataLoader.h"

// Library includes
//-

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	RawDataLoader::RawDataLoader(std::shared_ptr<TPGEContext> context) :
		IDataLoader(context)
	{

	}

	RawDataLoader::~RawDataLoader()
	{

	}

	std::shared_ptr<NArray<Variant> > RawDataLoader::LoadData(const std::string& path)
	{
		std::shared_ptr<NArray<Variant> > ret;

		std::string type;
		std::string dimsS;
		std::string line;
		size_t i = 0;
		std::ifstream myfile(path);
		if (myfile.is_open())
		{
			getline(myfile, type);
			getline(myfile, dimsS);
			std::vector<size_t> dims = GetDims(dimsS);

			ret = std::make_shared<NArray<Variant> >(dims.size(), dims);
			ret->Fill(Variant(type));
			while (getline(myfile, line))
			{
				if (i < ret->GetLength())
					ret->operator[](i++).Set(line);
				else
					break;
			}
			myfile.close();
		}

		return ret;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	std::vector<size_t> RawDataLoader::GetDims(const std::string& string)
	{
		std::stringstream iss(string);

		size_t number;
		std::vector<size_t> dims;
		while (iss >> number)
			dims.push_back(number);

		return dims;
	}
}