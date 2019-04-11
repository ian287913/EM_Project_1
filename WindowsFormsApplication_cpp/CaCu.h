#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<exception>
#include"Vec.h"

#define PI 3.14159265

static class CaCu
{
public:
	///const Vector operator =(const Vector &v2);
	static const Vector Add(const Vector &v1, const Vector &v2);
	static const Vector Neg(const Vector &v);
	static const Vector Scale(const Vector &v, const double &scale);	//	scale
	static const Vector Scale(const Vector &v1, const Vector &v2);		//	scale by 1 element Vector
	static const double Norm(const Vector &v);
	static const Vector Normalize(const Vector &v);
	static const Vector Cross(const Vector &v1, const Vector &v2);	//	Only support R3 x R3
	static const double Length(const Vector &v);
	static const double Dot(const Vector &v1, const Vector &v2);
	static const double Component(const Vector &v1, const Vector &v2);	//	v1 on v2
	static const Vector Projection(const Vector &v1, const Vector &v2);	//	v1 on v2
	static const double Triangle(const Vector &v1, const Vector &v2);
	static const bool IsParallel(const Vector &v1, const Vector &v2);
	static const bool IsOrthogonal(const Vector &v1, const Vector &v2);
	static const double Angle(const Vector &v1, const Vector &v2);
};

//	Exception
class myException: public std::exception
{
public:
	myException(std::string content) : Content(content) {}
	std::string Content;
};