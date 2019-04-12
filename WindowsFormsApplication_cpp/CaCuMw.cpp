#include"CaCuMw.h"

const Matrix CaCuMw::Add(const Matrix& m1, const Matrix& m2)
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
const int CaCuMw::Rank(const Matrix& input)
{
	if (input.Data.size() < 1)
		throw std::exception("matrix format error");
	if (input.Data[0].size() != input.Data.size())
		throw std::exception("matrix is not match format");
	
	Matrix temp = input;

	// 預設rank 等於 column 的個數.
	int rank = temp.Data[0].size();
	for (int row = 0; row < rank; row++)
	{
		if (temp.Data[row][row] != 0)
		{
			// 試圖將其他 rows 的同個 column 位置變成 0(相減)
			for (int r = 0; r < temp.Data.size(); r++)
			{
				if (r != row)
				{
					double scale = temp.Data[r][row] / temp.Data[row][row] * -1;
					std::vector<double> tempv = scaleVector(temp.Data[row], scale);
					temp.Data[r] = addVector(temp.Data[r], tempv);
					temp.Data[r][row] = 0;
				}
			}
		}
		else
		{
			// 找到底下能夠替代該 row 的 其他 row
			bool hasNZ = false;
			for (int r = row + 1; r < rank; r++)
				if (temp.Data[r][row] != 0)
				{
					// 有找到: 直接換
					hasNZ = true;
					std::vector<double>tempv = temp.Data[r];
					temp.Data[r] = temp.Data[row];
					temp.Data[row] = tempv;
				}
			if (!hasNZ)
			{
				// 沒找到: rank扣掉1
				rank -= 1;
				// 與最後交換
				for (int r = 0; r < rank; r++)
				{
					double tempd = temp.Data[r][rank];
					temp.Data[r][rank] = temp.Data[r][row];
					temp.Data[r][row] = tempd;
				}
			}
			row--;
		}
	}

	return rank;
}

const std::vector<double> CaCuMw::scaleVector(const std::vector<double> input, double scale)
{
	std::vector<double> output = input;
	for (int i = 0; i < output.size(); i++)
	{
		if(output[i] != 0)
			output[i] *= scale;
	}
	return output;
}
const std::vector<double> CaCuMw::addVector(const std::vector<double> v1, const std::vector<double> v2)
{
	if (v1.size() != v2.size())
		throw std::exception("vector add error");
	std::vector<double> output = v1;
	for (int i = 0; i < output.size(); i++)
		if (output[i] != 0 || v2[i] != 0)
			output[i] += v2[i];
	return output;
}