#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
}

bool DataManager::LoadVectorData(bool isVec)
{
	std::fstream fin;
	//開啟檔案，傳入open函數的參數有兩個，欲開起的檔案名稱，開啟檔案的模式參數(這邊std::ios::in為讀取(輸入)狀態)
	fin.open(FileName, std::ios::in);
	//讀取失敗回傳false
	if (!fin)
	{
		return false;
	}
	else
	{
		if (isVec)
		{
			Vectors.clear();
			VectorVariableIndex = 0;
			//標記當前讀取向量ID
			int currentLoadVectorID = 0;
			//定義向量資料暫存變數
			std::vector<double> tempVectorData;
			//定義讀取檔案字串暫存變數
			std::string tempSring;
			//從檔案讀取字串，解析掉向量總數
			fin >> tempSring;
			
			int tempdim;
			//執行讀檔迴圈，並在讀到檔案結尾時結束
			while (!fin.eof())
			{
				//從檔案讀取字串
				fin >> tempSring;
				//解析到向量標記"V"
				if (tempSring == "V")
				{
					if (currentLoadVectorID != 0)
					{
						//定義暫存向量資料結構
						Vector tempVector;
						//存入向量資料
						tempVector.Data = tempVectorData;
						//定義向量變數名稱，依VectorVariableIndex變數作名稱的控管
						std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
						//存入向量變數名稱
						tempVector.Name = vectorVariableTemp;
						//存入向量
						Vectors.push_back(tempVector);
						//遞增VectorVariableIndex，以確保變數名稱不重複
						VectorVariableIndex++;
						//清除向量資料暫存
						tempVectorData.clear();
					}
					//遞增currentLoadVectorID，標記到當前讀取向量ID
					currentLoadVectorID++;
					//從檔案讀取字串，解析掉向量維度
					fin >> tempSring;
					tempdim = std::stoi(tempSring.c_str());
				}
				else
				{
					//讀取向量資料，並將string轉為double
					double value;
					value = (double)strtod(tempSring.c_str(), NULL);
					//將向量資料存入暫存
					if (tempVectorData.size() < tempdim)
					{
						tempVectorData.push_back(value);
					}
				}

			}
			//讀入輸入檔案中最後一個向量資訊
			Vector tempVector;
			tempVector.Data = tempVectorData;
			std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
			tempVector.Name = vectorVariableTemp;
			Vectors.push_back(tempVector);
			VectorVariableIndex++;
			//讀取成功回傳false
			return true;
		}
		else
		{
			Matrices.clear();
			VectorVariableIndex = 0;
			//標記當前讀取向量ID
			int currentLoadVectorID = 0;

			//定義Row資料暫存變數
			std::vector<double> tempRowData;

			
			//M的維度暫存
			int maxrow, maxcol;

			//定義讀取檔案字串暫存變數
			std::string tempSring;
			//從檔案讀取字串，解析掉M總數
			fin >> tempSring;

			//執行讀檔迴圈，並在讀到檔案結尾時結束
			while (!fin.eof())
			{
				//從檔案讀取字串
				fin >> tempSring;
				//解析到向量標記"M"
				if (tempSring == "M")
				{
					if (currentLoadVectorID != 0)
					{
						//定義Matrix
						Matrix tempMatrix;
						std::vector<double> row;
						int colcount = 0;
						for (int i = 0; i < tempRowData.size(); i++)
						{
							colcount++;
							if (colcount > maxcol)
							{
								tempMatrix.Data.push_back(row);
								row.clear();
								row.push_back(tempRowData[i]);
								colcount = 1;
							}
							else
							{
								row.push_back(tempRowData[i]);
							}
						}
						tempMatrix.Data.push_back(row);
						//定義向量變數名稱，依VectorVariableIndex變數作名稱的控管
						std::string vectorVariableTemp = "$m" + std::to_string(VectorVariableIndex);
						//存入向量變數名稱
						tempMatrix.Name = vectorVariableTemp;
						//存入向量
						Matrices.push_back(tempMatrix);
						//遞增VectorVariableIndex，以確保變數名稱不重複
						VectorVariableIndex++;
						//清除向量資料暫存
						tempRowData.clear();
					}
					//遞增currentLoadVectorID，標記到當前讀取向量ID
					currentLoadVectorID++;
					fin >> tempSring; 
					maxrow = std::stoi(tempSring.c_str());
					fin >> tempSring;
					maxcol = std::stoi(tempSring.c_str());
				}
				else
				{
					//讀取M資料，並將string轉為double
					double value;
					value = (double)strtod(tempSring.c_str(), NULL);
					//將M資料存入暫存
					if(tempRowData.size() < maxrow * maxcol)
						tempRowData.push_back(value);
				}

			}
			//END Matrix
			Matrix endMatrix;
			std::vector<double> row;
			int colcount = 0;
			for (int i = 0; i < tempRowData.size(); i++)
			{
				colcount++;
				if (colcount > maxcol)
				{
					endMatrix.Data.push_back(row);
					row.clear();
					row.push_back(tempRowData[i]);
					colcount = 1;
				}
				else
				{
					row.push_back(tempRowData[i]);
				}
			}
			endMatrix.Data.push_back(row);
			//定義向量變數名稱，依VectorVariableIndex變數作名稱的控管
			std::string vectorVariableTemp = "$m" + std::to_string(VectorVariableIndex);
			//存入向量變數名稱
			endMatrix.Name = vectorVariableTemp;
			//存入向量
			Matrices.push_back(endMatrix);
			//遞增VectorVariableIndex，以確保變數名稱不重複
			VectorVariableIndex++;
			//清除向量資料暫存
			tempRowData.clear();
			//讀取成功回傳true
			return true;
		}
	}
}

std::vector<Vector> DataManager::GetVectors()
{
	return Vectors;
}
std::vector<Matrix> DataManager::GetMatrices()
{
	return Matrices;
}
void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}