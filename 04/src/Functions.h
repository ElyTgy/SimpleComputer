#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>


enum CInstructMapIndices
{
	Comps = 0,
	Dests,
	Jumps
};

const std::vector<std::unordered_map<std::string, std::string>> SetupSytaxTables();
void MakeSourceCodeClear(const std::string& fileName, const std::string& newFileName);
void RemoveSpace(std::string& line);
void RemoveComments(std::string& line);
std::unordered_map<int, std::string>* GetTokenLineMap(const std::string& newFileName);
const std::unordered_map<std::string, int>const* GetJumpTokenLineNumsMap(const std::string& newFileName);
bool IsAInsctruction(const std::string& str);
std::string IntToBinaryStr(int number, int maxBitNum);
std::unordered_map<std::string, int> SetupPreDefinedTable();
void ChangeTokensToBinary
(std::unordered_map<int, std::string>*& tokenMap,
	const std::unordered_map<std::string, int>& PreDefinedSymbolsMap,
	const std::unordered_map<std::string, int>const*& jumpTokenLineNums,
	const std::vector<std::unordered_map<std::string, std::string>>& CInstructionMaps);
std::string GetBinaryAInstruction(int tokensInstructionLine, int maxBinaryDigits);
std::string GetValForKeyInMap(const std::unordered_map<std::string, std::string >& map, const std::string& strKey);
void WriteBinaryFile(std::unordered_map<int, std::string>*& tokenMap, const std::string& binaryFileName);