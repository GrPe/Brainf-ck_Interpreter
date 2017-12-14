#include "Interpreter.hpp"

void Interpreter::ReadFile(const std::string& fileName)
{
	inputFile.open(fileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cerr << "Cannot open a file: " << fileName << "\n";
		exit(1);
	}

	std::string temp{ std::istreambuf_iterator<char>(inputFile),std::istreambuf_iterator<char>() };
	code = temp;

	inputFile.close();
}

void Interpreter::Interpret()
{
	auto c = code.begin();
	while (c != code.end())
	{
		InterpretSingleCommand(c);
		c++;
	}
}

void Interpreter::InterpretSingleCommand(std::string::iterator& c)
{
	switch (*c)
	{
	case '>':
		++p;
		break;
	case '<':
		--p;
		break;
	case '+':
		++memory[p];
		break;
	case '-':
		--memory[p];
		break;
	case '.':
		std::cout << static_cast<unsigned char>(memory[p]);
		break;
	case ',':
		InputChar(c);
		break;
	case '[':
		if (memory[p])
			loopStack.push(c);
		else 
			JumpToEndOfLoop(c);
		break;
	case ']':
		if (memory[p]) c = loopStack.top();
		else loopStack.pop();
		break;
	}
}

void Interpreter::InputChar(std::string::iterator& it)
{
	//conio.h -> input without enter -> C style
	char tmp;
	tmp = _getch();
	if(tmp != EOF)
		memory[p] = static_cast<uint8_t>(tmp);
}

void Interpreter::JumpToEndOfLoop(std::string::iterator& it)
{
	auto iter = it;
	int32_t counter = 0;
	for (iter; iter != code.end(); iter++)
	{
		if (*iter == '[') counter++;
		if (*iter == ']') counter--;
		if (!counter)
		{
			it = iter;
			return;
		}
	}
	std::cerr << "Error! End of loop not found ']'\n";
	exit(1);
}

void Interpreter::Run(const std::string& fileName)
{
	ReadFile(fileName);
	Interpret();
}
