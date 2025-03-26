#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace SanDX {
	struct MeshData;
	class ModelLoader {
	public:
		ModelLoader();
		~ModelLoader() = default;

		bool Load(const std::string& name, std::weak_ptr<MeshData>& outData);

		static ModelLoader& Get();

	private:
		static ModelLoader* instance;

		std::unordered_map <std::string, std::shared_ptr<MeshData>> meshes;
	};
}