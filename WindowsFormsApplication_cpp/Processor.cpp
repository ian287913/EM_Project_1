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
				double dout = 0.0;
				Vector vout;
				std::string sout = "";
				std::ostringstream strs;
				try
				{
					switch (func)
					{
					case 0:		// norm 
						vout = getSource(input[1]);
						dout = CaCu::Norm(vout);
						strs << dout;
						sout += strs.str();
						return sout;
					case 1:		// normlz
						vout = getSource(input[1]);
						vout = CaCu::Normalize(vout);
						sout = VectorToString(vout);
						return sout;
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
				}
				catch (const std::exception& e)
				{
				}
				return "function end.";
			}
		}
		else	// is need to infix to postfix
		{
			std::vector<std::string> postfix = InfixToPostfix(input);
			// now process postfix:
			std::string output;
			std::vector<Vector> stack;
			try
			{
				for (int i = 0; i < postfix.size(); i++)
				{
					if (postfix[i][0] == '$')
					{
						Vector push = getSource(postfix[i]);
						stack.push_back(push);
					}
					else
					{
						if (postfix[i] == "+")
						{
							Vector v1, v2, result;
							v1 = stack[stack.size() - 1];
							stack.pop_back();
							v2 = stack[stack.size() - 1];
							stack.pop_back();
							result = CaCu::Add(v1, v2);
							stack.push_back(result);
						}
						if (postfix[i] == "*")
						{
							Vector v1, v2, result;
							v1 = stack[stack.size() - 1];
							stack.pop_back();
							v2 = stack[stack.size() - 1];
							stack.pop_back();
							if (v1.Data.size() > 1)
							{
								Vector re;
								re.Data.clear();
								re.Data.push_back(CaCu::Dot(v2, v1));
								result = re;
							}
							else
								result = CaCu::Scale(v2, v1);
							stack.push_back(result);
						}
					}
				}
				if (stack.size() != 1)
					throw new std::exception("Stack error");
				output = VectorToString(stack[0]);
			}
			catch (const myException e)
			{
				output = "Cacu error: " + e.Content;
			}
			catch (const std::exception& e)
			{
				output = "Processor error: ";
				output += e.what();
			}

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