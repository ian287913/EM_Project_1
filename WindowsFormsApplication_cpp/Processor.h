#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Vec.h"
#include "Matrix.h"
#include "CaCu.h"

static class Processor
{
public:
	static std::vector<std::string> FunctionList;
	static std::vector<std::string> FunctionListM;
	static std::vector<std::string> priority;
	static std::vector<Vector> SourceVectors;
	static std::vector<Matrix> SourceMatrices;
	static bool isVector;

	static std::string Start(std::vector<std::string> input);
	static std::vector<std::string> InfixToPostfix(std::vector<std::string> input);
	static std::string VectorToString(Vector);
	static std::string MatrixToString(Matrix);
	static const Vector getSource(std::string);
	static const Matrix getSourceM(std::string);
};