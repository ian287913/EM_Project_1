#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<exception>
#include"Matrix.h"
#include"Vec.h"

static class CaCuMw
{
public:
	//加
	static const Matrix Add(const Matrix& m1, const Matrix& m2);
	//rank
	static const int Rank(const Matrix& input);

	//方便使用的乘法vector
	static const std::vector<double> scaleVector(const std::vector<double>, double);
	//方便使用的加法vector
	static const std::vector<double> addVector(const std::vector<double>, const std::vector<double>);
};