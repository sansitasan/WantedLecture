#include "TextureMappingMaterial.h"
#include "Render/Texture.h"

namespace SanDX {
	TextureMappingMaterial::TextureMappingMaterial()
		:Material(L"Default")
	{

	}

	TextureMappingMaterial::TextureMappingMaterial(
		const std::string& textureName,
		const std::wstring& name)
		: Material(name)
	{
		texture = std::make_unique<Texture>(textureName);
	}

	void TextureMappingMaterial::Bind()
	{
		Material::Bind();

		if (texture) {
			texture->Bind();
		}
	}
}