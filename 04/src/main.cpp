//TODO: REFACTOR FUNCTIONS, MAKE MORE EFFICIENT, ADD DEFINS FOR MAP NAMES, DIVIDE INTO CLASSES
//TODO: MAKE A FILE CLASS
//TODO: READ THE LOOK UP TABLE INFORMATION FROM A JSON OR CSV FILE
//TODO: REPLACE THE WHILE LOOPS FOR READING FILES WITH PREPROCCESSORS
//TODO: Make the operation codes for instructions constexpr

//DONE: Set up the lookup tables: make a dictionary of the pre reserved words and their values, make a dictionary of the meanings of the words in c-instruction.

//DONE: load the file 

//DONE: scan the file and make a dictionary of the lines and their line number, starting from 0. Ignore any character after '//' and any space. 
//Ignore blank lines and give th value of -1 to any line that has a pair of paranthesis ''''and write the actual line without the paranthesis in the dictionary''''

//DONE: Scan the tokens again, looking for a '('. Write the word in the paranthesis in a new dictioary for jump labels of the program. Look for all the values in the program flow
//dictionary and look for matching tokens that start with @. write their line number as the value of this new dictionary

//DONE: Scan the token dict looking for tokens that start with @. Check wheather theyre in the jump label table. Check if in Predefined table and replace.If not, then change to int and change the value to a 15 bit, unsigned binary value. the MSB must be zero.
//Keep a counter to remember which number should be assiged to its memory.The initial value should be 16. Convert all the numbers(including )

//DONE:lse they dont start with @, the token is a c instruction. the three leftmost bits will be ones. the fourth will be 0. 
//if there is a '=' copy the string after it unitl u reach the end of the string or the ';' symbol. Look for the command in the comp
//table. reserve its corrosponding value as the binary code for the comp section
//if there

//Close the file

#include "Functions.h"


int main()
{
	const std::string file = "assemblyFile.asm";
	const std::string newAssemblyFile = "newAssemblyFile.asm";
	const std::string binaryFile = "binary.txt";
	constexpr int maxDigits = 15;

	MakeSourceCodeClear(file, newAssemblyFile);
	
	std::vector<std::unordered_map<std::string, std::string>> CInstructionMaps = SetupSytaxTables();
	std::unordered_map<std::string, int> PreDefinedSymbolsMap = SetupPreDefinedTable();
	std::unordered_map<int, std::string>* tokenMap = GetTokenLineMap(newAssemblyFile);
	const std::unordered_map<std::string, int>const* jumpTokenLineNums = GetJumpTokenLineNumsMap(newAssemblyFile);

	ChangeTokensToBinary(tokenMap, PreDefinedSymbolsMap, jumpTokenLineNums, CInstructionMaps);
	WriteBinaryFile(tokenMap, binaryFile);

	delete tokenMap;
	delete jumpTokenLineNums;
	EXIT_SUCCESS;
}