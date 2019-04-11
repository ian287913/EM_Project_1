#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<exception>
#include"Vec.h"

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
};

//	Exception
class myException: public std::exception
{
public:
	myException(std::string content) : Content(content) {}
	std::string Content;
};