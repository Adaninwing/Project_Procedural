#pragma once

/// includes
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <map>
#include <string>

/// libraary includes
/// -

/// defines
#define TPGE_REGISTER_VARIANT_TYPE(string, type) GetMap()->insert(std::make_pair(string, &CreateInstance<type>))

namespace TPGE
{
	/// forward declaration
	class Variant;
	class VariantFactory;

	/// typedefs
	typedef boost::variant<bool, int, unsigned, float, double, std::string> VariantType;
	typedef std::map<std::string, VariantType(*)()> VariantTypeMap;
	typedef std::map<std::string, Variant> VariantMap;

	/// helper struct
	class VariantFactory {
	public:
		/// Create an instance of VariantType from a given type
		template<typename T> static VariantType CreateInstance()
		{
			return VariantType(T());
		}

		/// Create an instance of VariantType from a given string by accessing the static map
		static VariantType CreateInstance(std::string const& type)
		{
			VariantTypeMap::iterator it = GetMap()->find(type);
			if (it == GetMap()->end())
				return 0;
			return it->second();
		}

		static void RegisterVariantTypes(VariantTypeMap* map)
		{
			TPGE_REGISTER_VARIANT_TYPE("bool", bool);
			TPGE_REGISTER_VARIANT_TYPE("int", int);
			TPGE_REGISTER_VARIANT_TYPE("unsigned", unsigned);
			TPGE_REGISTER_VARIANT_TYPE("float", float);
			TPGE_REGISTER_VARIANT_TYPE("double", double);
			TPGE_REGISTER_VARIANT_TYPE("string", std::string);
		}

		/// Get the map
		static VariantTypeMap* GetMap()
		{
			if (!typeMap_)
			{
				// never delete'ed. (exist until program termination)
				// because we can't guarantee correct destruction order 
				typeMap_ = std::make_shared<VariantTypeMap>();
				RegisterVariantTypes(typeMap_.get());
			}
			return typeMap_.get();
		}

	private:
		/// the static variant map that stays static untill program termination
		static std::shared_ptr<VariantTypeMap> typeMap_;
	};

	/// The variant class
	class Variant
	{
	public:
		Variant() :
			Variant("string")
		{ }
		Variant(std::string type) :
			type_(type)
		{
			value_ = VariantFactory::CreateInstance(type);
		}
		Variant(const Variant& toCopy) :
			type_(toCopy.GetType())
		{
			value_ = VariantFactory::CreateInstance(toCopy.GetType());
			Set(toCopy);
		}
		~Variant() {}

		bool operator==(const Variant& rhs) const
		{
			if (rhs.Which() == Which())
			{
				return rhs.GetRaw() == value_;
			}
			else
				return false;
		}
		bool operator!=(const Variant& rhs) const
		{
			return !(*this == rhs);
		}
		bool operator<(const Variant& rhs) const
		{
			if (rhs.Which() == Which())
				return value_ < rhs.GetRaw();
			else
				return false;
		}

		/// Get the which value
		int Which() const
		{
			return value_.which();
		}

		/// Get the held value 
		template<typename T> T Get() const
		{
			return boost::get<T>(value_);
		}
		/// Get the held value as bool
		bool GetBool() const
		{
			return boost::get<bool>(value_);
		}
		/// Get the held value as int
		int GetInt() const
		{
			return boost::get<int>(value_);
		}
		/// Get the held value as unsigned
		unsigned GetUInt() const
		{
			return boost::get<unsigned>(value_);
		}
		/// Get the held value as float
		float GetFloat() const
		{
			return boost::get<float>(value_);
		}
		/// Get the held value as double
		double GetDouble() const
		{
			return boost::get<double>(value_);
		}
		/// Get the held value as string
		std::string GetString() const
		{
			switch (value_.which())
			{
			case 0:
				return std::to_string(GetBool());
			case 1:
				return std::to_string(GetInt());
			case 2:
				return std::to_string(GetUInt());
			case 3:
				return std::to_string(GetFloat());
			case 4:
				return std::to_string(GetDouble());
			default:
				return boost::get<std::string>(value_);
			}
		}
		/// Get the string type of the variant
		std::string& GetType() const
		{
			return const_cast<std::string&>(type_);
		}
		/// Get the raw value
		VariantType GetRaw() const
		{
			return value_;
		}

		/// Set from type if the variant has bool type returns false if held types don't match
		template<typename T> bool Set(T rhs)
		{
			return Set(rhs);
		}
		/// Set from bool if the variant has bool type returns false if held types don't match
		bool Set(bool rhs)
		{
			if (value_.which() == 0)
			{
				value_ = rhs;
				return true;
			}
			else
				return false;
		}
		/// Set from int if the variant has int type returns false if held types don't match
		bool Set(int rhs)
		{
			if(value_.which() == 1)
			{
				value_ = rhs;
				return true;
			}
			else
				return false;
		}
		/// Set from unisigned if the variant has unsigned type returns false if held types don't match
		bool Set(unsigned rhs)
		{
			if(value_.which() == 2)
			{
				value_ = rhs;
				return true;
			}
			else
				return false;
		}
		/// Set from float if the variant has foat type returns false if held types don't match
		bool Set(float rhs)
		{
			if(value_.which() == 3)
			{
				value_ = rhs;
				return true;
			}
			else
				return false;
		}
		/// Set from double if the variant has double type returns false if held types don't match
		bool Set(double rhs)
		{
			if(value_.which() == 4)
			{
				value_ = rhs;
				return true;
			}
			else
				return false;
		}
		/// Set from string will convert value to held value
		bool Set(std::string rhs)
		{
			switch (value_.which())
			{
			case 0: 
				value_ = boost::lexical_cast<bool>(rhs);
				break;
			case 1: 
				value_ = boost::lexical_cast<int>(rhs);
				break;
			case 2: 
				value_ = boost::lexical_cast<unsigned>(rhs);
				break;
			case 3: 
				value_ = boost::lexical_cast<float>(rhs);
				break;
			case 4: 
				value_ = boost::lexical_cast<double>(rhs);
				break;
			default: 
				value_ = rhs; 
				break;
			}
			return true;
		}
		/// Set from raw value returns false if held types don't match
		bool Set(const Variant& value)
		{
			switch (value_.which())
			{
			case 0:
				if (value.Which() == value_.which())
					return Set(value.GetBool());
				else
					return false;
			case 1:
				if (value.Which() == value_.which())
					return Set(value.GetInt());
				else
					return false;
			case 2:
				if (value.Which() == value_.which())
					return Set(value.GetUInt());
				else
					return false;
			case 3:
				if (value.Which() == value_.which())
					return Set(value.GetFloat());
				else
					return false;
			case 4:
				if (value.Which() == value_.which())
					return Set(value.GetDouble());
				else
					return false;
			default:
				if (value.Which() == value_.which())
					return Set(value.GetString());
				else
					return false;
			}
			return false;
		}

	private:
		/// The type of the variant
		std::string type_;
		/// the value of the variant
		VariantType value_;
	};

}