#pragma once

/// includes
#include <string>

/// library includes
#include "Model/Attributes.h"
#include "TemplateItem.h"

namespace TPGE
{
	class TechniqueTemplate : public TemplateItem
	{
	public:
		TechniqueTemplate();
		~TechniqueTemplate();

		/// Add an attr
		void AddAttribute(std::string name, std::shared_ptr<Attribute> attr);
		/// Add value
		void AddValue(std::string variableName, std::string pathToAttribute);

		/// Get an attribute
		std::shared_ptr<Attribute> GetAttribute(std::string name);
		/// Get an attribute
		std::shared_ptr<Attribute> GetAttribute(unsigned index);
		/// Get the number of attributes
		unsigned GetNumAttributes() const { return attributes_.Size(); }
		/// Get the number of paths to attributes
		unsigned GetNumPaths() const { return valueMap_.Size(); }
		/// Get the path to a selected attribute
		std::shared_ptr<std::pair<std::string, std::string> > GetPathToAttribute(const std::string& name);
		/// Get the path to an indexed attribute
		std::shared_ptr<std::pair<std::string, std::string> > GetPathToAttribute(unsigned index);

	protected:

	private:
		/// the map of attributes
		AttributeMap attributes_;
		/// The map that maps values to variables (left/key:VariableName, right/value:path-to-attribute)
		IndexedMap<std::pair<std::string, std::string> > valueMap_;
	};
}