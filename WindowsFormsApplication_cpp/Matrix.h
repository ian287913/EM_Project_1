#pragma once
#include<vector>
#include<string>

//定義向量資料結構
struct Matrix
{
public:
	Matrix();
	//	init the size of Rows and Columns
	Matrix(int row, int col);

	std::string Name = "";
	std::vector< std::vector<double>> Data;
};

inline Matrix::Matrix()
{

}

inline Matrix::Matrix(int row, int col)
{
	Data = std::vector< std::vector<double>>(row);
	for (int i = 0; i < row; i++)
		Data[i] = std::vector<double>(col);
}