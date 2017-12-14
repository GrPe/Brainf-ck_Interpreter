#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <stack>
#include <conio.h>



class Interpreter
{
private:
	//memory and 'pointer'
	std::array<uint8_t,30000> memory;
	std::stack<std::string::iterator> loopStack;
	uint32_t p; //current pointer

	//input file
	std::fstream inputFile;
	std::string code;
	void ReadFile(const std::string& fileName);

	//Main
	void Interpret();
	void InterpretSingleCommand(std::string::iterator& c);
	
	//Input char ,
	void InputChar(std::string::iterator&  it);

	//Loop []
	void JumpToEndOfLoop(std::string::iterator& it);

public:
	Interpreter() { p = 0; }
	void Run(const std::string& fileName);
};

