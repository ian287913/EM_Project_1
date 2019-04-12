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
std::vector<std::string> Processor::FunctionListM = {
		"rank",
		"trans",
		"sls",
		"det",
		"inv",
		"adj",
		"eigen",
		"pm",
		"ls",
		"rref",
		"cof"
};
std::vector<std::string> Processor::priority = { "*", "/", "%", "+", "-" };
std::vector<Vector> Processor::SourceVectors = std::vector<Vector>();
std::vector<Matrix> Processor::SourceMatrices = std::vector<Matrix>();
bool Processor::isVector = true;
std::string Processor::endl = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(System::Environment::NewLine)).ToPointer();

std::string Processor::Start(std::vector<std::string> input)
{
	if (input.size() == 0)
	{
		return "No Input";
	}
	else
	{
		if (isVector)
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
					std::vector<Vector> vvout;
					bool bout;
					double dout = 0.0;
					Vector vout, vout0;
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
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							vout = CaCu::Cross(vout, vout0);
							sout = VectorToString(vout);
							return sout;
						case 3:		// comp
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							dout = CaCu::Component(vout, vout0);
							strs << dout;
							sout += strs.str();
							return sout;
						case 4:		// proj
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							vout = CaCu::Projection(vout, vout0);
							sout = VectorToString(vout);
							return sout;
						case 5:		// area
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							dout = CaCu::Triangle(vout, vout0);
							strs << dout;
							sout += strs.str();
							return sout;
						case 6:		// ispar
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							bout = CaCu::IsParallel(vout, vout0);
							strs << ((bout) ? "True" : "False");
							sout += strs.str();
							return sout;
						case 7:		// isorth
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							bout = CaCu::IsOrthogonal(vout, vout0);
							strs << ((bout) ? "True" : "False");
							sout += strs.str();
							return sout;
						case 8:		// angle
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							dout = CaCu::Angle(vout, vout0);
							strs << dout;
							sout += strs.str();
							return sout;
						case 9:		// pn
							vout = getSource(input[1]);
							vout0 = getSource(input[2]);
							vout = CaCu::Cross(vout, vout0);
							sout = VectorToString(vout);
							return sout;
						case 10:	// islin
						case 11:	// ob 
							for (int i = 1; i < input.size(); i++)
							{
								vvout.push_back(getSource(input[i]));
							}
							vvout = CaCu::Orthonormal(vvout, vvout.size());
							for (Vector v : vvout)
							{
								strs << VectorToString(v) << std::endl;
							}
							sout += strs.str();
							return sout;
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
						throw std::exception("Stack error");
					output = VectorToString(stack[0]);
				}
				catch (std::exception& e)
				{
					output = "Processor error: ";
					output += e.what();
				}

				return output;
			}
		}
		else
		{
			if (find(FunctionListM.begin(), FunctionListM.end(), input[0]) != FunctionListM.end())	// is function
			{
				if (input.size() < 2)
					return "Function input format error";
				else
				{
					int func;
					for (int i = 0; i < FunctionListM.size(); i++)
					{
						if (FunctionListM[i] == input[0])
						{
							func = i;
							break;
						}
					}
					int iout;
					double dout = 0.0;
					Matrix mout0, mout1;
					std::vector<double> vdout;
					std::string sout = "";
					std::ostringstream strs;
					try
					{
						switch (func)
						{
						case 0:		// rank
							mout0 = getSourceM(input[1]);
							iout = CaCuMw::Rank(mout0);
							strs << "rank: " << iout;
							sout += strs.str();
							return sout;
						case 1:		// trans
							mout0 = getSourceM(input[1]);
							sout = MatrixToString(CaCuMi::Transpose(mout0));
							return sout;
						case 2:		// sls
							mout0 = getSourceM(input[1]);
							mout1 = getSourceM(input[2]);
							vdout = CaCuMw::solveLin(mout0, mout1);
							sout = VectorToString(vdout);
							return sout;
						case 3:		// det
							mout0 = getSourceM(input[1]);
							dout = CaCuMi::Determinant(mout0);
							strs << dout;
							sout += strs.str();
							return sout;
						case 4:		// inv
							mout0 = getSourceM(input[1]);
							sout = MatrixToString(CaCuMi::Inverse(mout0));
							return sout;
						case 5:		// adj
							mout0 = getSourceM(input[1]);
							sout = MatrixToString(CaCuMi::Adjoint(mout0));
							return sout;
						case 6:		// eigen
						case 7:		// pm
						case 8:		// ls
						case 9:		// rref
						case 10:	// cof
							mout0 = getSourceM(input[1]);
							sout = MatrixToString(CaCuMi::Cofactors(mout0));
							return sout;
						default:
							return "This function is invalid for now.";
							break;
						}
					}
					catch (const std::exception& e)
					{
						return e.what();
					}
					return "function end.";
				}
			}
			else	// is need to infix to postfix
			{
				std::vector<std::string> postfix = InfixToPostfix(input);
				// now process postfix:
				std::string output;
				std::vector<Matrix> stack;
				try
				{
					for (int i = 0; i < postfix.size(); i++)
					{
						if (postfix[i][0] == '$')
						{
							Matrix push = getSourceM(postfix[i]);
							stack.push_back(push);
						}
						else
						{
							if (postfix[i] == "+")
							{
								Matrix m1, m2, result;
								m1 = stack[stack.size() - 1];
								stack.pop_back();
								m2 = stack[stack.size() - 1];
								stack.pop_back();
								result = CaCuMw::Add(m1, m2);
								stack.push_back(result);
							}
							if (postfix[i] == "*")
							{
								Matrix m1, m2, result;
								m1 = stack[stack.size() - 1];
								stack.pop_back();
								m2 = stack[stack.size() - 1];
								stack.pop_back();
								result = CaCuMi::Multiply(m2, m1);
								stack.push_back(result);
							}
						}
					}
					if (stack.size() != 1)
						throw std::exception("Stack error");
					output = MatrixToString(stack[0]);
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
	output += endl;
	for (int i = 0; i < input.Data.size(); i++)
	{
		output += (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input.Data[i].ToString())).ToPointer();
		if (i != input.Data.size() - 1)
		{
			output += ", ";
			output += endl;
		}
	}
	output += "]";
	return output;
}
std::string Processor::VectorToString(std::vector<double> input)
{
	Vector v;
	v.Name = "No Name";
	v.Data = input;
	return VectorToString(v);
}
std::string Processor::MatrixToString(Matrix input)
{
	std::string output;
	for (int i = 0; i < input.Data.size(); i++)
	{
		for (int j = 0; j < input.Data[i].size(); j++)
		{
			output += (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input.Data[i][j].ToString())).ToPointer();
			if (j != input.Data[i].size() - 1)
				output += ", ";
		}
		output += (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(System::Environment::NewLine)).ToPointer();
	}
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
const Matrix Processor::getSourceM(std::string matName)
{
	for (int i = 0; i < SourceMatrices.size(); i++)
	{
		if (SourceMatrices[i].Name == matName)
			return SourceMatrices[i];
	}
	Matrix nullmat;
	nullmat.Name = "NULL";
	return nullmat;
}