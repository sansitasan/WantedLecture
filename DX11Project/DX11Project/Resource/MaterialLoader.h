#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>

namespace SanDX {
	class Material;
	class MaterialLoader {
	public:
		MaterialLoader();
		~MaterialLoader() = default;
		template<typename T, typename std::enable_if<std::is_base_of<Material, T>::value>::type* = nullptr>
		bool Load(std::weak_ptr<T>& outMaterial);

		static MaterialLoader& Get();

	private:
		static MaterialLoader* instance;
		std::unordered_map<std::string, std::shared_ptr<Material>> materials;
	};
}

//inl은 인라인의 약자
//컴파일되지 않는 확장자면 무엇이든 상관없다
//템플릿은 문법 상 틀리면 코드를 만들지 않는다
#include "MaterialLoader.inl"