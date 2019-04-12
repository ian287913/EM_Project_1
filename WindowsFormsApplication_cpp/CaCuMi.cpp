#include "CaCuMi.h"

const Matrix CaCuMi::Multiply(const Matrix & M1, const Matrix & M2)
{
	if (M1.Data[0].size() != M2.Data.size())
	{
		throw std::exception("(Multiply) cannot match the size.");
	}
	
	int row = M1.Data.size(), col = M2.Data[0].size();
	int depth = M2.Data.size();
	Matrix tempMatrix = Matrix(row, col);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			tempMatrix.Data[r][c] = 0.0;
			for (int d = 0; d < depth; d++)
			{
				tempMatrix.Data[r][c] += M1.Data[r][d] * M2.Data[d][c];
			}
		}
	}

	return Matrix();
}

const Matrix CaCuMi::Multiply(const Matrix & M, const Vector & V)
{
	throw std::exception("(Multiply_Vector) ½Ð¥Î Nx1 ¯x°}");
	return Matrix();
}

const Matrix CaCuMi::Multiply(const Matrix & M, const double & scale)
{
	Matrix tempMatrix = Matrix(M);
	int row = M.Data.size(), col = M.Data[0].size();

	for (int r = 0; r < row; r++)
		for (int c = 0; c < col; c++)
			tempMatrix.Data[r][c] *= scale;

	return Matrix();
}

const double CaCuMi::Determinant(const Matrix & M)
{
	int row = M.Data.size(), col = M.Data[0].size();
	double value = 0.0;
	double add = 1.0;
	double sub = -1.0;

	for (int r = 0; r < row; r++)
	{
		add = 1.0;
		sub = -1.0;
		for (int c = 0; c < col; c++)
		{
			add *= M.Data[(r + c) % row][c];
			sub *= M.Data[(r - c) % row][c];
		}
		value += (add + sub);
	}


	return value;
}

///...
const Matrix CaCuMi::Cofactors(const Matrix & M)
{
	Matrix tempMatrix = Matrix(M);
	int row = M.Data.size(), col = M.Data[0].size();

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			///...
			///
		}
	}

	return Matrix();
}

void CaCuMi::ZeroCheck(const Matrix & M)
{
	if (M.Data.size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
	if (M.Data[0].size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
}
