#pragma once


/// includes
#include <map>
#include <memory>
#include <string>

namespace TPGE
{

	class TemplateItem
	{
	public:

		TemplateItem();
		~TemplateItem();

		/// Get the type name of this template
		std::string& GetFile() const { return const_cast<std::string&>(file_); }
		/// Get the index of this template
		unsigned GetIndex() const { return index_; }
		/// Get the parent template
		std::shared_ptr<TemplateItem> GetParent() { return parent_; }
		/// Get the type name of this template
		std::string& GetTypeName() const { return const_cast<std::string&>(typeName_); }

		/// Set the type name of this template
		void SetFile(const std::string& file) { file_ = file; }
		/// Set the index of this template
		void SetIndex(unsigned index) { index_ = index; }
		/// Set the parent template
		void SetParent(std::shared_ptr<TemplateItem> parent) { parent_ = parent; }
		/// Set the type name of this template
		void SetTypeName(const std::string& name) { typeName_ = name; }

	protected:
		/// The file-Name
		std::string file_;
		/// The index of this item
		unsigned index_;
		/// The parent template
		std::shared_ptr<TemplateItem> parent_;
		/// the designating name of the template
		std::string typeName_;

	private:

	};
}
