#pragma once

/// includes
#include <map>
#include <memory>
#include <string>
#include <vector>

/// library includes
#include "Model/Attributes.h"
#include "TemplateItem.h"

namespace TPGE 
{
	// forward declaration of classes
	class PassTemplate;

	class DataTemplate : public TemplateItem
	{
	public:
		DataTemplate();
		~DataTemplate();

		/// Add an attr
		void AddAttribute(unsigned index, std::string name, std::shared_ptr<Attribute> attr);
		/// Add an attr
		void AddAttribute(unsigned index, std::shared_ptr<Attribute> attr);
		/// Add an attr
		void AddAttribute(std::string name, std::shared_ptr<Attribute> attr);
		/// Add a pass template
		void AddPassTemplate(unsigned index, std::string name, std::shared_ptr<PassTemplate> pass);
		/// Add a pass template
		void AddPassTemplate(unsigned index, std::shared_ptr<PassTemplate> pass);
		/// Add a pass template
		void AddPassTemplate(std::string name, std::shared_ptr<PassTemplate> pass);

		/// Get an attribute
		std::shared_ptr<Attribute> GetAttribute(std::string name);
		/// Get an attribute
		std::shared_ptr<Attribute> GetAttribute(unsigned index);
		/// Get the dimension of the Template
		unsigned GetDimension() { return dimension_; };
		/// Get the number of passes
		unsigned GetNumAttributes() { return attributes_.Size(); }
		/// Get the number of passes
		unsigned GetNumPassTemplates() { return passes_.Size(); }
		/// Get a combo template
		std::shared_ptr<PassTemplate> GetPassTemplate(std::string name);
		/// access the map at index
		std::shared_ptr<PassTemplate> GetPassTemplate(unsigned index);

		/// Set the dimension of the Template
		void SetDimension(unsigned dimension) { dimension_ = dimension; }

	protected:
		/// the map of attributes
		AttributeMap attributes_;
		/// The dimenson of the array;
		unsigned dimension_;
		/// the map of child passes in the template
		IndexedMap<PassTemplate> passes_;

	private:

	};
}