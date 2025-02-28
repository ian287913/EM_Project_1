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

	return tempMatrix;
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

	double value = 1.0;

	Matrix temp = M;
	std::vector<double> tempVector;

	//變成上三角
	for (int R = 0; R < row; R++)
	{
		//	0
		if (temp.Data[R][R] == 0)
		{
			for (int r = R + 1; r < row; r++) 
			{
				if (temp.Data[r][R] != 0.0) 
				{
					value *= (-1.0);
					//	Switch
					tempVector = temp.Data[r];
					temp.Data[r] = temp.Data[R];
					temp.Data[R] = tempVector;

					break;
				}
			}
		}


		if (temp.Data[R][R] == 0.0)
			return 0.0;
		// 消去
		for (int r = R + 1; r < row; r++) {
			double scale = -temp.Data[r][R] / temp.Data[R][R];
			for (int c = R; c < row; c++)
			{
				temp.Data[r][c] += temp.Data[R][c] * scale;
			}
		}
		value *= temp.Data[R][R];
	}

	return value;
}

const double CaCuMi::Determinant(double **M, int size)
{
	double value = 1.0;

	double **temp = new double*[size];
	for (int r = 0; r < size; r++)
	{
		temp[r] = new double[size];
		for (int c = 0; c < size; c++)
			temp[r][c] = M[r][c];
	}

	//變成上三角
	for (int R = 0; R < size; R++)
	{
		//	0
		if (temp[R][R] == 0.0)
		{
			for (int r = R + 1; r < size; r++)
			{
				if (temp[r][R] != 0.0)
				{
					value *= (-1.0);
					//	Switch
					double *tempVector = new double[size];
					int i;
					for(i = 0; i < size; i++)
						tempVector[i] = temp[r][i];
					for (i = 0; i < size; i++)
						temp[r][i] = temp[R][i];
					for (i = 0; i < size; i++)
						temp[r][i] = temp[R][i];
					for (i = 0; i < size; i++)
						temp[R][i] = tempVector[i];
					delete[] tempVector;
					break;
				}
			}
		}

		if (temp[R][R] == 0.0)
		{
			value = 0.0;
			break;
		}
		// 消去
		for (int r = R + 1; r < size; r++) {
			double scale = -temp[r][R] / temp[R][R];
			for (int c = R; c < size; c++)
			{
				temp[r][c] += temp[R][c] * scale;
			}
		}
		value *= temp[R][R];
	}

	for (int d = 0; d < size; d++)
		delete[] temp[d];
	delete[] temp;
	return value;
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
		if (M[row][0] == 0)
			continue;

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
		
	}
	return value;
}

const Matrix CaCuMi::Cofactors(const Matrix & M)
{
	int row = M.Data.size(), col = M.Data[0].size();
	//	Zero
	if (row < 2 || col < 2 || col != row)
		throw std::exception("(Cofactors) dim unacceptable");

	Matrix tempMatrix = Matrix(M);
	//	
	double **temp = new double*[row-1];
	for (int r = 0; r < row-1; r++)
		temp[r] = new double[row-1];

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			for (int cutR = 0; cutR < row-1; cutR++)
			{
				for (int cutC = 0; cutC < col-1; cutC++)
				{
					if (cutR == r)
					{

					}
					if (cutC == c)
					{

					}
					temp[cutR][cutC] = M.Data[(cutR >= r ? (cutR + 1) : cutR)][(cutC >= c ? (cutC + 1) : cutC)];
				}
			}


			////Matrix determinTemp = Matrix(M);
			//////	cut	a row
			////determinTemp.Data.erase(determinTemp.Data.begin() + c);
			//////	cut	a column
			////for (int cut = 0; cut < determinTemp.Data.size(); cut++)
			////	determinTemp.Data[cut].erase(determinTemp.Data[cut].begin() + r);
			//////	do Determinant
			////tempMatrix.Data[r][c] = Determinant(determinTemp);
			tempMatrix.Data[r][c] = Determinant(temp,row-1);
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
	double asdf = (1.0 / Determinant(M));
	return Multiply(Adjoint(M), (1.0 / Determinant(M)));
}

void CaCuMi::ZeroCheck(const Matrix & M)
{
	if (M.Data.size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
	if (M.Data[0].size() <= 0)
		throw std::exception("(ZeroCheck) Zero dimention detected!");
}
