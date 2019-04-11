#include"Processor.h"

std::vector<std::string> Processor::FunctionList = {
		"norm",
		"normlz",
		"cross",
		"comp",
		"proj",
		"area",
		"ispar",
		"isorth",
		"angle",
		"pn",
		"islin",
		"ob"
};
std::vector<std::string> Processor::priority = { "*", "/", "%", "+", "-" };
std::vector<Vector> Processor::SourceVectors = std::vector<Vector>();

std::string Processor::Start(std::vector<std::string> input)
{
	if (input.size() == 0)
	{
		return "No Input";
	}
	else
	{
		if (find(FunctionList.begin(), FunctionList.end(), input[0]) != FunctionList.end())	// is function
		{
			if (input.size() < 2)
				return "Function input format error";
			else
			{
				int func;
				for (int i = 0; i < FunctionList.size(); i++)
				{
					if (FunctionList[i] == input[0])
					{
						func = i;
						break;
					}
				}
				switch (func)
				{
				case 0:		// norm 

				case 1:		// normlz
				case 2:		// cross
				case 3:		// comp
				case 4:		// proj
				case 5:		// area
				case 6:		// ispar
				case 7:		// isorth
				case 8:		// angle
				case 9:		// pn
				case 10:	// islin
				case 11:	// ob 
				default:
					return "This function is invalid for now.";
					break;
				}
				return "function end.";
			}
		}
		else	// is need to infix to postfix
		{
			std::vector<std::string> postfix = InfixToPostfix(input);
			// now process postfix:
			std::string output;


			// test postfix out
			for (int i = 0; i < postfix.size(); i++)
			{
				output += postfix[i];
			}
			// test

			return output;
		}
	}
}
std::vector<std::string> Processor::InfixToPostfix(std::vector<std::string> input)
{
	std::vector<std::string> infix = input;
	std::vector<std::string> stack;
	std::vector<std::string> output;

	infix.push_back(")");
	stack.push_back("(");
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == "(")
			stack.push_back("(");
		else if (infix[i] == ")")
		{
			while (true)
			{
				if (stack[stack.size() - 1] == "(")
				{
					stack.pop_back();
					break;
				}
				else
				{
					output.push_back(stack[stack.size() - 1]);
					stack.pop_back();
				}
			}
		}
		else if (find(priority.begin(), priority.end(), infix[i]) != priority.end()) // is a operator
		{
			if (infix[i] == "*" || infix[i] == "/" || infix[i] == "%")
			{
				while (true)
				{
					if (stack[stack.size() - 1] == "-" || stack[stack.size() - 1] == "+" || stack[stack.size() - 1] == "(")
						break;
					output.push_back(stack[stack.size() - 1]);
					stack.pop_back();
				}
				stack.push_back(infix[i]);
			}
			else
			{
				while (true)
				{
					if (stack[stack.size() - 1] == "(")
						break;
					output.push_back(stack[stack.size() - 1]);
					stack.pop_back();
				}
				stack.push_back(infix[i]);
			}
		}
		else
		{
			// is a var
			output.push_back(infix[i]);
		}
	}
	while (stack.size() != 0)
	{
		if (stack[stack.size() - 1] != "(")
			output.push_back(stack[stack.size() - 1]);
		stack.pop_back();
	}
	return output;
}
std::string Processor::VectorToString(Vector input)
{
	std::string output = "[";
	for (int i = 0; i < input.Data.size(); i++)
	{
		output += (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input.Data[i].ToString())).ToPointer();
		if (i != input.Data.size() - 1)
			output += ", ";
	}
	output += "]";
	return output;
}
const Vector Processor::getSource(std::string vecName)
{
	for (int i = 0; i < SourceVectors.size(); i++)
	{
		if (SourceVectors[i].Name == vecName)
			return SourceVectors[i];
	}
	Vector nullvec;
	nullvec.Name = "NULL";
	return nullvec;
}