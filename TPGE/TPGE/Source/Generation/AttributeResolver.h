#pragma once
/// includes
#include <memory>

/// base class
#include "Engine/TPGEObject.h"

/// engine incudes
#include "Util/Variant.h"


namespace TPGE
{
	const std::string _constraints[16] =
	{
		"Alpha",
		"Beta",
		"Dev",
		"Distribution",
		"Fixed",
		"Generator",
		"Lambda",
		"M",
		"Max",
		"Mean",
		"Min",
		"N",
		"P",
		"K",
		"S",
		"Seed"
	};

	/// forward declaration
	struct Attribute;
	class Random;

	class AttributeResolver : public TPGEObject
	{
	public:
		TPGE_OBJECT(AttributeResolver, TPGEObject)

		AttributeResolver(std::shared_ptr<TPGEContext> context);
		~AttributeResolver();

		/// Generate an Attribute from constraints only
		std::shared_ptr<Variant> GenerateAttribute(std::shared_ptr<Attribute> attr);

	protected:

	private:
		/// Generate the random number generator
		std::shared_ptr<Random> GenerateRandomizer(std::shared_ptr<Attribute> attr);

	};
}