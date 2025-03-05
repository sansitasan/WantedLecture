#include "Matrix4x4.h"
#include <cmath>

#include "DirectXMath.h"

using namespace DirectX;

namespace SanDX {
	Matrix4x4 Matrix4x4::Identity = Matrix4x4();

	Matrix4x4::Matrix4x4()
	{
		memset(elements, 0, sizeof(float) * 16);
		m00 = m11 = m22 = m33 = 1.f;
	}

	Matrix4x4::Matrix4x4(const Vector3& position, const Vector3& rotation, const Vector3& scale)
	{
		simd512 = _mm512_setzero_ps();
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& other)
	{
		simd512 = other.simd512;
		//memcpy(elements, other.elements, sizeof(float) * 16);
	}

	void Matrix4x4::Translation(const Vector3& position, Matrix4x4& outValue)
	{
		Translation(position.x, position.y, position.z, outValue);
	}

	void Matrix4x4::Translation(float x, float y, float z, Matrix4x4& outValue)
	{
		outValue.simd512 = _mm512_setzero_ps();
		outValue.m00 = 1.f;
		outValue.m11 = 1.f;
		outValue.m22 = 1.f;
		outValue.m30 = x;
		outValue.m31 = y;
		outValue.m32 = z;
		outValue.m33 = 1.f;
		//outValue.m00 = 1.f;		outValue.m01 = 0.f;		outValue.m02 = 0.f;		outValue.m03 = 0.f;
		//outValue.m10 = 0.f;		outValue.m11 = 1.f;		outValue.m12 = 0.f;		outValue.m13 = 0.f;
		//outValue.m20 = 0.f;		outValue.m21 = 0.f;		outValue.m22 = 1.f;		outValue.m23 = 0.f;
		//outValue.m30 = x;			outValue.m31 = y;		outValue.m32 = z;		outValue.m33 = 1.f;
	}

	void Matrix4x4::Rotation(const Vector3& rotation, Matrix4x4& outValue)
	{
		return Rotation(rotation.x, rotation.y, rotation.z, outValue);
	}

	void Matrix4x4::Rotation(float x, float y, float z, Matrix4x4& outValue)
	{
		Matrix4x4 xm, ym, zm;
		RotationX(x, xm);
		RotationY(y, ym);
		RotationZ(z, zm);
		outValue = xm * ym * zm;
	}

	void Matrix4x4::RotationX(float angle, Matrix4x4& outValue)
	{
		//outValue.simd512 = _mm512_setzero_ps();
		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);

