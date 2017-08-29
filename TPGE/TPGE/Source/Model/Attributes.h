#pragma once

/// includes
#include <limits>
#include <map>
#include <memory>
#include <string>

/// Engine Includes
#include "Util/IndexedMap.h"

namespace TPGE
{
	/// forwdard declaration
	struct Attribute;
	struct Constraint;

	/// typedefs
	typedef IndexedMap<Attribute> AttributeMap;
	typedef IndexedMap<Constraint> ConstraintMap;

	/// attribute struct
	struct Attribute
	{
		Attribute() : index_(UINT_MAX), name_("") {}

		/// the constraints placed upon this attribute
		ConstraintMap constraints_;
		/// The index of the attribute for reference
		unsigned index_;
		/// The name of the attribute for reference
		std::string name_;
		/// The value of the attribute
		std::shared_ptr<Variant> value_;

		bool operator==(const Attribute& other) const { return name_ == other.name_ && name_ != "" || index_ == other.index_ && index_ != UINT_MAX; }
		bool operator!=(const Attribute& other) const { return !(*this == other); }
	};


	/// constraint struct
	struct Constraint
	{
		Constraint() : index_(UINT_MAX), name_("") {}

		/// The index of the constraint for reference
		unsigned index_;
		/// The type of the constraint for reference
		std::string name_;
		/// The value of the constraint
		std::shared_ptr<Variant> value_;

		bool operator==(const Constraint& other) const { return name_ == other.name_ && name_ != "" || index_ == other.index_ && index_ != UINT_MAX; }
		bool operator!=(const Constraint& other) const { return !(*this == other); }
	};
}