#include "PreCompiledHeader.h"
#include "Matrix2x2.h"

const Matrix2x2 Matrix2x2::Rad30 = Matrix2x2(std::cos(PI / 6), -std::sin(PI / 6), std::sin(PI / 6), std::cos(PI / 6));
const Matrix2x2 Matrix2x2::Rad45 = Matrix2x2(std::cos(PI / 4), -std::sin(PI / 4), std::sin(PI / 4), std::cos(PI / 4));
const Matrix2x2 Matrix2x2::Rad60 = Matrix2x2(std::cos(PI / 3), -std::sin(PI / 3), std::sin(PI / 3), std::cos(PI / 3));
const Matrix2x2 Matrix2x2::Rad90 = Matrix2x2(std::cos(PI / 2), -std::sin(PI / 2), std::sin(PI / 2), std::cos(PI / 2));
const Matrix2x2 Matrix2x2::Rad180 = Matrix2x2(std::cos(PI), -std::sin(PI), std::sin(PI), std::cos(PI));