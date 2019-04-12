#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<exception>
#include"Vec.h"
#include "Matrix.h"

static class CaCuMi
{
	static const Matrix Multiply(const Matrix& M1	, const Matrix& M2);
	//	dont use dis
	static const Matrix Multiply(const Matrix& M	, const Vector& V);	
	static const Matrix Multiply(const Matrix& M	, const double& scale);



	//	�YR��C�j�p���s�h��ҥ~
	static void ZeroCheck(const Matrix& M);
};