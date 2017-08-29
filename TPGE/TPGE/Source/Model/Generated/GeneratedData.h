#pragma once
/// includes
#include <memory>
#include <string>

/// library includes
#include "Engine/TPGEObject.h"
#include "Util/NArray.h"
#include "Util/IndexedMap.h"

namespace TPGE
{
	class GeneratedData : public TPGEObject
	{
	public:
		TPGE_OBJECT(GeneratedData, TPGEObject)

		GeneratedData(std::shared_ptr<TPGEContext> context);
		~GeneratedData();

		/// can only be called after building
		void AddContentVariable(unsigned index, std::string name, std::string value);
		/// can only be called after building
		void AddContentVariable(unsigned index, std::string value);
		/// can only be called after building
		void AddContentVariable(std::string name, std::string value);
		/// can only be called after building
		void AddContentVariable(unsigned index, std::string name, std::shared_ptr<NArray<Variant>> content);
		/// can only be called after building
		void AddContentVariable(unsigned index, std::shared_ptr<NArray<Variant>> content);
		/// can only be called after building
		void AddContentVariable(std::string name, std::shared_ptr<NArray<Variant>> content);
		/// can only be called before building
		void AddDimension(unsigned index, std::string name, size_t value);
		/// can only be called before building
		void AddDimension(unsigned index, size_t value);
		/// can only be called before building
		void AddDimension(std::string name, size_t value);
		/// initialize
		void Build();

		/// Get a content array
		std::shared_ptr<NArray<Variant> > GetContent(unsigned index);
		/// Get a content array
		std::shared_ptr<NArray<Variant> > GetContent(std::string name);
		/// Get a dimension
		size_t GetDim(unsigned index) { return *dims_[index].get(); }
		/// Get a dimension
		size_t GetDim(std::string name) { return *dims_[name].get(); }
		/// Get the indices
		unsigned GetIndex() const { return index_; }
		/// Get the designating name of the graph
		std::string& GetName() const { return const_cast<std::string&>(name_); }

		/// Set a dimension
		void SetDim(unsigned index, size_t value);
		/// Set a dimension
		void SetDim(std::string name, size_t value);
		/// Set the index
		void SetIndex(unsigned index) { index_ = index; }
		/// Set the designating name of the graph
		void SetName(const std::string name) { name_ = name; }

	private:
		/// a flag for initialization
		bool built_;
		/// The attributes
		IndexedMap<NArray<Variant> > content_;
		/// The dimensions of the data
		IndexedMap<size_t> dims_;
		/// The indices pointing to this graph
		unsigned index_;
		/// The designating name of the graph
		std::string name_;
	};
}