#pragma once

/// includes
#include <memory>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"
#include "Util/IndexedMap.h"

namespace TPGE
{
	class Attributed : public TPGEObject
	{
	public:
		TPGE_OBJECT(Attributed, TPGEObject)

		Attributed(std::shared_ptr<TPGEContext> context);
		~Attributed();

		// Add a node
		void AddAttribute(unsigned index, std::string name, const Variant& attribute);
		/// Add a node
		void AddAttribute(unsigned index, const Variant& attribute);
		/// Add a node
		void AddAttribute(std::string name, const Variant& attribute);
		/// Remove a node
		bool RemoveAttribute(unsigned index);
		/// Remove a node
		bool RemoveAttribute(std::string name);
		/// Remove all nodes
		void ClearAttributes();

		/// Get the node at index
		std::shared_ptr<Variant> GetAttribute(unsigned index);
		/// Get the node by name
		std::shared_ptr<Variant> GetAttribute(std::string name);
		/// Get the indices
		unsigned GetIndex() const { return index_; }
		/// Get the designating name of the graph
		std::string& GetName() const { return const_cast<std::string&>(name_); }

		/// Set the index of this object
		void SetIndex(unsigned index) { index_ = index; }
		/// Set the designating name of this object
		void SetName(const std::string name) { name_ = name; }

	protected:
		/// the attributes held by the class
		IndexedVariantMap attributes_;
		/// The indices pointing to this object
		unsigned index_;
		/// The designating name of the object
		std::string name_;

	private:
	};
}
