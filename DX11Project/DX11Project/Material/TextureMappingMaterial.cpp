#include "TextureMappingMaterial.h"
#include "Render/Texture.h"
#include "Resource/TextureLoader.h"

namespace SanDX {
	TextureMappingMaterial::TextureMappingMaterial()
		:Material(L"TextureMapping")
	{

	}

	TextureMappingMaterial::TextureMappingMaterial(
		const std::string& textureName,
		const std::wstring& name)
		: Material(name)
	{

		TextureLoader::Get().Load(textureName, texture);
	}

	void TextureMappingMaterial::Bind()
	{
		Material::Bind();

		if (texture.lock()) {
			texture.lock()->Bind();
		}
	}

	void TextureMappingMaterial::SetTexture(const std::weak_ptr<class Texture>& newTexture)
	{
		texture = newTexture;
	}
}