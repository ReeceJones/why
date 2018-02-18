#include "why.h"
#include <minmax.h>
#include <fstream>

#include <Windows.h>

//reduce overhead by excluding headers we don't need

int main()
{
	int i = 1;
	cout << CPHelper::bitwise::rawData<int>(&i) << endl;
	unsigned short s = SHRT_MAX* 2;
	cout << CPHelper::bitwise::rawData<unsigned short>(&s) << endl;
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
	//vector<string> asdf = 
	//{
	//	"....",
	//	"....",
	//	"....",
	//	"....",
	//};
	//CPHelper::pathfinding::Node start = { nullptr, 0, 0, 0.f, 0.f, 0.f };
	//CPHelper::pathfinding::Node end = { nullptr, 3, 3, 0.f, 0.f, 0.f };
	//CPHelper::pathfinding::Field* f = new CPHelper::pathfinding::Field(asdf);
	//auto solution = CPHelper::pathfinding::aStar(start, end, f, ".", PATHFIND_DIAGONAL | PATHFIND_NORMAL);

	//cout << "solution" << endl;
	//for (CPHelper::pathfinding::Node n : solution)
	//	cout << n.x << ", " << n.y << endl;
	//f->display(solution.at(0));

	cout << "official HP Codewars maze problem: " << endl;
	
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
	auto solution = CPHelper::pathfinding::aStar(startPos, endPos, mazeField, " X", PATHFIND_DIAGONAL | PATHFIND_NORMAL);
	mazeField->display(solution.at(0));

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

	system("pause");
    return 0;
}

