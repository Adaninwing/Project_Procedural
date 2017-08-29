#pragma once

/// includes
#include <memory>
#include <string>
#include <vector>

/// library includes
#include "Engine/TPGEObject.h"

namespace TPGE
{
	/// forward declaration
	class Agent;
	class ComboTemplate;
	class DataTemplate;
	class GeneratedData;
	class GeneratedGraph;
	class GraphTemplate;
	class PassTemplate;
	class Template;

	class ModelGenerator : public TPGEObject
	{
	public:
		TPGE_OBJECT(ModelGenerator, TPGEObject)

		ModelGenerator(std::shared_ptr<TPGEContext> context);
		~ModelGenerator();

		/// Generate the nodes of a graph
		void GenerateNodes(GeneratedGraph* graph);

		/// Get the generated Data at indeces indicating a path though the tree
		std::shared_ptr<GeneratedData> GetGeneratedData(const std::vector<unsigned>& indices, unsigned index);
		/// Get the generated Data at indices indicating a path though the tree
		std::shared_ptr<GeneratedData> GetGeneratedData(const std::vector<unsigned>& indices, std::string name);
		/// Get a generated Graph at indeces indicating a path though the tree
		std::shared_ptr<GeneratedGraph> GetGeneratedGraph(const std::vector<unsigned>& indices);
		/// Get a generated Graph at names indicating a path though the tree
		std::shared_ptr<GeneratedGraph> GetGeneratedGraph(const std::vector<std::string>& names);
		/// Get the template
		std::shared_ptr<Template> GetTemplate() { return template_; }

		/// Set the template
		void SetTemplate(std::shared_ptr<Template> temp) { template_ = temp; }

	protected:

	private:
		/// execute a pass on generated data
		void ExecutePass(std::shared_ptr<GeneratedData> data, std::shared_ptr<PassTemplate> pass);
		/// execute a pass on generated data
		void ExecutePass(GeneratedGraph* graph, std::shared_ptr<GraphTemplate> graphTemplate, std::shared_ptr<PassTemplate> pass);
		/// traverse Graph to find combo template
		std::shared_ptr<ComboTemplate> FindCombo(const std::vector<unsigned>& indices);
		/// traverse Graph to find combo template
		std::shared_ptr<ComboTemplate> FindCombo(const std::vector<std::string>& names);
		/// generate data from a combo and return it
		std::shared_ptr<GeneratedData> GenerateData(std::shared_ptr<DataTemplate> data, unsigned index, std::string name);
		/// generate a graph from a combo and return it
		std::shared_ptr<GeneratedGraph> GenerateGraph(std::shared_ptr<ComboTemplate> combo);
		/// Initialize agents
		void InitializeAgents(std::vector<std::shared_ptr<Agent> >& agents, GeneratedGraph* graph, std::shared_ptr<GraphTemplate> graphTemplate, std::shared_ptr<PassTemplate> pass);
		/// Initialize agents
		void InitializeAgents(std::vector<std::shared_ptr<Agent> >& agents, std::shared_ptr<GeneratedData> data, std::shared_ptr<PassTemplate> pass);

		/// sanitize a path and extract the variable name, returns empty if not found
		std::string GetVariableNameFromPath(const std::string& path, const std::string& prefix);

		// the Template for generation
		std::shared_ptr<Template> template_;
	};
}
