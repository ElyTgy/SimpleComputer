#include "Functions.h"


const std::vector<std::unordered_map<std::string, std::string>> SetupSytaxTables()
{
	//comps and the a bit
	const std::unordered_map<std::string, std::string> CInstructionComps({
		{"0",   "0101010"},
		{"1",   "0111111"},
		{"-1",  "0111010"},
		{"D",   "0001100"},
		{"A",   "0110000"},
		{"!D",  "0001101"},
		{"!A",  "0110001"},
		{"-D",  "0001111"},
		{"-A",  "0110011"},
		{"D+1", "0011111"},
		{"A+1",	"0110111"},
		{"D-1",	"0001110"},
		{"A-1",	"0110010"},
		{"D+1",	"0000010"},
		{"D-A",	"0010011"},
		{"A-D",	"0000111"},
		{"D&A",	"0000000"},
		{"D|A",	"0010101"},
		{"M",	"1110000"},
		{"!M",	"1110001"},
		{"-M",	"1110011"},
		{"M+1",	"1110111"},
		{"M-1",	"1110010"},
		{"D+M",	"1000010"},
		{"D-M",	"1010011"},
		{"M-D",	"1000111"},
		{"D&M",	"1000000"},
		{"D|M",	"1010101"}
		});

	const std::unordered_map<std::string, std::string> CInstructionDests({
		{"null", "000"},
		{"M",	 "001"},
		{"D",	 "010"},
		{"MD",	 "011"},
		{"A",	 "100"},
		{"AM",	 "101"},
		{"AD",	 "110"},
		{"AMD",  "111"}
		});


	const std::unordered_map<std::string, std::string> CInstructionJumps({
		{"null", "000"},
		{"JGT",	 "001"},
		{"JEQ",	 "010"},
		{"JGE",	 "011"},
		{"JLT",	 "100"},
		{"JNE",	 "101"},
		{"JLE",	 "110"},
		{"JMP",  "111"}
		});

	return std::vector<std::unordered_map<std::string, std::string>>(
		{CInstructionComps, CInstructionDests, CInstructionJumps });
}
std::unordered_map<std::string, int> SetupPreDefinedTable()
{
	const std::unordered_map<std::string, int> PredefinedSymbols({

			{ "SP",		0},
			{ "LCL",	1},
			{ "ARG",	2},
			{ "THIS",	3},
			{ "THAT",	4},
			{ "R0",		0},
			{ "R1",		1},
			{ "R2",		2},
			{ "R3",		3},
			{ "R4",		4},
			{ "R5",		5},
			{ "R6",		6},
			{ "R7",		7},
			{ "R8",		8},
			{ "R9",		9},
			{ "R10",	10},
			{ "R11",	11},
			{ "R12",	12},
			{ "R13",	13},
			{ "R14",	14},
			{ "R15",	15},
			{ "SCREEN", 16384},
			{ "KBD",	24576}
		});

	return PredefinedSymbols;
}

void MakeSourceCodeClear(const std::string& fileName, const std::string& newFileName)
{
	std::string line;
	std::ifstream file(fileName);
	std::ofstream newFile;

	if (file.is_open())
	{
		newFile.open(newFileName);
		while (getline(file, line))
		{
			RemoveComments(line);
			RemoveSpace(line);
			if (line.size() == 0) { continue; }
			newFile << line << std::endl;
		}
		
		file.close();
		newFile.close();
	}
	else std::cout << "Unable to open file";
}

