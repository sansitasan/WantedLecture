#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Type.h"

namespace SanDX {
	class Texture;
	class RenderTexture;

	class TextureLoader {
	public:
		TextureLoader();
		~TextureLoader() = default;

		void Load(const std::string& name, std::weak_ptr<Texture>& outTexture);
		void MakeRenderTexture(std::weak_ptr<RenderTexture>& outTexture, uint32 width = 0, uint32 height = 0);
		const std::vector<std::shared_ptr<RenderTexture>>& GetRenderTextures();

		static TextureLoader& Get();
	private:
		static TextureLoader* instance;
		std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<RenderTexture>> renderTextures;
	};
}