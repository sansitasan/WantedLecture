#include "MaterialLoader.h"
#include "Material/Material.h"

namespace SanDX {
	MaterialLoader* MaterialLoader::instance = nullptr;

	MaterialLoader::MaterialLoader()
	{
		if (instance != nullptr) return;
		instance = this;
	}

	MaterialLoader& MaterialLoader::Get()
	{
		return *instance;
	}
}