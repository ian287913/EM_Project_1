#include "CaCuMi.h"

const Matrix CaCuMi::Multiply(const Matrix & M1, const Matrix & M2)
{
	if (M1.Data[0].size() != M2.Data.size())
		throw std::exception("(Multiply) cannot match the size.");

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

	return tempMatrix;
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
	//	Zero
	if (row == 0 || col == 0)
		throw std::exception("(Determinant) 0-dim unacceptable");
	//	Vector-like
	if (row == 1 || col == 1)
		return 0.0;
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

const Matrix CaCuMi::Cofactors(const Matrix & M)
{
	int row = M.Data.size(), col = M.Data[0].size();
	//	Zero
	if (row < 2 || col <2)
		throw std::exception("(Cofactors) 0or1 dim unacceptable");

	Matrix tempMatrix = Matrix(M);

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			Matrix determinTemp = Matrix(M);
			//	cut	a row
			determinTemp.Data.erase(determinTemp.Data.begin() + c);
			//	cut	a column
			for (int cut = 0; cut < determinTemp.Data.size(); cut++)
				determinTemp.Data[cut].erase(determinTemp.Data[cut].begin() + r);
			//	do Determinant
			tempMatrix.Data[r][c] = Determinant(determinTemp);
			//	1 or -1
			if (((r + c) % 2) != 0)
				tempMatrix.Data[r][c] *= (-1.0);
		}
	}

	return tempMatrix;
}

const Matrix CaCuMi::Transpose(Matrix& input)
{
	if (input.Data.size() < 1)
		throw std::exception("matrix format error");
	Matrix output(input.Data[0].size(), input.Data.size());

	for (int i = 0; i < input.Data.size(); i++)
	{
		for (int j = 0; j < input.Data[i].size(); j++)
		{
			output.Data[j][i] = input.Data[i][j];
		}
	}
	return output;
}

void CaCuMi::ZeroCheck(const Matrix & M)
{
	if (M.Data.size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
	if (M.Data[0].size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
}
