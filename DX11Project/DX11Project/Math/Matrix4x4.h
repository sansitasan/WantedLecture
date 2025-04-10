#pragma once

#include "../Type.h"
#include "Vector3.h"

namespace SanDX {
	class Matrix4x4 {
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& other);
		~Matrix4x4() = default;

		static uint32 Stride() noexcept { return sizeof(Matrix4x4); }

		//Translate(T)
		static Matrix4x4 Translation(const Vector3& position);
		static void Translation(const Vector3& position, Matrix4x4& outValue);
		static void Translation(float x, float y, float z, Matrix4x4& outValue);

		//Rotate(R)
		static Matrix4x4 Rotation(const Vector3& rotation);
		static void Rotation(const Vector3& rotation, Matrix4x4& outValue);
		static void Rotation(float x, float y, float z, Matrix4x4& outValue);
		static void RotationX(float angle, Matrix4x4& outValue);
		static void RotationY(float angle, Matrix4x4& outValue);
		static void RotationZ(float angle, Matrix4x4& outValue);

		//Scale(S)
		static Matrix4x4 Scale(const Vector3& scale);
		static void Scale(const Vector3& scale, Matrix4x4& outValue);
		static void Scale(float x, float y, float z, Matrix4x4& outValue);
		static void Scale(float scale, Matrix4x4& outValue);

		void Transpose();

		static Matrix4x4 Transpose(const Matrix4x4& target);
		static void Transpose(const Matrix4x4& target, Matrix4x4& outValue);

		static Matrix4x4 Perspective(
			float fieldOfView,
			float width,
			float height,
			float nearDistance,
			float farDistance
		);

		Matrix4x4& operator=(const Matrix4x4& other);
		Matrix4x4 operator*(const Matrix4x4& other);
		Matrix4x4& operator*=(const Matrix4x4& other);

		friend Vector3 operator*(const Matrix4x4& matrix, const Vector3& vector);
		friend Vector3 operator*(const Vector3& vector, const Matrix4x4& matrix);

		//각 <> 호 변환
		//constexpr을 붙이면 헤더에 해도 가능
		//계산된 결과만 저장해둠
		//계산 결과는 vs가 해주는 것
		static Matrix4x4 Identity;
		static constexpr float degreeToRadian = 3.14159274f / 180.0f;
		static constexpr float radianToDegree = 180.f / 3.14159274f;

	private:
		union {
			//이름이 없어 바로 접근할 수 있다.
			//이렇게 나누는 이유는 그냥 시각적인 이유
			struct {
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			//2차원 배열을 선언해도 내부적으로 선형으로 들고있게 된다.
			float elements[4 * 4];
		};
	};
}