// library includes

// header
#include "Attributed.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	Attributed::Attributed(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context),
		index_(0),
		name_("")
	{

	}

	Attributed::~Attributed()
	{

	}

	void Attributed::AddAttribute(unsigned index, std::string name, const Variant& attribute)
	{
		attributes_.Insert(index, name, attribute);
	}
	
	void Attributed::AddAttribute(unsigned index, const Variant& attribute)
	{
		attributes_.Insert(index, attribute);
	}
	
	void Attributed::AddAttribute(std::string name, const Variant& attribute)
	{
		attributes_.Insert(name, attribute);
	}
	
	bool Attributed::RemoveAttribute(unsigned index)
	{
		return attributes_.Erase(index);
	}
	
	bool Attributed::RemoveAttribute(std::string name)
	{
		return attributes_.Erase(name);
	}
	
	void Attributed::ClearAttributes()
	{
		attributes_.Clear();
	}

	std::shared_ptr<Variant> Attributed::GetAttribute(unsigned index)
	{
		return attributes_[index];
	}
	
	std::shared_ptr<Variant> Attributed::GetAttribute(std::string name)
	{
		return attributes_[name];
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================

}