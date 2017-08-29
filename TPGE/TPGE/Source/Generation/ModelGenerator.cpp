// includes
#include <climits>
#include <deque>

// header
#include "ModelGenerator.h"

// library includes
#include "Pass.h"
#include "AttributeResolver.h"
#include "Engine/TPGEContext.h"
#include "Filesystem/FileSystem.h"
#include "Filesystem/IDataLoader.h"
#include "Model/Generated/GeneratedData.h"
#include "Model/Generated/GeneratedGraph.h"
#include "Model/Templates/AgentTemplate.h"
#include "Model/Templates/ComboTemplate.h"
#include "Model/Templates/DataTemplate.h"
#include "Model/Templates/GraphTemplate.h"
#include "Model/Templates/PassTemplate.h"
#include "Model/Templates/TechniqueTemplate.h"
#include "Model/Templates/Template.h"
#include "Techniques/TechniqueInvoker.h"

namespace TPGE
{

	//===============================================================
	// P U B L I C
	//===============================================================
	ModelGenerator::ModelGenerator(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context)
	{

	}

	ModelGenerator::~ModelGenerator()
	{

	}

	void ModelGenerator::GenerateNodes(GeneratedGraph* graph)
	{
		if (!template_)
			return;

		std::deque<unsigned> temp = graph->GetPathUnsigned();
		std::vector<unsigned> indices;
		std::copy(temp.begin(), temp.end(), std::back_inserter(indices));
		std::shared_ptr<ComboTemplate> currentCombo = FindCombo(indices);

		if (currentCombo)
		{
			std::shared_ptr<GraphTemplate> graphTemplate = currentCombo->GetGraph();
			if (graphTemplate)
			{
				// genrate the nodes
				std::shared_ptr<PassTemplate> pass;
				for (unsigned i = 0; i < graphTemplate->GetNumPassTemplates(); i++)
				{
					pass = graphTemplate->GetPassTemplate(i);
					ExecutePass(graph, graphTemplate, pass);
				}
			}
		}
	}

	std::shared_ptr<GeneratedData> ModelGenerator::GetGeneratedData(const std::vector<unsigned>& indices, unsigned index)
	{
		if (!template_)
			return nullptr;

		std::shared_ptr<GeneratedData> genData = nullptr;
		std::shared_ptr<ComboTemplate> currentCombo = FindCombo(indices);

		// check if a combo was found
		if (currentCombo)
		{
			std::string dataUse = currentCombo->GetGraph()->GetDataUse(index);
			std::shared_ptr<DataTemplate> dataTemplate = currentCombo->GetDataTemplate(dataUse);
			if (dataTemplate)
			{
				genData = GenerateData(dataTemplate, index, dataUse);
			}
		}

		return genData;
	}
	
	std::shared_ptr<GeneratedData> ModelGenerator::GetGeneratedData(const std::vector<unsigned>& indices, std::string name)
	{
		if (!template_)
			return nullptr;

		std::shared_ptr<GeneratedData> genData = nullptr;
		std::shared_ptr<ComboTemplate> currentCombo = FindCombo(indices);

		// check if a combo was found
		if (currentCombo)
		{
			unsigned dataUse = currentCombo->GetGraph()->GetDataUse(name);
			if (dataUse != UINT_MAX)
			{
				std::shared_ptr<DataTemplate> dataTemplate = currentCombo->GetDataTemplate(name);
				if (dataTemplate)
				{
					genData = GenerateData(dataTemplate, dataUse, name);
				}
			}
		}

		return genData;
	}

	std::shared_ptr<GeneratedGraph> ModelGenerator::GetGeneratedGraph(const std::vector<unsigned>& indices)
	{
		if (!template_)
			return nullptr;

		std::shared_ptr<GeneratedGraph> genGraph = nullptr;
		std::shared_ptr<ComboTemplate> currentCombo = FindCombo(indices);
		
		// check if a combo was found
		if (currentCombo)
		{
			genGraph = GenerateGraph(currentCombo);
		}

		return genGraph;
	}

