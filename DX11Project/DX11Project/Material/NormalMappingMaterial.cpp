#include "NormalMappingMaterial.h"
#include "Render/Texture.h"

namespace SanDX {
	NormalMappingMaterial::NormalMappingMaterial()
		: Material(TEXT("NormalMapping"))
	{

	}

	void NormalMappingMaterial::Bind()
	{
		Material::Bind();

		for (const auto& textureRef : textures) {
			std::shared_ptr<Texture> texture = textureRef.second.lock();
			if (!texture) continue;

			texture->Bind(static_cast<uint32>(textureRef.first));
		}
	}
	void NormalMappingMaterial::SetTexture(ETextureBindType bindType, const std::weak_ptr<Texture>& newTexture)
	{
		textures.insert(std::make_pair(bindType, newTexture));
	}
}