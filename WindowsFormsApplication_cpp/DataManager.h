#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Processor.h"

//�w�q���޸��class
class DataManager
{
private:
	std::vector<Matrix> Matrices;
	//�x�s�V�q���
	std::vector<Vector> Vectors;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;
	//�����ɮ׸��|�W��
	std::string FileName;
public:
	DataManager();
	//Ū���V�q���
	bool LoadVectorData(bool isVec);
	//���o�V�q���
	std::vector<Vector> GetVectors();
	//���o�x�}���
	std::vector<Matrix> GetMatrices();
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
};
