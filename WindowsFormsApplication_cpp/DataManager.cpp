#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
}

bool DataManager::LoadVectorData(bool isVec)
{
	std::fstream fin;
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);
	//Ū�����Ѧ^��false
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
			//�аO��eŪ���V�qID
			int currentLoadVectorID = 0;
			//�w�q�V�q��ƼȦs�ܼ�
			std::vector<double> tempVectorData;
			//�w�qŪ���ɮצr��Ȧs�ܼ�
			std::string tempSring;
			//�q�ɮ�Ū���r��A�ѪR���V�q�`��
			fin >> tempSring;
			
			int tempdim;
			//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
			while (!fin.eof())
			{
				//�q�ɮ�Ū���r��
				fin >> tempSring;
				//�ѪR��V�q�аO"V"
				if (tempSring == "V")
				{
					if (currentLoadVectorID != 0)
					{
						//�w�q�Ȧs�V�q��Ƶ��c
						Vector tempVector;
						//�s�J�V�q���
						tempVector.Data = tempVectorData;
						//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
						std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
						//�s�J�V�q�ܼƦW��
						tempVector.Name = vectorVariableTemp;
						//�s�J�V�q
						Vectors.push_back(tempVector);
						//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
						VectorVariableIndex++;
						//�M���V�q��ƼȦs
						tempVectorData.clear();
					}
					//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
					currentLoadVectorID++;
					//�q�ɮ�Ū���r��A�ѪR���V�q����
					fin >> tempSring;
					tempdim = std::stoi(tempSring.c_str());
				}
				else
				{
					//Ū���V�q��ơA�ñNstring�ରdouble
					double value;
					value = (double)strtod(tempSring.c_str(), NULL);
					//�N�V�q��Ʀs�J�Ȧs
					if (tempVectorData.size() < tempdim)
					{
						tempVectorData.push_back(value);
					}
				}

			}
			//Ū�J��J�ɮפ��̫�@�ӦV�q��T
			Vector tempVector;
			tempVector.Data = tempVectorData;
			std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
			tempVector.Name = vectorVariableTemp;
			Vectors.push_back(tempVector);
			VectorVariableIndex++;
			//Ū�����\�^��false
			return true;
		}
		else
		{
			Matrices.clear();
			VectorVariableIndex = 0;
			//�аO��eŪ���V�qID
			int currentLoadVectorID = 0;

			//�w�qRow��ƼȦs�ܼ�
			std::vector<double> tempRowData;

			
			//M�����׼Ȧs
			int maxrow, maxcol;

			//�w�qŪ���ɮצr��Ȧs�ܼ�
			std::string tempSring;
			//�q�ɮ�Ū���r��A�ѪR��M�`��
			fin >> tempSring;

			//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
			while (!fin.eof())
			{
				//�q�ɮ�Ū���r��
				fin >> tempSring;
				//�ѪR��V�q�аO"M"
				if (tempSring == "M")
				{
					if (currentLoadVectorID != 0)
					{
						//�w�qMatrix
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
						//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
						std::string vectorVariableTemp = "$m" + std::to_string(VectorVariableIndex);
						//�s�J�V�q�ܼƦW��
						tempMatrix.Name = vectorVariableTemp;
						//�s�J�V�q
						Matrices.push_back(tempMatrix);
						//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
						VectorVariableIndex++;
						//�M���V�q��ƼȦs
						tempRowData.clear();
					}
					//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
					currentLoadVectorID++;
					fin >> tempSring; 
					maxrow = std::stoi(tempSring.c_str());
					fin >> tempSring;
					maxcol = std::stoi(tempSring.c_str());
				}
				else
				{
					//Ū��M��ơA�ñNstring�ରdouble
					double value;
					value = (double)strtod(tempSring.c_str(), NULL);
					//�NM��Ʀs�J�Ȧs
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
			//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
			std::string vectorVariableTemp = "$m" + std::to_string(VectorVariableIndex);
			//�s�J�V�q�ܼƦW��
			endMatrix.Name = vectorVariableTemp;
			//�s�J�V�q
			Matrices.push_back(endMatrix);
			//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
			VectorVariableIndex++;
			//�M���V�q��ƼȦs
			tempRowData.clear();
			//Ū�����\�^��true
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