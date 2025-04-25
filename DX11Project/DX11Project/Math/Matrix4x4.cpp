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

	Matrix4x4::Matrix4x4(const Matrix4x4& other)
	{
		memcpy(elements, other.elements, sizeof(float) * 16);
	}

	void Matrix4x4::Translation(const Vector3& position, Matrix4x4& outValue)
	{
		Translation(position.x, position.y, position.z, outValue);
	}

	void Matrix4x4::Translation(float x, float y, float z, Matrix4x4& outValue)
	{
		memset(&outValue, 0, Matrix4x4::Stride());
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
		memset(&outValue, 0, sizeof(float) * 16);
		float cosAngle = std::cos(angle * degreeToRadian);
		float sinAngle = std::sin(angle * degreeToRadian);
		outValue.m00 = 1.f;
		outValue.m11 = cosAngle;	
		outValue.m12 = sinAngle;
		outValue.m21 = -sinAngle;	
		outValue.m22 = cosAngle;
		outValue.m33 = 1.f;

		//outValue.m00 = 1.f;		outValue.m01 = 0.f;			outValue.m02 = 0.f;			outValue.m03 = 0.f;
		//outValue.m10 = 0.f;		outValue.m11 = cosAngle;	outValue.m12 = sinAngle;	outValue.m13 = 0.f;
		//outValue.m20 = 0.f;		outValue.m21 = -sinAngle;	outValue.m22 = cosAngle;	outValue.m23 = 0.f;
		//outValue.m30 = 0.f;		outValue.m31 = 0.f;			outValue.m32 = 0.f;			outValue.m33 = 1.f;
	}

	void Matrix4x4::RotationY(float angle, Matrix4x4& outValue)
	{
		memset(&outValue, 0, sizeof(float) * 16);
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
		memset(&outValue, 0, sizeof(float) * 16);
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
		memset(&outValue, 0, sizeof(float) * 16);
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

	void Matrix4x4::Transpose()
	{
		std::swap(m01, m10);
		std::swap(m02, m20);
		std::swap(m03, m30);
		std::swap(m12, m21);
		std::swap(m13, m31);
		std::swap(m23, m32);
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
		memcpy(elements, other.elements, sizeof(float) * 16);
		return *this;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
	{
		Matrix4x4 m;
		m.m00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
		m.m01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
		m.m02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
		m.m03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;
		
		m.m10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
		m.m11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
		m.m12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
		m.m13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;
		
		m.m20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
		m.m21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
		m.m22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
		m.m23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;
		
		m.m30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
		m.m31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
		m.m32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
		m.m33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

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
		result.x = matrix.m00 * vector.x + matrix.m10 * vector.y + matrix.m20 * vector.z;
		result.x = matrix.m01 * vector.x + matrix.m11 * vector.y + matrix.m21 * vector.z;
		result.x = matrix.m02 * vector.x + matrix.m12 * vector.y + matrix.m22 * vector.z;
		return result;
	}
}