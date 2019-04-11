#include "CaCu.h"

const Vector CaCu::Add(const Vector & v1, const Vector & v2)
{
	if (v1.Data.size() == 0)
	{
		return v2;
	}
	else if (v2.Data.size() == 0)
	{
		return v1;
	}
	else if (v2.Data.size() != v1.Data.size())
	{
		throw myException("(+) Wrong size");
	}
	else
	{
		Vector tempVector(v1);
		for (int i = 0; i < tempVector.Data.size(); i++)
		{
			tempVector.Data[i] += v2.Data[i];
		}
		return tempVector;
	}
}

const Vector CaCu::Neg(const Vector & v)
{
	Vector tempVector(v);
	for (int i = 0; i < tempVector.Data.size(); i++)
	{
		tempVector.Data[i] = -(tempVector.Data[i]);
	}
	return tempVector;
}

const Vector CaCu::Scale(const Vector & v, const double & scale)
{
	Vector tempVector(v);
	for (int i = 0; i < tempVector.Data.size(); i++)
	{
		tempVector.Data[i] *= scale;
	}
	return tempVector;
}

const Vector CaCu::Scale(const Vector & v1, const Vector & v2)
{
	if (v2.Data.size() != 1)
	{
		throw new myException("(*) invalid scalar - size != 1");
	}
	Vector tempVector(v1);
	for (int i = 0; i < tempVector.Data.size(); i++)
	{
		tempVector.Data[i] *= v2.Data[0];
	}
	return tempVector;
}

const double CaCu::Norm(const Vector & v)
{
	if (v.Data.size() == 0)
		return 0.0;

	double sum = 0;
	for (int i = 0; i < v.Data.size(); i++)
	{
		sum += pow(abs(v.Data[i]), v.Data.size());
	}
	return pow(sum, (1.0 / v.Data.size()));
}

const Vector CaCu::Normalize(const Vector & v)
{
	Vector tempVector(v);

	double length = 0.0;
	for (int i = 0; i < tempVector.Data.size(); i++)
	{
		length += (tempVector.Data[i] * tempVector.Data[i]);
	}
	if (length == 0.0)
	{
		///	Turn to ZERO vector?	Exception?
	}
	else
	{
		for (int i = 0; i < tempVector.Data.size(); i++)
			tempVector.Data[i] /= length;
	}

	return tempVector;
}

const Vector CaCu::Cross(const Vector & v1, const Vector & v2)
{
	Vector tempVector = Vector();
	tempVector.Data.clear();	//	(Zero vector

	if (v1.Data.size() == 0 || v2.Data.size() == 0)
		return tempVector;	///	Is this right?
	if (v1.Data.size() != 3 || v2.Data.size() != 3)
		throw new myException("(Cross) only support 3d x 3d");

	tempVector.Data.push_back((v1.Data[1] * v2.Data[2]) - (v1.Data[2] * v2.Data[1]));	//	[0]
	tempVector.Data.push_back((v1.Data[2] * v2.Data[0]) - (v1.Data[0] * v2.Data[2]));	//	[1]
	tempVector.Data.push_back((v1.Data[0] * v2.Data[1]) - (v1.Data[1] * v2.Data[0]));	//	[2]

	return tempVector;
}
