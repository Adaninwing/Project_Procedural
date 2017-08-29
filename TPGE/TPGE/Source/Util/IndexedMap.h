#pragma once

/// includes
#include <climits>
#include <iostream>
#include <map>
#include <memory>
#include <string>

/// library includes
#include "Variant.h"

namespace TPGE
{
	/// forward declarations
	template<typename A, typename B> bool ComparePointerContents(const std::shared_ptr<A>& lhs, const std::shared_ptr<B>& rhs);
	template<typename A, typename B> bool ComparePointerContents(const A& lhs, const std::shared_ptr<B>& rhs);
	template<typename A, typename B> bool ComparePointerContents(const std::shared_ptr<A>& lhs, const B& rhs);

	/// Helper struct for the key
	struct KeyType
	{
		KeyType() : id_(UINT_MAX), key_("") {}
		KeyType(unsigned id) : id_(id), key_("") {}
		KeyType(std::string key) : id_(UINT_MAX), key_(key) {}
		KeyType(unsigned id, std::string key) : id_(id), key_(key) {}

		bool operator==(const KeyType& other) const 
		{
			return other.id_ == id_ && other.key_ == key_;
		}
		bool operator!=(const KeyType& other) const
		{
			return !(*this == other);
		}
		bool operator==(const unsigned& other) const
		{
			return other == id_;
		}
		bool operator!=(const unsigned& other) const
		{
			return !(*this == other);
		}
		bool operator==(const std::string& other) const
		{
			return other == key_;
		}
		bool operator!=(const std::string& other) const
		{
			return !(*this == other);
		}
		bool operator<(const KeyType& rhs) const {
			return id_ < rhs.id_ ? true
				: rhs.id_ < id_ ? false 
				: key_.compare(rhs.key_) < 0;
		}

		unsigned id_;
		std::string key_;
	};

	/// the map type
	template<typename T> class IndexedMap
	{
	public:
		typedef typename std::map<KeyType, std::shared_ptr<T> >::iterator Iterator;
		typedef typename std::map<KeyType, std::shared_ptr<T> >::const_iterator ConstIterator;

		IndexedMap() : map_() {}
		~IndexedMap() {}

		std::shared_ptr<T> operator[] (int index) {	return At(index); }
		std::shared_ptr<T> operator[] (std::string key)	{ return Get(key); }

		/// Get the value stored by index
		std::shared_ptr<T> At(int index)
		{ 
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				if (std::get<0>(*it) == index)
					return std::get<1>(*it);
			}
			return nullptr;
		}
		/// The begin iterator
		ConstIterator Begin() const { return map_.begin(); }
		/// The begin iterator
		Iterator Begin() { return map_.begin(); }
		/// clear the map
		void Clear()
		{
			map_.clear();
		}
		/// check if the element is allready stored in the structure
		bool Contains(const T& value)
		{
			std::shared_ptr<T> val;
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				val = std::get<1>(*it);
				if (ComparePointerContents(val, value))
					return true
			}
			return false;
		}
		/// get the number of elements in the maps
		bool Empty() { return map_.empty(); }
		/// The end iterator
		ConstIterator End() const { return map_.end(); }
		/// The end iterator
		Iterator Emd() { return map_.end(); }
		/// erase a value from the map by value; returns true on success
		bool Erase(const T& value)
		{
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				if (ComparePointerContents(std::get<1>(*it), value))
				{
					map_.erase(it);
					return true;
				}
			}
			return false;
		}
		/// erase a value from the map by key; returns true on success
		bool Erase(const std::string& key)
		{
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				if (std::get<0>(*it) == key)
				{
					map_.erase(it);
					return true;
				}
			}
			return false;
		}
		/// erase a value from the map by index; returns true on success
		bool Erase(int index)
		{
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				if (std::get<0>(*it) == index)
				{
					map_.erase(it);
					return true;
				}
			}
			return false;
		}
		/// Get the value stored by string key
		std::shared_ptr<T> Get(const std::string& key)
		{
			ConstIterator it;
			for (it = map_.begin(); it != map_.end(); it++)
			{
				if (std::get<0>(*it) == key)
					return std::get<1>(*it);
			}
			return nullptr;
		}
		/// Get the value stored by int key
		std::shared_ptr<T> Get(int index) { return At(index); }
		/// insert an element into the map
		void Insert(int index, const T& value)
		{
			if(!At(index))
				map_[KeyType(index)] = std::make_shared<T>(value);
		}
		/// insert an element into the map
		void Insert(int index, std::shared_ptr<T> value)
		{
			if (!At(index))
				map_[KeyType(index)] = value;
		}
		/// insert an element into the map
		void Insert(const std::string& key, const T& value)
		{
			if (!Get(key))
				map_[KeyType(key)] = std::make_shared<T>(value);
		}
		/// insert an element into the map
		void Insert(const std::string& key, std::shared_ptr<T> value)
		{
			if (!Get(key))
				map_[KeyType(key)] = value;
		}

		/// insert an element into the map
		void Insert(int index, const std::string& key, const T& value)
		{
			KeyType kType = KeyType(index, key);
			map_.insert(std::make_pair(kType, std::make_shared<T>(value)));
		}
		/// insert an element into the map
		void Insert(int index, const std::string& key, std::shared_ptr<T> value)
		{
			KeyType kType = KeyType(index, key);
			map_.insert(std::make_pair(kType, value));
		}
		/// get the number of elements in the maps
		size_t Size() const
		{
			return map_.size();
		}

	private:
		/// The internal map of values
		std::map<KeyType, std::shared_ptr<T>> map_;

	};

	/// Typedefs
	typedef IndexedMap<Variant> IndexedVariantMap;

	/// Helper to compatre the contents of two std::shared_ptr instances instead of the pointers
	template<typename A, typename B> 
	bool ComparePointerContents(const std::shared_ptr<A>& lhs, const std::shared_ptr<B>& rhs)
	{
		if ((*lhs.get()) == (*rhs.get()))
			return true;
		else
			return false;
	}

	template<typename A, typename B> 
	bool ComparePointerContents(const A& lhs, const std::shared_ptr<B>& rhs)
	{
		if (lhs == (*rhs.get()))
			return true;
		else
			return false;
	}

	template<typename A, typename B> 
	bool ComparePointerContents(const std::shared_ptr<A>& lhs, const B& rhs)
	{
		if ((*lhs.get()) == rhs)
			return true;
		else
			return false;
	}

}