void RemoveSpace(std::string& line)
{
	for (std::string::iterator iter = line.begin(); iter != line.end();)
	{
		if (*iter == ' ')
		{
			line.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void RemoveComments(std::string& line)
{
	for (int i = 0; i < line.size()-1 && line.size() > 0; ++i)
	{
		if (line[i] == '/')
		{
			if (line[i + 1] == '/')
			{
				line.erase(i, line.size() - i);
				return;
			}
		}
	}
}

std::unordered_map<int, std::string>* GetTokenLineMap(const std::string& newFileName)
{
	std::fstream file;
	
	file.open(newFileName);
	if (file.is_open())
	{
		int lineNum = 0;
		std::string line;
		std::unordered_map<int, std::string>* tokenLinesMap = new std::unordered_map<int, std::string>;

		while (getline(file, line))
		{
			if (line[0] == '(')
			{
				continue;
			}
			else
			{
				tokenLinesMap->insert(std::pair<int, std::string>(lineNum, line));
				++lineNum;
			}
		}

		return tokenLinesMap;
	}
	else
	{
		std::cout << "unable to open file";
	}
}

const std::unordered_map<std::string, int>const* GetJumpTokenLineNumsMap(const std::string& newFileName)
{
	std::fstream file;

	file.open(newFileName);
	if (file.is_open())
	{
		int lineNum = 0;
		std::string line;
		std::unordered_map<std::string, int>* JumpTokenLineNum = new std::unordered_map<std::string, int>;

		while (getline(file, line))
		{
			if (line[0] == '(')
			{
				JumpTokenLineNum->insert({line.substr(1, line.size()-2), lineNum+1});
			}
			++lineNum;
		}

		return JumpTokenLineNum;
	}
	else
	{
		std::cout << "unable to open file";
	}
}

bool IsAInsctruction(const std::string& str)
{
	if (str[0] == '@')
	{
		return true;
	}
	return false;
}

std::string IntToBinaryStr(int number, int maxBitNum)
{
	if (number > pow(2, maxBitNum)) { std::cout << "number is too big";abort; }
	std::vector<int>indicesForOne;
	while (number > 0)
	{
		int exponent = log2(number);
		number = number - pow(2, exponent);
		indicesForOne.push_back(exponent);
	}

	std::string binaryNum = "";
	for (int i = 0; i < maxBitNum; ++i)
	{
		std::vector<int>::iterator it = find(indicesForOne.begin(), indicesForOne.end(), i);
		if (it != indicesForOne.end())
		{
			binaryNum = binaryNum + "1";
		}
		else
		{
			binaryNum = binaryNum + "0";
		}
	}

	//reverse the actual binary digits
	int j = binaryNum.size() - 1;
	for (int i = 0; i < binaryNum.size(); ++i)
	{
		char tempDigitAtI = binaryNum[i];

		binaryNum[i] = binaryNum[j];
		binaryNum[j] = tempDigitAtI;
		--j;
	}

	return binaryNum;
}

void ChangeTokensToBinary
(std::unordered_map<int, std::string>*& tokenMap,
	const std::unordered_map<std::string, int>& PreDefinedSymbolsMap,
	const std::unordered_map<std::string, int>const*& jumpTokenLineNums,
	const std::vector<std::unordered_map<std::string, std::string>>& CInstructionMaps)
{
	constexpr int maxDigits = 15;

	for (std::unordered_map<int, std::string>::iterator tokenIter = tokenMap->begin();
		tokenIter != tokenMap->end(); ++tokenIter)
	{
		std::string line = tokenIter->second;

		if (IsAInsctruction(line))
		{
			line = line.substr(1, line.size() - 1); //remove the @ sign so that we dont have to repeat substr operation mutiple times

			std::unordered_map<std::string, int>::const_iterator preDefMapIter = PreDefinedSymbolsMap.find(line);
			std::unordered_map<std::string, int>::const_iterator jumpTokenIter = jumpTokenLineNums->find(line);

			if (preDefMapIter != PreDefinedSymbolsMap.end())
			{
				tokenIter->second = GetBinaryAInstruction(preDefMapIter->second, maxDigits);
			}
			else if (jumpTokenIter != jumpTokenLineNums->end())
			{
				tokenIter->second = GetBinaryAInstruction(jumpTokenIter->second, maxDigits);
			}
			else
			{
				tokenIter->second = GetBinaryAInstruction(stoi(line), maxDigits);
			}
		}
		else
		{
			//dest = comp ; jump

			std::string cInstructionOp = "111"; //should be constexpr

			int compStartIndex = 0;
			int compEndIndex = line.size() - 1;

			auto equalSignIndex = line.find("=");
			auto semicolonIndex = line.find(";");

			std::string destInstructionBinary = "";
			std::string jumpInstructionBinary = "";

			if (equalSignIndex != std::string::npos)//has dest section
			{
				compStartIndex = equalSignIndex + 1;
				std::string destInstruction(1, line[0]); //dest can only be one 
				destInstructionBinary = GetValForKeyInMap(CInstructionMaps[Dests], destInstruction);
			}
			if (semicolonIndex != std::string::npos)//has jump section
			{
				compEndIndex = semicolonIndex - 1;
				std::string jumpInstruction = line.substr(semicolonIndex + 1, line.size() - 1);
				jumpInstructionBinary = GetValForKeyInMap(CInstructionMaps[Jumps], jumpInstruction);
			}

			std::string compInstruction = line.substr(compStartIndex, compEndIndex - compStartIndex + 1);
			std::string compInstructionBinary = GetValForKeyInMap(CInstructionMaps[Comps], compInstruction);

			tokenIter->second = cInstructionOp + compInstructionBinary + destInstructionBinary + jumpInstructionBinary;
		}
	}
}

std::string GetBinaryAInstruction(int tokensInstructionLine, int maxBinaryDigits)
{
	std::string binaryLine = "0"; //Should be constexpr
	return binaryLine + IntToBinaryStr(tokensInstructionLine, maxBinaryDigits);;
}

std::string GetValForKeyInMap(const std::unordered_map<std::string, std::string >& map, const std::string& strKey)
{
	for (std::unordered_map<std::string, std::string>::const_iterator iter = map.begin(); iter != map.end(); ++iter)
	{
		if (strKey == iter->first)
		{
			return iter->second;
		}
	}

	std::cout << "reached end of search for value for c instructions";
}

void WriteBinaryFile(std::unordered_map<int, std::string>*& tokenMap, const std::string& binaryFileName)
{
	std::string line;;
	std::ofstream file;
	file.open(binaryFileName);

	if (file.is_open())
	{
		for (std::unordered_map<int, std::string>::const_iterator iter = tokenMap->begin(); iter != tokenMap->end(); ++iter)
		{
			file << iter->second << std::endl;
		}
		file.close();
	}
	else std::cout << "Unable to open file";
}