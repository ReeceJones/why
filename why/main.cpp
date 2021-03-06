#include "why.h"
#include <minmax.h>
#include <fstream>

#include <Windows.h>

/*
this header causes issues with compilation sometimes
if you get "internal build error" just right-click on the project, and click rebuild
*/
#include <iomanip>

#define MAZE_STRESS_SIZE 100

vector<string> rf()
{
	ifstream ifile("input.txt");
	vector<string> ret;
	ret.push_back(CPHelper::input::getSingleLine(ifile));
	ret.push_back(CPHelper::input::getSingleLine(ifile));
	ifile.close();
	return ret;
}

int main()
{
	SetConsoleTitleA("Magnum 3.1415926535897932384626433832795028");
	int i = 1;
	cout << CPHelper::bitwise::rawData<int>(i) << endl;
	unsigned short s = SHRT_MAX* 2;
	cout << CPHelper::bitwise::rawData<unsigned short>(s) << endl;
	cout << "estimated bits in 255: " << CPHelper::bitwise::estimateBits(255) << endl;
	cout << "estimated bits in 256: " << CPHelper::bitwise::estimateBits(256) << endl;
	cout << "enter something to tokenize it" << endl;
	string input = CPHelper::input::getSingleLine();
	vector<string> tokens = CPHelper::stringprocessor::getTokens(input, ' ');
	for (string str : tokens)
		cout << str << endl;
	cout << "type \"0 0\" to quit this input" << endl;
	vector<string> lns = CPHelper::input::getInput("0 0");
	for (string str : lns)
		cout << str << endl;
	cout << "input a string to have every 4th character removed" << endl;
	string nth = CPHelper::input::getSingleLine();
	string nprime = CPHelper::stringprocessor::removeNthOccurence(4, nth);
	cout << nprime << endl;
	
	CPHelper::output::OutputBuffer *out = new CPHelper::output::OutputBuffer(10, 5, 'X');
	for (int i = 0; i < out->getWidth(); i++)
		out->writeToBuffer(i, abs(i - 4), 'O');
	out->display();

	string fixme = "xxxxxxxmexxxmxxxexxxx";
	cout << CPHelper::stringprocessor::removeAboveThreshold(fixme, 4) << endl;

	string something = "bent e ken"; // should be just e
	cout << "shared letters in \"" << something << "\": " << CPHelper::stringprocessor::sharedLetters(something) << endl;

	cout << "BST:" << endl;
	CPHelper::dataprocessor::BinarySearchTree<int>* BST = new CPHelper::dataprocessor::BinarySearchTree<int>(10);
	BST->insert(5);
	BST->insert(15);
	BST->insert(20);
	cout << "Lowest Value in {10, 5, 15, 20}: " << BST->getMin() << endl;
	cout << "Largest Value in {10, 5, 15, 20}: " << BST->getMax() << endl;

	cout << "The Hex Value 4F in Ascii is: " << CPHelper::stringprocessor::escapeHexCode("4F") << endl;
	cout << "The Binary Value 01001100 is: " << CPHelper::stringprocessor::escapeBinary("01001100") << endl;
	cout << "The Octal Value 120 is: " << CPHelper::stringprocessor::escapeOctal("120") << endl;
	cout << "The Decimal Value 83 is: " << CPHelper::stringprocessor::escapeDecimal("83") << endl;

	cout << "The Hex Value of 50 is: " << CPHelper::stringprocessor::toHex((char)50) << endl;
	cout << "The Binary Value of 4 is: " << CPHelper::stringprocessor::toBinary((char)4) << endl;
	cout << "The Octal Value of 11 is: " << CPHelper::stringprocessor::toOctal((char)11) << endl;

	CPHelper::output::Bododo();

	cout << "We are going to now solve a maze, watch our amazingness!" << endl;
	cout << "Maze stress test: " << endl;
	//this was just a test maze, you can use it if you want
	vector<string> asdf;
	for (unsigned int i = 0; i < MAZE_STRESS_SIZE; i++)
	{
		asdf.push_back(string(MAZE_STRESS_SIZE, '.'));
	}
	CPHelper::pathfinding::Node start = { nullptr, 0, 0, 0.f, 0.f, 0.f };
	CPHelper::pathfinding::Node end = { nullptr, MAZE_STRESS_SIZE - 1, MAZE_STRESS_SIZE - 1, 0.f, 0.f, 0.f };
	CPHelper::pathfinding::Field* f = new CPHelper::pathfinding::Field(asdf);
	CPHelper::time::startRecording();
	auto solution = CPHelper::pathfinding::aStar(start, end, f, ".", PATHFIND_NORMAL);
	cout << "solved stress test in " << (float)(CPHelper::time::stopRecording()) / 1000.f << "s" << endl;
	f->display(solution.at(0), start, end, '*', '*');

	cout << "official HP Codewars maze problem: " << endl;
	CPHelper::time::startRecording();

	ifstream mazeFile("maze.txt");
	vector<string> maze;
	string tmp;
	while (getline(mazeFile, tmp))
		maze.push_back(tmp);
	CPHelper::pathfinding::Field* mazeField = new CPHelper::pathfinding::Field(maze);
	CPHelper::pathfinding::Node startPos;
	CPHelper::pathfinding::Node endPos;

	//starting position is a @
	//ending position is a X
	for (unsigned int i = 0; i < maze.size(); i++)
	{
		string ln = maze.at(i);
		for (unsigned int x = 0; x < ln.size(); x++)
		{
			char c = ln.at(x);
			if (c == '@')
			{
				//startPos.x = x;
				//startPos.y = i;
				startPos = { nullptr, (int)x, (int)i, 0.f, 0.f, 0.f };
			}
			else if (c == 'X')
			{
				//endPos.x = x;
				//endPos.y = i;
				endPos = { nullptr, (int)x, (int)i, 0.f, 0.f, 0.f };
			}
		}
	}
	cout << "Start: " << "(" << startPos.x << ", " << startPos.y << ")" << endl;
	cout << "End: " << "(" << endPos.x << ", " << endPos.y << ")" << endl;
	solution = CPHelper::pathfinding::aStar(startPos, endPos, mazeField, " X", PATHFIND_DIAGONAL | PATHFIND_NORMAL);
	cout << "It took " << CPHelper::time::stopRecording() << "ms to solve the maze!" << endl;
	mazeField->display(solution.at(0), startPos, endPos, '@', 'X');

	cout << "Dictionary Example: " << endl;
	vector<char> base;
	base.push_back('a');
	base.push_back('b');
	base.push_back('c');

	vector<string> translation;
	translation.push_back("Hell");
	translation.push_back("o Wor");
	translation.push_back("ld!");

	CPHelper::stringprocessor::Dictionary* dict = new CPHelper::stringprocessor::Dictionary(base, translation);
	dict->dumpDictionary();
	cout << "\"abc\" -> " << "\"" << dict->translate("abc") << "\"" << endl;

	//test catching input from a file
	CPHelper::output::printVector<string>(rf());

	vector<int> l = { 1,2,3,4,5 };
	vector<int> r = { 4,3,2,1,0 };
	cout << "the sum of { 1, 2, 3, 4, 5 } and { 4, 3, 2, 1, 0 } is:" << endl;
	CPHelper::output::printVector<int>(CPHelper::math::sum(l, r));

	CPHelper::output::pause("we're pausing right now!");

	string remPunc = "We're going to remove puncuation and spaces from this string!";
	cout <<  remPunc << endl;
	cout << CPHelper::stringprocessor::removeChars(remPunc, "'.,;:!?[]{}-\\/_=+@#$%^&*()`~ ") << endl;

	string palindrome = "racecar";
	cout << palindrome << " backwards is " << CPHelper::stringprocessor::reverseString(palindrome) << endl;

	cout << "123.456 to a string should be " << CPHelper::stringprocessor::toString<float>(123.456f) << endl;
	cout << "the average of 1, 5, and 2 is: " << setprecision(2) << fixed << CPHelper::dataprocessor::avg<int>(vector<int>{1, 5, 2}) << endl;

	wstring toBeNarrowed = L"this is a wide-string";
	wcout << L"(wcout) " << toBeNarrowed << endl;
	cout << "(cout) " << CPHelper::stringprocessor::narrowString(toBeNarrowed) << endl;

	string b = "this is a ";
	string e = "string in multiple parts";
	cout << CPHelper::stringprocessor::append(b, e) << endl;
	cout << CPHelper::stringprocessor::prepend(e, b) << endl;

	string justforrishabh = string("1234567890") * 4;
	cout << justforrishabh << endl;

	//now just to test the Input class
	CPHelper::input::Input* inputTest = new CPHelper::input::Input();
	ifstream infile("input.txt");
	inputTest->getInput("0 0", infile);
	for (unsigned int i = 0; i < inputTest->numLines(); i++)
	{
		cout << "Line " << i << ": " << endl;
		for (unsigned int x = 0; x < inputTest->getLine(i)->numElements(); x++)
		{
			cout << "\t" << inputTest->getLine(i)->getElement(x)->getString() << endl;
		}
	}

	cout << "there are " << CPHelper::input::getFileLines("input.txt") << " lines in input.txt" << endl;
	cout << "there are " << CPHelper::input::getFileLines("maze.txt") << " lines in maze.txt" << endl;


	CPHelper::output::pause("PRESS ANY KEY TO END THE PROGRAM...");
    return 0;
}

