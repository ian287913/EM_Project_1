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
		throw new std::exception("(+) Wrong size");
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

const Vector CaCu::Sub(const Vector & v1, const Vector & v2)
{
	///	Caution!!	No exception handling	///

	Vector tempVector(v1);
	for (int i = 0; i < tempVector.Data.size(); i++)
	{
		tempVector.Data[i] -= v2.Data[i];
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
		throw new std::exception("(*) invalid scalar - size != 1");
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
	return Length(v);
}

const Vector CaCu::Normalize(const Vector & v)
{
	Vector tempVector(v);
	double length = Length(v);
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
		throw new std::exception("(Cross) only support 3d x 3d");

	tempVector.Data.push_back((v1.Data[1] * v2.Data[2]) - (v1.Data[2] * v2.Data[1]));	//	[0]
	tempVector.Data.push_back((v1.Data[2] * v2.Data[0]) - (v1.Data[0] * v2.Data[2]));	//	[1]
	tempVector.Data.push_back((v1.Data[0] * v2.Data[1]) - (v1.Data[1] * v2.Data[0]));	//	[2]

	return tempVector;
}

const double CaCu::Length(const Vector & v)
{
	double length = 0.0;
	for (int i = 0; i < v.Data.size(); i++)
		length += (v.Data[i] * v.Data[i]);
	return sqrt(length);
}

const double CaCu::Dot(const Vector & v1, const Vector & v2)
{
	if (v1.Data.size() == 0 || v2.Data.size() == 0)
		return 0.0;
	if (v1.Data.size() != v2.Data.size())
		throw new std::exception("(Dot) Different dimention");

	double sum = 0;
	for (int i = 0; i < v1.Data.size(); i++)
		sum += v1.Data[i] * v2.Data[i];
	return sum;
}

const double CaCu::Component(const Vector & v1, const Vector & v2)
{
	if (v1.Data.size() != v2.Data.size())
		throw new std::exception("(Component) Different dimention");

	double Component = Dot(v1, v2);

	if (Length(v2) == 0.0)
		return 0.0;
	//	else
	Component /= Length(v2);
	return Component;
}

const Vector CaCu::Projection(const Vector & v1, const Vector & v2)
{
	Vector tempVector = Vector();
	tempVector.Data.clear();
	if (v1.Data.size() == 0 || v2.Data.size() == 0)
		return tempVector;	//	Zero

	if(Length(v2) == 0)
		return tempVector;	//	zero

	return Scale(v2, (Dot(v1, v2) / Dot(v2, v2)));
}

const double CaCu::Triangle(const Vector & v1, const Vector & v2)
{
	if (v1.Data.size() == 0 || v2.Data.size() == 0)
		return 0.0;
	if (v1.Data.size() != v2.Data.size())
		throw new std::exception("(Triangle) Different dimention");


	
	return (Length(v2) * sin(Angle(v1, v2) * Length(v1) / 2.0));
}

const bool CaCu::IsParallel(const Vector & v1, const Vector & v2)
{
	if (v1.Data.size() == 0 || v2.Data.size() == 0)
		return true;
	if (v1.Data.size() != v2.Data.size())
		throw new std::exception("(IsParallel) Different dimention");

	Vector tempV1 = Normalize(v1), tempV2 = Normalize(v2);
	//	make it same way
	if (tempV1.Data[0] != tempV2.Data[0])
		tempV1 = Neg(tempV1);

	bool isPar = true;
	//	if any difference
	for (int i = 0; i < v1.Data.size(); i++)
	{
		//std::cout << tempV1.Data[i] - tempV2.Data[i]<< "\n";
		if (abs(tempV1.Data[i] - tempV2.Data[i]) > 0.000001)
			isPar = false;
	}
	//	else
	return isPar;
}

const bool CaCu::IsOrthogonal(const Vector & v1, const Vector & v2)
{
	return (Dot(v1, v2) == 0.0);
}

const double CaCu::Angle(const Vector & v1, const Vector & v2)
{
	double length1 = Length(v1), length2 = Length(v2);
	if (length1 == 0 || length2 == 0)
		throw new std::exception("(Angle) No zero vector allowed");

	return acos((Dot(v1, v2) / (length1*length2))) *180.0 / PI;
}

const std::vector<Vector> CaCu::Orthonormal(const std::vector<Vector>& vs, int size)
{
	std::vector<Vector> vecs = std::vector<Vector>(vs);

	for (int i = 0; i < size; i++)
	{
		for (int j = (i-1); j >= 0; j--)
		{
			vecs[i] = Sub(vecs[i], (Projection(vecs[i], vecs[j])));
		}
	}
	for (int i = 0; i < size; i++)
	{
		vecs[i] = Normalize(vecs[i]);
	}

	return vecs;
}
