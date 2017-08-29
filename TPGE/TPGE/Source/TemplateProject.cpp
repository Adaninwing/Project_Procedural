// System includes
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>

// incudes
#include <vector>

// ibrry includes
#include "Engine/TPGEContext.h"
#include "Filesystem/FileSystem.h"
#include "Generation/AttributeResolver.h"
#include "Generation/ModelGenerator.h"
#include "Model/Templates/Template.h"
#include "Model/Templates/TemplateFactory.h"
#include "Techniques/TechniqueInvoker.h"
#include "Util/Variant.h"

// header
#include "TemplateProject.h"

namespace TPGE
{

//===============================================================
// P U B L I C
//===============================================================
TemplateProject::TemplateProject() :
	projectDir_(GetCurrentDir()),
	projectState_(PS_IDLE)
{
	PreInitialization();
}

TemplateProject::TemplateProject(const std::string& projectDir) :
	projectDir_(projectDir),
	projectState_(PS_IDLE)
{
	PreInitialization();
}

TemplateProject::TemplateProject(const TemplateProject& toCopy) :
	projectDir_(toCopy.GetProjectDir()),
	projectState_(PS_IDLE)
{
	PreInitialization();
}

TemplateProject::~TemplateProject()
{

}

void TemplateProject::InitializeProject()
{
	context_->RegisterSubsystem(std::make_shared<AttributeResolver>(context_));
	context_->RegisterSubsystem(std::make_shared<ModelGenerator>(context_));
	context_->RegisterSubsystem(std::make_shared<TemplateFactory>(context_));
	context_->RegisterSubsystem(std::make_shared<TechniqueInvoker>(context_));
	context_->RegisterSubsystem(std::make_shared<FileSystem>(context_));
	projectState_ = PS_INITIALIZED;
}

void TemplateProject::LoadProject(const std::string& file)
{
	if (projectState_ == PS_INITIALIZED || PS_LOADED)
	{
		projectState_ = PS_LOADING;
		std::shared_ptr<TemplateFactory> factory = context_->GetSubsystem<TemplateFactory>();
		factory->SetProjectPath(projectDir_ + file);
		factory->Load();

		template_ = factory->GetLoadedTemplate();
		std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
		generator->SetTemplate(template_);
		projectState_ = PS_LOADED;
	}
}

std::string TemplateProject::GetCurrentDir()
{
	wchar_t path[MAX_PATH];
	path[0] = 0;
	GetCurrentDirectoryW(MAX_PATH, path);
	std::wstring ws(path);
	return std::string(ws.begin(), ws.end());
}

void TemplateProject::SetProjectDir(const std::string& projectDir)
{
	// does p actually exist?
	if (GetPathExists(projectDir))
	{
		projectDir_ = projectDir;
	}
	else
		projectDir_ = GetCurrentDir();
}

bool TemplateProject::GetPathExists(const std::string& path)
{
	// cross-platform way of checking for a path
	struct stat info;

	if (stat(path.c_str(), &info) != 0)
		return false;
	else if (info.st_mode & S_IFDIR)
		return true;
	else
		return false;
}

GeneratedGraph* TemplateProject::GetRootGraph()
{
	if (projectState_ == PS_LOADED)
	{
		if (rootGraph_)
			return rootGraph_.get();
		else
		{
			std::shared_ptr<ModelGenerator> generator = context_->GetSubsystem<ModelGenerator>();
			std::vector<unsigned> indices = { 0 };
			rootGraph_ = generator->GetGeneratedGraph(indices);
			return rootGraph_.get();
		}
	}
	else return nullptr;
}

//===============================================================
// P R O T E C T E D
//===============================================================

//===============================================================
// P R I V A T E
//===============================================================
void TemplateProject::PreInitialization()
{
	/// Register types
	VariantFactory::GetMap();

	/// create context
	context_ = std::make_shared<TPGEContext>();
}
}