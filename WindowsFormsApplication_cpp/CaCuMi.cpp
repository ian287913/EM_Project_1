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
	throw std::exception("(Multiply_Vector) 請用 Nx1 矩陣");
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
	//	Zero
	if (M.Data.size() == 0)
		throw std::exception("(Determinant) 0-dim unacceptable");

	int row = M.Data.size(), col = M.Data[0].size();
	//	Non-square
	if (row != col)
		throw std::exception("(Determinant) Non-Square unacceptable");
	//	1x1
	if (row == 1)
		return M.Data[0][0];
	//	2x2
	if (row == 1)
		return (M.Data[0][0]* M.Data[1][1] - M.Data[1][0]* M.Data[0][1]);

	//	Matrix with double**
	double **doubleM = new double*[row];
	for (int r = 0; r < row; r++)
	{
		doubleM[r] = new double[row];
		for (int c = 0; c < row; c++)
		{
			doubleM[r][c] = M.Data[r][c];
		}
	}

	//double value = 0.0;

	//std::cout << "\n";
	//for (int r = 0; r < row; r++)
	//{
	//	Matrix tempMatrix = Matrix(M);
	//	//	cut	a column
	//	for (int cut = 0; cut < row; cut++)
	//		tempMatrix.Data[cut].erase(tempMatrix.Data[cut].begin());
	//	//	cut a row
	//	tempMatrix.Data.erase(tempMatrix.Data.begin() + r);
	//	//	value of each
	//	value += Laplace(tempMatrix) * ((r%2 == 0)?(M.Data[r][0]):(-(M.Data[r][0])));
	//}

	return Laplace(doubleM, row);
}

const double CaCuMi::Laplace(double **M, const int& size)
{
	if (size == 3)
	{
		//	三階
		return (
			M[0][0] * M[1][1] * M[2][2] +
			M[0][1] * M[1][2] * M[2][0] +
			M[0][2] * M[1][0] * M[2][1] -
			M[0][2] * M[1][1] * M[2][0] -
			M[0][0] * M[1][2] * M[2][1] -
			M[0][1] * M[1][0] * M[2][2]
			);
	}

	//std::cout << size << "\n";

	double value = 0.0;
	double **subM = new double*[size - 1];

	int c, r, row;
	//	init subM
	for (int c = 0; c < size - 1; c++)
	{
		subM[c] = new double[size - 1];
	}

	for (row = 0; row < size; row++)
	{
		for (r = 0; r < (size - 1); r++)
		{
			if (r < row)
			{
				for (c = 0; c < (size - 1); c++)
				{
					subM[r][c] = M[r][c+1];
				}
			}
			else
			{
				for (c = 0; c < (size - 1); c++)
				{
					subM[r][c] = M[r+1][c+1];
				}
			}
		}
		value += Laplace(subM, (size - 1)) * ((row % 2 == 0) ? (M[row][0]) : (-(M[row][0])));


		////	cut	a column
		//for (int cut = 0; cut < tempMatrix.Data.size(); cut++)
		//	tempMatrix.Data[cut].erase(tempMatrix.Data[cut].begin());
		////	value of each
		//if ((M.Data[r][0]) == 0.0)
		//	continue;
		//value += Laplace(tempMatrix) * ((r % 2 == 0) ? (M.Data[r][0]) : (-(M.Data[r][0])));
	}
	return value;
}
//
/////
//int determinantsol(int a, int** Matrix)
//{
//	int ** Matrixitem = new int*[a - 1];
//	int sum = 0, i = 0, p = 0, q = 0;
//	if (a == 1) 
//	{
//		sum = Matrix[0][0];
//	}
//	else 
//	{
//		for (i = 0; i < a - 1; i++) 
//		{
//			Matrixitem[i] = new int[a - 1];
//		}
//		for (i = 0; i < a; i++) 
//		{
//			for (p = 0; p < a - 1; p++)
//			{
//				for (q = 0; q < a - 1; q++) 
//				{
//					if (q < i) Matrixitem[p][q] = Matrix[p + 1][q];
//					if (q >= i) Matrixitem[p][q] = Matrix[p + 1][q + 1];
//				}
//			}
//			sum = sum + (pow((double)-1, i % 2) * Matrix[0][i] * determinantsol(a - 1, Matrixitem));//1和-1
//		}
//	}
//	return sum;
//}
const Matrix CaCuMi::Cofactors(const Matrix & M)
{
	int row = M.Data.size(), col = M.Data[0].size();
	//	Zero
	if (row < 2 || col < 2)
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

const Matrix CaCuMi::Transpose(const Matrix& input)
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

const Matrix CaCuMi::Adjoint(const Matrix & M)
{
	return Transpose(Cofactors(M));
}

const Matrix CaCuMi::Inverse(const Matrix & M)
{
	return Multiply(Adjoint(M), (1.0 / Determinant(M)));
}

void CaCuMi::ZeroCheck(const Matrix & M)
{
	if (M.Data.size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
	if (M.Data[0].size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
}
