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

//inl�� �ζ����� ����
//�����ϵ��� �ʴ� Ȯ���ڸ� �����̵� �������
//���ø��� ���� �� Ʋ���� �ڵ带 ������ �ʴ´�
#include "MaterialLoader.inl"