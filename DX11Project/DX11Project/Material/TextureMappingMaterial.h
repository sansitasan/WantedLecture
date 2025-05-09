#pragma once
#include "Material.h"
#include <memory>

namespace SanDX {
	class TextureMappingMaterial : public Material {
	public:
		TextureMappingMaterial();
		TextureMappingMaterial(
			const std::string& textureName,
			const std::wstring& name = L"TextureMapping");

		virtual void Bind() override;

	protected:
		//std::unique_ptr<class Texture> texture;
		std::weak_ptr<class Texture> texture;
	};
}