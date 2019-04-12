#include"CaCuMw.h"

const Matrix CaCuMw::Add(Matrix& m1, Matrix& m2)
{
	Matrix output;
	if (m1.Data.size() != m2.Data.size())
		throw std::exception("Matrices dimensions not match!");
	for (int i = 0; i < m1.Data.size(); i++)
	{
		if(m1.Data[i].size() != m2.Data[i].size())
			throw std::exception("Matrices dimensions not match!");
		std::vector<double> temprow;
		for (int j = 0; j < m1.Data[i].size(); j++)
		{
			temprow.push_back(m1.Data[i][j] + m2.Data[i][j]);
		}
		output.Data.push_back(temprow);
	}
	return output;
}