#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Processor.h"

//定義控管資料class
class DataManager
{
private:
	std::vector<Matrix> Matrices;
	//儲存向量資料
	std::vector<Vector> Vectors;
	//紀錄向量ID，用於控管
	int  VectorVariableIndex;
	//紀錄檔案路徑名稱
	std::string FileName;
public:
	DataManager();
	//讀取向量資料
	bool LoadVectorData(bool isVec);
	//取得向量資料
	std::vector<Vector> GetVectors();
	//取得矩陣資料
	std::vector<Matrix> GetMatrices();
	//設置檔案路徑名稱
	void SetFileName(std::string fileName);
};
