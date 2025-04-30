#pragma once
#include "Material.h"
#include "Type.h"
#include <memory>
#include <unordered_map>

namespace SanDX {
	class NormalMappingMaterial : public Material {
	public:
		enum class ETextureBindType : uint32 {
			Diffuse = 0,
			NormalMap = 1
		};

	public:
		NormalMappingMaterial();

		virtual void Bind() override;

		void SetTexture(ETextureBindType bindType, const std::weak_ptr<class Texture>& newTexture);

	protected:
		std::unordered_map<ETextureBindType, std::weak_ptr<class Texture>> textures;
	};
}