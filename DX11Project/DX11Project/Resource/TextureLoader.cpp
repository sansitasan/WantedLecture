#include "TextureLoader.h"
#include "Render/Texture.h"
#include "Render/RenderTexture.h"

namespace SanDX {
	TextureLoader* TextureLoader::instance = nullptr;

	TextureLoader::TextureLoader()
	{
		if (instance != nullptr) return;
		instance = this;
	}

	void TextureLoader::Load(const std::string& name, std::weak_ptr<Texture>& outTexture)
	{
		auto find = textures.find(name);
		if (find != textures.end()) {
			outTexture = find->second;
			return;
		}

		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(name);
		textures.insert(std::make_pair(name, newTexture));
		outTexture = newTexture;
	}

	void TextureLoader::MakeRenderTexture(std::weak_ptr<RenderTexture>& outTexture, uint32 width, uint32 height)
	{
		std::shared_ptr<RenderTexture> newTexture = std::make_shared<RenderTexture>(width, height);
		renderTextures.emplace_back(newTexture);
		outTexture = newTexture;
	}

	const std::vector<std::shared_ptr<RenderTexture>>& TextureLoader::GetRenderTextures()
	{
		return renderTextures;
	}

	TextureLoader& TextureLoader::Get()
	{
		return *instance;
	}
}