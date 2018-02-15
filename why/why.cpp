#include "why.h"
#include <minmax.h>
#include <memory>

int main()
{
	int i = 1;
	cout << CPHelper::bitwise::rawData<int>(&i) << endl;
	unsigned short s = SHRT_MAX* 2;
	cout << CPHelper::bitwise::rawData<unsigned short>(&s) << endl;
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

	system("pause");
    return 0;
}

