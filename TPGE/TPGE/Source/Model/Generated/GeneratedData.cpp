// library includes

// header
#include "GeneratedData.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	GeneratedData::GeneratedData(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context),
		built_(false)
	{

	}

	GeneratedData::~GeneratedData()
	{

	}

	void GeneratedData::AddContentVariable(unsigned index, std::string name, std::string value)
	{
		if (built_)
		{
			NArray<Variant>::NArraySize arraySize;
			for (unsigned i = 0; i < dims_.Size(); i++)
				arraySize.push_back(*dims_[i]);
			std::shared_ptr<NArray<Variant> > arr = std::make_shared<NArray<Variant> >(dims_.Size(), arraySize);
			arr->Fill(Variant(value));
			content_.Insert(index, name, arr);
		}
	}

	void GeneratedData::AddContentVariable(unsigned index, std::string value)
	{
		if (built_)
		{
			NArray<Variant>::NArraySize arraySize;
			for (unsigned i = 0; i < dims_.Size(); i++)
				arraySize.push_back(*dims_[i]);
			std::shared_ptr<NArray<Variant> > arr = std::make_shared<NArray<Variant> >(dims_.Size(), arraySize);
			arr->Fill(Variant(value));
			content_.Insert(index, arr);
		}
	}

	void GeneratedData::AddContentVariable(std::string name, std::string value)
	{
		if (built_)
		{
			NArray<Variant>::NArraySize arraySize;
			for (unsigned i = 0; i < dims_.Size(); i++)
				arraySize.push_back(*dims_[i]);
			std::shared_ptr<NArray<Variant> > arr = std::make_shared<NArray<Variant> >(dims_.Size(), arraySize);
			arr->Fill(Variant(value));
			content_.Insert(name, arr);
		}
	}

	void GeneratedData::AddContentVariable(unsigned index, std::string name, std::shared_ptr<NArray<Variant>> content)
	{
		if (built_)
		{
			content_.Insert(index, name, content);
		}
	}

	void GeneratedData::AddContentVariable(unsigned index, std::shared_ptr<NArray<Variant>> content)
	{
		if (built_)
		{
			content_.Insert(index, content);
		}
	}

	void GeneratedData::AddContentVariable(std::string name, std::shared_ptr<NArray<Variant>> content)
	{
		if (built_)
		{
			content_.Insert(name, content);
		}
	}

	void GeneratedData::AddDimension(unsigned index, std::string name, size_t value)
	{
		if(!built_)
			dims_.Insert(index, name, value);
	}
	
	void GeneratedData::AddDimension(unsigned index, size_t value)
	{
		if (!built_)
			dims_.Insert(index, value);
	}
	
	void GeneratedData::AddDimension(std::string name, size_t value)
	{
		if (!built_)
			dims_.Insert(name, value);
	}

	void GeneratedData::Build()
	{
		built_ = true;
	}

	std::shared_ptr<NArray<Variant> > GeneratedData::GetContent(unsigned index)
	{
		return content_[index];
	}
	
	std::shared_ptr<NArray<Variant> > GeneratedData::GetContent(std::string name)
	{
		return content_[name];
	}

	void GeneratedData::SetDim(unsigned index, size_t value)
	{
		if(!built_)
			*(dims_[index].get()) = value;
	}
	
	void GeneratedData::SetDim(std::string name, size_t value)
	{
		if(!built_)
			*(dims_[name].get()) = value;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}