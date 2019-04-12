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
	//�[
	static const Matrix Add(const Matrix& m1, const Matrix& m2);
	//rank
	static const int Rank(const Matrix& input);

	//��K�ϥΪ����kvector
	static const std::vector<double> scaleVector(const std::vector<double>, double);
	//��K�ϥΪ��[�kvector
	static const std::vector<double> addVector(const std::vector<double>, const std::vector<double>);
};