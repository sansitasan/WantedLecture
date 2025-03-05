#include "DefaultMaterial.h"

namespace SanDX {
	DefaultMaterial::DefaultMaterial()
		: Material(TEXT("Default"))
	{
	}

	DefaultMaterial::~DefaultMaterial()
	{
	}

	void DefaultMaterial::Bind()
	{
		Material::Bind();
	}
}