		outValue.m00 = 1.f;		outValue.m01 = 0.f;			outValue.m02 = 0.f;			outValue.m03 = 0.f;
		outValue.m10 = 0.f;		outValue.m11 = cosAngle;	outValue.m12 = sinAngle;	outValue.m13 = 0.f;
		outValue.m20 = 0.f;		outValue.m21 = -sinAngle;	outValue.m22 = cosAngle;	outValue.m23 = 0.f;
		outValue.m30 = 0.f;		outValue.m31 = 0.f;			outValue.m32 = 0.f;			outValue.m33 = 1.f;
	}

	void Matrix4x4::RotationY(float angle, Matrix4x4& outValue)
	{
		//outValue.simd512 = _mm512_setzero_ps();
		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);
		outValue.m00 = cosAngle;
		outValue.m02 = -sinAngle;
		outValue.m11 = 1.f;
		outValue.m20 = sinAngle;
		outValue.m22 = cosAngle;
		outValue.m33 = 1.f;

		//outValue.m00 = cosAngle;		outValue.m01 = 0.f;		outValue.m02 = -sinAngle;	outValue.m03 = 0.f;
		//outValue.m10 = 0.f;			outValue.m11 = 1.f;		outValue.m12 = 0.f;			outValue.m13 = 0.f;
		//outValue.m20 = sinAngle;		outValue.m21 = 0.f;		outValue.m22 = cosAngle;	outValue.m23 = 0.f;
		//outValue.m30 = 0.f;			outValue.m31 = 0.f;		outValue.m32 = 0.f;			outValue.m33 = 1.f;
	}

	void Matrix4x4::RotationZ(float angle, Matrix4x4& outValue)
	{
		//outValue.simd512 = _mm512_setzero_ps();
		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);

		outValue.m00 = cosAngle;	outValue.m01 = sinAngle;
		outValue.m10 = -sinAngle;	outValue.m11 = cosAngle;
		outValue.m22 = 1.f;
		outValue.m33 = 1.f;

		//outValue.m00 = cosAngle;		outValue.m01 = sinAngle;	outValue.m02 = 0.f;		outValue.m03 = 0.f;
		//outValue.m10 = -sinAngle;		outValue.m11 = cosAngle;	outValue.m12 = 0.f;		outValue.m13 = 0.f;
		//outValue.m20 = 0.f;			outValue.m21 = 0.f;			outValue.m22 = 1.f;		outValue.m23 = 0.f;
		//outValue.m30 = 0.f;			outValue.m31 = 0.f;			outValue.m32 = 0.f;		outValue.m33 = 1.f;
	}

	void Matrix4x4::Scale(const Vector3& scale, Matrix4x4& outValue)
	{
		Scale(scale.x, scale.y, scale.z, outValue);
	}

	void Matrix4x4::Scale(float x, float y, float z, Matrix4x4& outValue)
	{
		//outValue.simd512 = _mm512_setzero_ps();
		outValue.m00 = x;
		outValue.m11 = y;
		outValue.m22 = z;
		outValue.m33 = 1.f;

		//outValue.m00 = x;			outValue.m01 = 0.f;		outValue.m02 = 0.f;		outValue.m03 = 0.f;
		//outValue.m10 = 0.f;		outValue.m11 = y;		outValue.m12 = 0.f;		outValue.m13 = 0.f;
		//outValue.m20 = 0.f;		outValue.m21 = 0.f;		outValue.m22 = z;		outValue.m23 = 0.f;
		//outValue.m30 = 0.f;		outValue.m31 = 0.f;		outValue.m32 = 0.f;		outValue.m33 = 1.f;
	}

	void Matrix4x4::Scale(float scale, Matrix4x4& outValue)
	{
		Scale(scale, scale, scale, outValue);
	}

	void Matrix4x4::Transpose(const Matrix4x4& target, Matrix4x4& outValue)
	{
		outValue = target;
		std::swap(outValue.m01, outValue.m10);
		std::swap(outValue.m02, outValue.m20);
		std::swap(outValue.m03, outValue.m30);

		std::swap(outValue.m12, outValue.m21);
		std::swap(outValue.m13, outValue.m31);
		std::swap(outValue.m23, outValue.m32);
	}

	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
	{
		//memcpy(elements, other.elements, sizeof(float) * 16);
		simd512 = other.simd512;
		return *this;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
	{
		Matrix4x4 m;
		__m128 temp;
		for (__int8 i = 0; i < 4; ++i) {
			for (__int8 j = 0; j < 4; ++j) {
				temp = _mm_mul_ps(simd128[i], _mm_set_ps(other.elements[j], other.elements[j + 4], other.elements[j + 8], other.elements[j + 12]));
				m.elements[(i << 2) + j] = temp.m128_f32[0] + temp.m128_f32[1] + temp.m128_f32[2] + temp.m128_f32[3];
			}
		}

		return m;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector3 operator*(const Matrix4x4& matrix, const Vector3& vector)
	{
		return vector * matrix;
	}

	Vector3 operator*(const Vector3& vector, const Matrix4x4& matrix)
	{
		Vector3 result;
		__m128 temp = _mm_mul_ps(_mm_set_ps(matrix.m00, matrix.m10, matrix.m20, 0), _mm_set_ps(vector.x, vector.y, vector.z, 0));
		result.x = temp.m128_f32[1] + temp.m128_f32[2] + temp.m128_f32[3];
		temp = _mm_mul_ps(_mm_set_ps(matrix.m01, matrix.m11, matrix.m21, 0), _mm_set_ps(vector.x, vector.y, vector.z, 0));
		result.y = temp.m128_f32[1] + temp.m128_f32[2] + temp.m128_f32[3];
		temp = _mm_mul_ps(_mm_set_ps(matrix.m02, matrix.m12, matrix.m22, 0), _mm_set_ps(vector.x, vector.y, vector.z, 0));
		result.z = temp.m128_f32[1] + temp.m128_f32[2] + temp.m128_f32[3];
		return result;
	}
}