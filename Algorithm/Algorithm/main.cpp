#include "PCH.h"
#include <string>
#include "Solution/Sol1976.h"
#include <chrono>
#include <new>
#include <xmmintrin.h>

class Vector3 {
public:
	float x = .0f;
	float y = .0f;
	float z = .0f;

	inline Vector3()
		: x(0), y(0), z(0) {
	}

	inline Vector3(float value)
		: x(value), y(value), z(value) {
	}

	inline Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {
	}
};

class Matrix4x4 {
public:
	Matrix4x4() {
		memset(elements, 0, sizeof(float) * 16);
		m00 = m11 = m22 = m33 = 1.f;
	}

	~Matrix4x4() = default;

	friend Vector3 operator*(const Matrix4x4& matrix, const Vector3& vector)
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

	friend Vector3 operator*(const Vector3& vector, const Matrix4x4& matrix) {
		Vector3 result;
		result.x = matrix.m00 * vector.x + matrix.m01 * vector.y + matrix.m02 * vector.z;
		result.x = matrix.m10 * vector.x + matrix.m11 * vector.y + matrix.m12 * vector.z;
		result.x = matrix.m20 * vector.x + matrix.m21 * vector.y + matrix.m22 * vector.z;
		return result;
	}

private:
	union {
		__m128 simd128[4];
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

template<typename T>
class Base {
public:
	class Nested {
	public:
		Nested() = default;

		Nested(int x) {

		}
	};
};

template<typename T>
class Derived : public Base<T>::Nested {
public:
	Derived(int x)
		: Base<T>::Nested(x) {
		typename Base<T>::Nested temp;
	}
};

//class A {
//public:
//	A() { printf("A 생성자\n"); }
//	virtual ~A() { printf("A 소멸자\n"); }
//	int A_num = 0;
//};
//
//class B : virtual public A {
//public:
//	B() { printf("B 생성자\n"); }
//	virtual ~B() { printf("B 소멸자\n"); }
//private:
//	int B_num = 1;
//};
//
//class C : virtual public A {
//public:
//	C() { printf("C 생성자\n"); }
//	virtual ~C() { printf("C 소멸자\n"); }
//private:
//	int C_num = 2;
//};
//
//class D : public B, public C {
//public:
//	D() { printf("D 생성자\n"); }
//	virtual ~D() { printf("D 소멸자\n"); }
//private:
//	int D_num = 3;
//};

class CompanyA {
public:
	void SendCleartext(const string& msg) {}
	void sendEncrypted(const string& msg) {}
};

class CompanyB {
public:
	void SendCleartext(const string& msg) {}
	void sendEncrypted(const string& msg) {}
};

class CompanyZ {
public:
	void sendEncrypted(const string& msg) {}
};

class MsgInfo {
public:
	string msg;
};

template<typename Company>
class MsgSender {
public:
	void sendClear(const MsgInfo& info) {
		string msg;
		Company c;
		c.sendCleartext(msg);
	}

	void sendSecret(const MsgInfo& info) {}
};

template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) { sendClear(info); }
};

template<typename T>
class B {
public:
	class Xyz { /*...*/ };
	typedef int Pqr;
};
template<typename T>
class D : public B<T> {
public:
	using B<T>::Xyz;
	using B<T>::Pqr;

	void g()
	{
		Xyz x;
		Pqr y;
	}
};

class A1 {
public:
	A1(int x) : xx(x) { cout << "only A1" << '\n'; }

private:
	int xx;
};

class B1 {
public:
	B1(int x) : xx(x) {}

	operator A1() {

		cout << "A1 in B1" << '\n';
	}

private:
	int xx;
};

void g(int x) {

}

void g(A1 x) {

}

int main() {
	//Solution* s = new Sol1976();
	//
	//s->Answer();

	//B* d = new B();
	//delete d;

	//LoggingMsgSender<CompanyA> x;
	//MsgInfo s;
	//x.sendClearMsg(s);

	cin.get();
	//Matrix4x4 a;
	//Vector3 b;
	//
	//auto start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < 100000000; ++i) {
	//	a * b;
	//}
	//auto end = std::chrono::high_resolution_clock::now();
	//std::cout << "SIMD multiply: "
	//	<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
	//	<< " microseconds" << '\n';
	//
	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < 100000000; ++i) {
	//	b * a;
	//}
	//end = std::chrono::high_resolution_clock::now();
	//std::cout << "normal multiply: "
	//	<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
	//	<< " microseconds" << '\n';

	return 0;
}