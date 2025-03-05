#include "MaterialLoader.h"

namespace SanDX {
	template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Material, T>::value>::type*>
	inline bool MaterialLoader::Load(std::weak_ptr<T>& outMaterial, Args... args) {
		auto name = typeid(T).name();
		auto find = materials.find(name);
		if (find != materials.end()) {
			//dynamic_cast가 아니라 static_pointer_cast를 쓸 수 있는 이유
			//T가 Material의 자식으로 강제하면 된다.
			//강제하지 않으면 컴파일 오류가 날 수 있다?
			//컴파일 돌리기 전에 문법상 오류와 컴파일 타임 오류의 차이인가
			outMaterial = std::static_pointer_cast<T>(find->second);
			return true;
		}

		std::shared_ptr<Material> newMaterial = std::make_shared<T>(args...);
		materials.insert(std::make_pair(name, newMaterial));
		outMaterial = std::static_pointer_cast<T>(newMaterial);
		return true;
	}
}