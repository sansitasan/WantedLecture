#include "MaterialLoader.h"

namespace SanDX {
	template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Material, T>::value>::type*>
	inline bool MaterialLoader::Load(std::weak_ptr<T>& outMaterial, Args... args) {
		auto name = typeid(T).name();
		auto find = materials.find(name);
		if (find != materials.end()) {
			//dynamic_cast�� �ƴ϶� static_pointer_cast�� �� �� �ִ� ����
			//T�� Material�� �ڽ����� �����ϸ� �ȴ�.
			//�������� ������ ������ ������ �� �� �ִ�?
			//������ ������ ���� ������ ������ ������ Ÿ�� ������ �����ΰ�
			outMaterial = std::static_pointer_cast<T>(find->second);
			return true;
		}

		std::shared_ptr<Material> newMaterial = std::make_shared<T>(args...);
		materials.insert(std::make_pair(name, newMaterial));
		outMaterial = std::static_pointer_cast<T>(newMaterial);
		return true;
	}
}