	std::shared_ptr<GeneratedGraph> ModelGenerator::GetGeneratedGraph(const std::vector<std::string>& names)
	{
		if (!template_)
			return nullptr;

		std::shared_ptr<GeneratedGraph> genGraph = nullptr;
		std::shared_ptr<ComboTemplate> currentCombo = FindCombo(names);

		// check if a combo was found
		if (currentCombo)
		{
			genGraph = GenerateGraph(currentCombo);
		}

		return genGraph;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	void ModelGenerator::ExecutePass(std::shared_ptr<GeneratedData> data, std::shared_ptr<PassTemplate> pass)
	{
		std::shared_ptr<Pass> passGenerated = std::make_shared<Pass>();
		passGenerated->name_ = pass->GetTypeName();
		InitializeAgents(passGenerated->agents_, data, pass);

		std::shared_ptr<TechniqueInvoker> invoker = context_->GetSubsystem<TechniqueInvoker>();
		invoker->ExecutePass(passGenerated);
	}

	void ModelGenerator::ExecutePass(GeneratedGraph* graph, std::shared_ptr<GraphTemplate> graphTemplate, std::shared_ptr<PassTemplate> pass)
	{
		std::shared_ptr<Pass> passGenerated = std::make_shared<Pass>();
		passGenerated->name_ = pass->GetTypeName();
		InitializeAgents(passGenerated->agents_, graph, graphTemplate, pass);

		std::shared_ptr<TechniqueInvoker> invoker = context_->GetSubsystem<TechniqueInvoker>();
		invoker->ExecutePass(passGenerated);
	}

	std::shared_ptr<ComboTemplate> ModelGenerator::FindCombo(const std::vector<unsigned>& indices)
	{
		std::shared_ptr<ComboTemplate> currentCombo = nullptr;
		for (size_t i = 0; i < indices.size(); i++)
		{
			if (i == 0)
			{
				// first check template combos
				currentCombo = template_->GetComboTemplateAt(indices[i]);
				if (!currentCombo)
				{
					currentCombo = nullptr;
					break;
				}
			}
			else
			{
				// get n'th combo of current combo
				currentCombo = currentCombo->GetComboTemplateAt(indices[i]);
			}
		}
		return currentCombo;
	}

	std::shared_ptr<ComboTemplate> ModelGenerator::FindCombo(const std::vector<std::string>& names)
	{
		std::shared_ptr<ComboTemplate> currentCombo = nullptr;
		for (size_t i = 0; i < names.size(); i++)
		{
			if (i == 0)
			{
				// first check template combos
				currentCombo = template_->GetComboTemplate(names[i]);
				if (!currentCombo)
				{
					currentCombo = nullptr;
					break;
				}
			}
			else
			{
				// get n'th combo of current combo
				currentCombo = currentCombo->GetComboTemplate(names[i]);
			}
		}
		return currentCombo;
	}

	std::shared_ptr<GeneratedData> ModelGenerator::GenerateData(std::shared_ptr<DataTemplate> data, unsigned index, std::string name)
	{
		std::shared_ptr<AttributeResolver> attrResolver = context_->GetSubsystem<AttributeResolver>();

		std::shared_ptr<GeneratedData> genData = std::make_shared<GeneratedData>(context_);
		genData->SetIndex(index);
		genData->SetName(name);

		// set dimensions
		std::shared_ptr<Attribute> att;
		std::shared_ptr<Variant> var;
		for (unsigned i = 0; i < data->GetDimension(); i++)
		{
			att = data->GetAttribute(i);
			var = attrResolver->GenerateAttribute(att);
			if(var && var->GetType() == "unsigned")
				genData->AddDimension(att->index_, att->name_, var->GetUInt());
		}

		// build data
		genData->Build();

		// set variables
		for (unsigned i = data->GetDimension(); i < data->GetNumAttributes(); i++)
		{
			att = data->GetAttribute(i);
			if (att)
			{
				std::shared_ptr<Constraint> constr;
				if (att->constraints_.Size())
					constr = att->constraints_.Get("File");
				if (constr)
				{
					std::string filePath = GetRelativePath(data->GetFile(), constr->value_->GetString());
					std::string ending = GetPathEnding(filePath);
					std::shared_ptr<IDataLoader> dataLoader = context_->GetSubsystem<FileSystem>()->GetDataLoader(ending);
					genData->AddContentVariable(att->name_, dataLoader->LoadData(filePath));
				}
				else
				{
					genData->AddContentVariable(att->name_, att->value_->GetType());
				}
			}
		}

		// genrate the data
		std::shared_ptr<PassTemplate> pass;
		for (unsigned i = 0; i < data->GetNumPassTemplates(); i++)
		{
			pass = data->GetPassTemplate(i);
			ExecutePass(genData, pass);
		}

		return genData;
	}

	std::shared_ptr<GeneratedGraph> ModelGenerator::GenerateGraph(std::shared_ptr<ComboTemplate> combo)
	{
		std::shared_ptr<GeneratedGraph> genGraph = std::make_shared<GeneratedGraph>(context_);
		genGraph->SetName(combo->GetTypeName());
		genGraph->SetIndex(combo->GetIndex());
		return genGraph;
	}

	void ModelGenerator::InitializeAgents(std::vector<std::shared_ptr<Agent> >& agents, GeneratedGraph* graph, std::shared_ptr<GraphTemplate> graphTemplate, std::shared_ptr<PassTemplate> pass)
	{
		std::shared_ptr<AttributeResolver> attrResolver = context_->GetSubsystem<AttributeResolver>();

		// variable declarations
		std::shared_ptr<AgentTemplate> agentTemplate;
		std::shared_ptr<TechniqueTemplate> techniqueTemplate;
		std::shared_ptr<Variant> constant;
		std::shared_ptr<Attribute> constantAttr;
		std::vector<std::string> dataPaths = graphTemplate->GetDataUses();
		std::string nodePath = "node/";
		std::string edgePath = "edge/";

		for (unsigned i = 0; i < pass->GetNumAgents(); i++)
		{
			agentTemplate = pass->GetAgentTemplate(i);
			techniqueTemplate = agentTemplate->GetTechniqeTemplate();

			// only parse agent types that are graph
			if (agentTemplate->GetAgentType() != AgentType::GRAPH) continue;

			agents.push_back(std::make_shared<Agent>(context_));
			agents.back()->SetAgentType(agentTemplate->GetAgentType());
			agents.back()->SetName(agentTemplate->GetTypeName());
			agents.back()->SetNodes(graph->GetNodes());
			agents.back()->SetEdgeType(graphTemplate->GetEdgeTemplate()->type_);

			// parse token values
			if (agentTemplate->GetTokens())
				agents.back()->SetTokens(attrResolver->GenerateAttribute(agentTemplate->GetMaskValue())->GetUInt());

			// parse technique constants
			for (unsigned i = 0; i < techniqueTemplate->GetNumAttributes(); i++)
			{
				constantAttr = techniqueTemplate->GetAttribute(i);
				constant = attrResolver->GenerateAttribute(constantAttr);
				agents.back()->AddTechniqueConstant(constantAttr->index_, constantAttr->name_, constant);
			}

			// parse used vars
			for (unsigned var = 0; var < techniqueTemplate->GetNumPaths(); var++)
			{
				std::shared_ptr<std::pair<std::string, std::string> > pathToValuePair = techniqueTemplate->GetPathToAttribute(var);
				std::string path = pathToValuePair->second;
				std::string name = pathToValuePair->first;
				if (path.find(nodePath) != std::string::npos)
				{
					std::shared_ptr<Variant> variable;
					std::shared_ptr<Attribute> att = graphTemplate->GetNodeTemplate()->attributes_[GetVariableNameFromPath(path, nodePath)];
					if (att)
					{
						variable = std::make_shared<Variant>(att->value_->GetType());
						agents.back()->AddNodeVariable(name, variable);
					}
				}
				else if (path.find(edgePath) != std::string::npos)
				{
					std::shared_ptr<Variant> variable;
					std::shared_ptr<Attribute> att = graphTemplate->GetEdgeTemplate()->attributes_[GetVariableNameFromPath(path, edgePath)];
					if (att)
					{
						variable = std::make_shared<Variant>(att->value_->GetType());
						agents.back()->AddEdgeVariable(name, variable);
					}
				}
				for (unsigned i = 0; i < dataPaths.size(); i++)
				{
					if (path.find(dataPaths[i] + "/") != std::string::npos)
					{
						std::shared_ptr<NArray<Variant> > variable;
						std::shared_ptr<GeneratedData> data = graph->GetData(dataPaths[i]);
						if (!data) continue;
						variable = data->GetContent(GetVariableNameFromPath(path, dataPaths[i] + "/"));
						if (variable)
							agents.back()->AddDataVariable(name, variable);
					}
				}
			}
		}
	}

	void ModelGenerator::InitializeAgents(std::vector<std::shared_ptr<Agent> >& agents, std::shared_ptr<GeneratedData> data, std::shared_ptr<PassTemplate> pass)
	{
		std::shared_ptr<AttributeResolver> attrResolver = context_->GetSubsystem<AttributeResolver>();

		// variable declarations
		std::shared_ptr<AgentTemplate> agentTemplate;
		std::shared_ptr<TechniqueTemplate> techniqueTemplate;
		std::shared_ptr<Variant> constant;
		std::shared_ptr<Attribute> constantAttr;
		std::shared_ptr<NArray<Variant> > mask;
		std::shared_ptr<NArray<Variant> > variable;
		std::string dataPath = "data/";

		for (unsigned i = 0; i < pass->GetNumAgents(); i++)
		{
			agentTemplate = pass->GetAgentTemplate(i);
			techniqueTemplate = agentTemplate->GetTechniqeTemplate();
			agents.push_back(std::make_shared<Agent>(context_));
			agents.back()->SetAgentType(agentTemplate->GetAgentType());
			agents.back()->SetName(agentTemplate->GetTypeName());

			// parse token values
			if (agentTemplate->GetTokens())
				agents.back()->SetTokens(attrResolver->GenerateAttribute(agentTemplate->GetMaskValue())->GetUInt());
			
			// parse technique constants
			for (unsigned i = 0; i < techniqueTemplate->GetNumAttributes(); i++)
			{
				constantAttr = techniqueTemplate->GetAttribute(i);
				constant = attrResolver->GenerateAttribute(constantAttr);
				agents.back()->AddTechniqueConstant(constantAttr->index_, constantAttr->name_, constant);
			}

			// parse masked values
			if (agentTemplate->GetAgentType() == AgentType::MASKED)
			{
				std::string maskString = agentTemplate->GetMask();
				mask = data->GetContent(GetVariableNameFromPath(maskString, dataPath));
				if (mask)
					agents.back()->SetMask(mask);
				if (agentTemplate->GetMaskValue())
					agents.back()->SetMaskValue(attrResolver->GenerateAttribute(agentTemplate->GetMaskValue()));
			}

			// parse used vars
			for (unsigned var = 0; var < techniqueTemplate->GetNumPaths(); var++)
			{
				std::shared_ptr<std::pair<std::string, std::string> > pathToValuePair = techniqueTemplate->GetPathToAttribute(var);
				std::string path = pathToValuePair->second;
				std::string name = pathToValuePair->first;
				variable = data->GetContent(GetVariableNameFromPath(path, dataPath));
				if (variable)
					agents.back()->AddDataVariable(name, variable);
			}
		}
	}

	std::string ModelGenerator::GetVariableNameFromPath(const std::string& path, const std::string& prefix)
	{
		std::string variable = path;
		size_t indexFound = path.find(path);
		if (indexFound != std::string::npos)
		{
			variable = variable.erase(indexFound, prefix.length());
		}
		return variable;
	}
}