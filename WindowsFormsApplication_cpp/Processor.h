#pragma once
#include <vector>
#include <string>
#include "Vec.h"

static class Processor
{
public:
	static std::vector<std::string> FunctionList;
	static std::vector<std::string> priority;
	static std::vector<Vector> SourceVectors;

	static std::string Start(std::vector<std::string> input);
	static std::vector<std::string> InfixToPostfix(std::vector<std::string> input);
	static std::string VectorToString(Vector);
	static const Vector getSource(std::string);
};