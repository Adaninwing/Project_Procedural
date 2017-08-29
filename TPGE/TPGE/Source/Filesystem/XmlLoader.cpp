// library includes
#include "FileSystem.h"
#include "Model/Attributes.h"
#include "Model/Templates/AgentTemplate.h"
#include "Model/Templates/ComboTemplate.h"
#include "Model/Templates/DataTemplate.h"
#include "Model/Templates/GraphTemplate.h"
#include "Model/Templates/PassTemplate.h"
#include "Model/Templates/TechniqueTemplate.h"
#include "Model/Templates/Template.h"
#include <pugixml.hpp>

// header
#include "XmlLoader.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	XmlLoader::XmlLoader(std::shared_ptr<TPGEContext> context) :
		IFileLoader(context)
	{

	}

	XmlLoader::~XmlLoader()
	{

	}

	void XmlLoader::LoadCombo(std::shared_ptr<ComboTemplate> combo, std::map<std::string, std::shared_ptr<DataTemplate> >& dataToLoadRef, std::map<std::string, std::shared_ptr<GraphTemplate> >& graphToLoadRef)
	{
		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(combo->GetFile().c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();

			pugi::xml_node node = root.first_child();
			std::string name;
			std::string dataUses;
			std::string file;
			std::shared_ptr<DataTemplate> dataTemp;
			std::shared_ptr<GraphTemplate> graphTemp;

			while (node)
			{
				// Load what's possible
				name = node.attribute("name").value();
				file = node.attribute("file").value();

				std::string type = node.name();
				if (type == "data")
				{
					dataTemp = std::make_shared<DataTemplate>();
					dataTemp->SetTypeName(name);
					dataTemp->SetFile(GetRelativePath(combo->GetFile(), file));
					dataTemp->SetParent(combo);
					dataToLoadRef.insert(std::pair<std::string, std::shared_ptr<DataTemplate> >(name, dataTemp));
					combo->AddDataTemplate(name, dataTemp);
				}
				else if (type == "graph") 
				{
					dataUses = node.attribute("uses").value();

					graphTemp = std::make_shared<GraphTemplate>();
					graphTemp->SetTypeName(name);
					graphTemp->SetFile(GetRelativePath(combo->GetFile(), file));
					graphTemp->AddMutipleDataUses(dataUses);
					graphTemp->SetParent(combo);
					graphToLoadRef.insert(std::pair<std::string, std::shared_ptr<GraphTemplate> >(name, graphTemp));
					combo->SetGraph(graphTemp);
				}

				// get next
				node = node.next_sibling();
			}
		}
	}

	void XmlLoader::LoadData(std::shared_ptr<DataTemplate> data, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef)
	{
		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(data->GetFile().c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();
			data->SetDimension(root.attribute("dim").as_uint());

			pugi::xml_node node = root.first_child();
			std::string name;
			unsigned index;
			std::string file;

			while (node)
			{
				std::string type = node.name();
				if (type == "attribute")
				{
					// crete the attribute
					std::shared_ptr<Attribute> attrPtr = LoadAttribute(node);

					// add the attribute to the parent
					if(attrPtr->index_ != UINT_MAX)
						data->AddAttribute(attrPtr->index_, attrPtr->name_, attrPtr);
					else
						data->AddAttribute(attrPtr->name_, attrPtr);
				}
				else if (type == "pass")
				{
					// crete the attribute
					std::shared_ptr<PassTemplate> passPtr = std::make_shared<PassTemplate>();

					pugi::xml_attribute attr = node.attribute("name");
					if (attr)
					{
						name = attr.value();
						passPtr->SetTypeName(name);
					}
					attr = node.attribute("index");
					if (attr)
					{
						index = attr.as_uint();
						passPtr->SetIndex(index);
					}
					attr = node.attribute("file");
					passPtr->SetFile(GetRelativePath(data->GetFile(), attr.value()));
					passPtr->SetParent(data);
					data->AddPassTemplate(passPtr->GetIndex(), passPtr->GetTypeName(), passPtr);
					passesToLoadRef.insert(std::pair<std::string, std::shared_ptr<PassTemplate> >(passPtr->GetTypeName(), passPtr));
				}

				// get next
				node = node.next_sibling();
			}
		}
	}

	void XmlLoader::LoadGraph(std::shared_ptr<GraphTemplate> graph, std::map<std::string, std::shared_ptr<PassTemplate> >& passesToLoadRef)
	{
		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(graph->GetFile().c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();

			pugi::xml_node node = root.first_child();
			std::string name;
			unsigned index;
			std::string file;

			while (node)
			{
				std::string type = node.name();
				if (type == "node")
				{
					std::shared_ptr<GraphTemplateNode> tempateNode = std::make_shared<GraphTemplateNode>();
					pugi::xml_node attrNode = node.first_child();

					while (attrNode)
					{
						std::string type = attrNode.name();
						if (type == "attribute")
						{
							// crete the attribute
							std::shared_ptr<Attribute> attrPtr = LoadAttribute(attrNode);

							// add the attribute to the parent
							if (attrPtr->index_ != UINT_MAX)
								tempateNode->attributes_.Insert(attrPtr->index_, attrPtr->name_, attrPtr);
							else
								tempateNode->attributes_.Insert(attrPtr->name_, attrPtr);
						}

						// get next
						attrNode = attrNode.next_sibling();
					}

					graph->SetNodeTemplate(tempateNode);
				}
				else if (type == "edge")
				{
					std::shared_ptr<GraphTemplateEdge> tempateNode = std::make_shared<GraphTemplateEdge>();
					std::string directedType = node.attribute("type").value();
					tempateNode->type_ = GetEdgeType(directedType);

					pugi::xml_node attrNode = node.first_child();

					while (attrNode)
					{

						std::string type = attrNode.name();
						if (type == "attribute")
						{
							// crete the attribute
							std::shared_ptr<Attribute> attrPtr = LoadAttribute(attrNode);

							// add the attribute to the parent
							if (attrPtr->index_ != UINT_MAX)
								tempateNode->attributes_.Insert(attrPtr->index_, attrPtr->name_, attrPtr);
							else
								tempateNode->attributes_.Insert(attrPtr->name_, attrPtr);

						}

						// get next
						attrNode = attrNode.next_sibling();
					}

					graph->SetEdgeTemplate(tempateNode);
				}
				else if (type == "pass")
				{
					// crete the attribute
					std::shared_ptr<PassTemplate> passPtr = std::make_shared<PassTemplate>();

					pugi::xml_attribute attr = node.attribute("name");
					if (attr)
					{
						name = attr.value();
						passPtr->SetTypeName(name);
					}
					attr = node.attribute("index");
					if (attr)
					{
						index = attr.as_uint();
						passPtr->SetIndex(index);
					}
					attr = node.attribute("file");
					passPtr->SetFile(GetRelativePath(graph->GetFile(), attr.value()));
					passPtr->SetParent(graph);
					graph->AddPassTemplate(passPtr->GetIndex(), passPtr->GetTypeName(), passPtr);
					passesToLoadRef.insert(std::pair<std::string, std::shared_ptr<PassTemplate> >(passPtr->GetTypeName(), passPtr));
				}

				// get next
				node = node.next_sibling();
			}
		}
	}

	void XmlLoader::LoadPass(std::shared_ptr<PassTemplate> pass, std::map<std::string, std::shared_ptr<TechniqueTemplate> >& techniquesToLoadRef)
	{
		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(pass->GetFile().c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();
			pugi::xml_node node = root.first_child();
			std::string name;
			std::string file;
			std::string agentType;

			while (node)
			{
				std::shared_ptr<AgentTemplate> agentTemp = std::make_shared<AgentTemplate>();
				name = node.attribute("name").value();
				agentType = node.attribute("type").value();
				file = node.attribute("technique").value();

				pugi::xml_attribute attr = node.attribute("mask");
				if (attr)
				{
					std::string mask = attr.value();
					agentTemp->SetMask(mask);
				}
				agentTemp->SetTypeName(name);
				agentTemp->SetAgentType(GetAgentType(agentType));
				agentTemp->SetParent(pass);

				// parse attributes of agent
				pugi::xml_node attrNode = node.first_child();
				while (attrNode)
				{
					std::string type = attrNode.name();
					if (type == "attribute")
					{
						// crete the attribute
						std::shared_ptr<Attribute> attrPtr = LoadAttribute(attrNode);
						if (attrPtr->name_ == "Mask Value")
							agentTemp->SetMaskValue(attrPtr);
						else if (attrPtr->name_ == "Tokens")
							agentTemp->SetTokens(attrPtr);
					}
					attrNode = attrNode.next_sibling();
				}

				// ony load file if it doesn't exist already
				std::shared_ptr<TechniqueTemplate> techniqueTemp = std::make_shared<TechniqueTemplate>();
				techniqueTemp->SetTypeName(name + "." + file);
				techniqueTemp->SetFile(GetRelativePath(pass->GetFile(), file));
				techniqueTemp->SetParent(agentTemp);
					
				techniquesToLoadRef.insert(std::pair<std::string, std::shared_ptr<TechniqueTemplate> >(techniqueTemp->GetTypeName(), techniqueTemp));

				agentTemp->SetTechniqueTemplate(techniqueTemp);

				pass->AddAgentTemplate(name, agentTemp);

				// get next
				node = node.next_sibling();
			}
		}
	}

	void XmlLoader::LoadTechnique(std::shared_ptr<TechniqueTemplate> technique)
	{
		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(technique->GetFile().c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();
			pugi::xml_node node = root.first_child();

			while (node)
			{
				std::string type = node.name();
				if (type == "attribute")
				{
					// crete the attribute
					std::shared_ptr<Attribute> attrPtr = LoadAttribute(node);

					// add the attribute to the parent
					technique->AddAttribute(attrPtr->name_, attrPtr);
				}
				else if (type == "uses")
				{
					std::string varPath = node.attribute("name").value();
					std::string varName = node.attribute("as").value();

					technique->AddValue(varName, varPath);
				}

				// get next
				node = node.next_sibling();
			}
		}
	}

	std::shared_ptr<Template> XmlLoader::LoadTemplate(const std::string& path, std::map<std::string, std::shared_ptr<ComboTemplate> >& combosToLoadRef)
	{
		// create template
		std::shared_ptr<Template> temp = std::make_shared<Template>();
		temp->SetFile(path);

		// load document
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());

		if (result)
		{
			pugi::xml_node root = doc.root().first_child();

			pugi::xml_attribute attr = root.attribute("name");
			std::string name = attr.value();
			temp->SetTypeName(name);

			// initialize
			pugi::xml_node combo = root.child("combo");
			std::string comboName;
			std::string comboFile;
			std::shared_ptr<ComboTemplate> comboTemp;

			while (combo)
			{
				// Load what's possible
				comboName = combo.attribute("name").value();
				comboFile = combo.attribute("file").value();
				comboTemp = std::make_shared<ComboTemplate>();
				comboTemp->SetTypeName(comboName);
				comboTemp->SetFile(GetRelativePath(path, comboFile));
				comboTemp->SetParent(temp);
				combosToLoadRef.insert(std::pair<std::string, std::shared_ptr<ComboTemplate> >(comboName, comboTemp));
				temp->AddComboTemplate(comboName, comboTemp);

				// Load children
				RecursiveCreateComboTree(combo, comboTemp, combosToLoadRef);

				// get next combo
				combo = combo.next_sibling();
			}
		}
		else
		{
			return nullptr;
		}

		return temp;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	std::shared_ptr<Attribute> XmlLoader::LoadAttribute(pugi::xml_node node)
	{
		std::string name;
		unsigned index;
		std::string type;
		std::string value;

		// crete the attribute
		std::shared_ptr<Attribute> attrPtr = std::make_shared<Attribute>();

		pugi::xml_attribute attr = node.attribute("name");
		if (attr)
		{
			name = attr.value();
			attrPtr->name_ = name;
		}
		attr = node.attribute("index");
		if (attr)
		{
			index = attr.as_uint();
			attrPtr->index_ = index;
		}
		type = node.attribute("type").value();
		attrPtr->value_ = std::make_shared<Variant>(type);
		attr = node.attribute("value");
		if (attr)
		{
			value = attr.value();
			attrPtr->value_->Set(value);
		}

		// get the constrints
		pugi::xml_node constraint = node.first_child();
		while (constraint)
		{
			// crete the constrint
			std::shared_ptr<Constraint> constrPtr = std::make_shared<Constraint>();

			pugi::xml_attribute constraintAttr = constraint.attribute("name");
			constrPtr->name_ = constraintAttr.value();
			type = constraint.attribute("type").value();
			constrPtr->value_ = std::make_shared<Variant>(type);
			constraintAttr = constraint.attribute("value");
			constrPtr->value_->Set(std::string(constraintAttr.value()));

			attrPtr->constraints_.Insert(constrPtr->name_, constrPtr);

			// get next
			constraint = constraint.next_sibling();
		}

		return attrPtr;
	}

	void XmlLoader::RecursiveCreateComboTree(pugi::xml_node root, std::shared_ptr<ComboTemplate> attatchTo, std::map<std::string, std::shared_ptr<ComboTemplate> >& combosToLoadRef)
	{
		pugi::xml_node combo = root.child("combo");
		std::string comboName;
		std::string comboFile;
		std::shared_ptr<ComboTemplate> comboTemp;

		while (combo)
		{
			// Load what's possible
			comboName = combo.attribute("name").value();
			comboFile = combo.attribute("file").value();
			comboTemp = std::make_shared<ComboTemplate>();
			comboTemp->SetTypeName(comboName);
			comboTemp->SetFile(GetRelativePath(attatchTo->GetFile(), comboFile));
			comboTemp->SetParent(attatchTo);
			combosToLoadRef.insert(std::pair<std::string, std::shared_ptr<ComboTemplate> >(comboName, comboTemp));
			attatchTo->AddComboTemplate(comboName, comboTemp);

			// Load children
			RecursiveCreateComboTree(combo, comboTemp, combosToLoadRef);

			// get next combo
			combo = combo.next_sibling();
		}
	}

}