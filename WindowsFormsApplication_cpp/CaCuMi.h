#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<exception>
#include"Vec.h"
#include "Matrix.h"

static class CaCuMi
{
public:
	static const Matrix Multiply(const Matrix& M1	, const Matrix& M2);
	//	dont use dis
	static const Matrix Multiply(const Matrix& M	, const Vector& V);	
	static const Matrix Multiply(const Matrix& M	, const double& scale);
	//	��C��
	static const double Determinant(const Matrix& M);
	static const Matrix Cofactors(const Matrix& M);
	//trans
	static const Matrix Transpose(const Matrix& M);
	static const Matrix Adjoint(const Matrix& M);
	static const Matrix Inverse(const Matrix& M);

	//	�YR��C�j�p���s�h��ҥ~
	static void ZeroCheck(const Matrix& M);
};