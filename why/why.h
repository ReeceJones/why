#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

//named the namespace the wrong thing because i was thinking of something else, so I guess it stands for "copy-paste helper"
namespace CPHelper
{
	namespace bitwise
	{
		template<typename T>
		bool testBit(T *data, unsigned short pos)
		{
			return (*data) & (1 << pos);
		}
		template<typename T>
		unsigned short numBits()
		{
			return sizeof(T) * 8;
		}
		template<typename T>
		string rawData(T *data)
		{
			string b = "";
			const unsigned int uFlag = 1;
			for (unsigned short l = 0; l < numBits<T>(); l++)
			{
				b += (testBit<T>(data, l)) ? '1' : '0';
			}
			return b;
		}
		unsigned short estimateBits(unsigned long value)
		{
			//log base 2 value
			return floorl((log(value) / log(2)));
		}
	}
	namespace input
	{
		vector<string> getInput(istream& inputStream, string terminator)
		{
			vector<string> buf;
			string in;
			do
			{
				getline(inputStream, in);
				buf.push_back(in);
			} while (strcmp(in.c_str(), terminator.c_str()) != 0);
			//remove the terminator from the buffer
			buf.pop_back();
			return buf;
		}
		vector<string> getInput(string terminator)
		{
			return getInput(cin, terminator);
		}
		string getSingleLine(istream& inputStream)
		{
			string ln;
			getline(inputStream, ln);
			return ln;
		}
		string getSingleLine()
		{
			return getSingleLine(cin);
		}
	}
	namespace math
	{
		//n: number b: base
		double logBase(double n, double b)
		{
			return (log(n) / log(b));
		}
	}
	namespace output
	{
		class OutputBuffer
		{
		public:
			//default constructor
			OutputBuffer()
			{
				this->bufHeight = 0;
				this->bufWidth = 0;
				this->outBuffer.clear();
			}
			//construct based on height and width and have a blank buffer
			OutputBuffer(unsigned short _width, unsigned short _height)
			{
				this->bufHeight = _height;
				this->bufWidth = _width;
				outBuffer.clear();
			}
			//construct with width and heigt and fill buffer with a certain character
			OutputBuffer(unsigned short _width, unsigned short _height, char fillCh)
			{
				this->bufHeight = _height;
				this->bufWidth = _width;
				outBuffer.clear();
				for (unsigned short s = 0; s < this->bufHeight; s++)
					outBuffer.push_back(string(this->bufWidth, fillCh));
			}
			unsigned short getWidth()
			{
				return this->bufWidth;
			}
			unsigned short getHeight()
			{
				return this->bufHeight;
			}
			void setWidth(unsigned short newWidth)
			{
				this->bufWidth = newWidth;
			}
			void setHeight(unsigned short newHeight)
			{
				this->bufHeight = newHeight;
			}
			void writeToBuffer(unsigned short x, unsigned short y, char c)
			{
				if (x >= this->bufWidth)
					cout << "error: writing to buffer at invalid index: (" << x << ", " << y << ")" << endl;
				else if (y >= this->bufHeight)
					cout << "error: writing to buffer at invalid index: (" << x << ", " << y << ")" << endl;
				else
					this->outBuffer.at(y).at(x) = c;
			}
			void display()
			{
				for (string ln : this->outBuffer)
					cout << ln << endl;
			}
		private:
			unsigned short bufWidth, bufHeight;
			vector<string> outBuffer;
		};
	}
	namespace stringprocessor
	{
		vector<string> getTokens(string inputString, char delimiter)
		{
			vector<string> tokens;
			stringstream ss(inputString);
			string buf;
			while (getline(ss, buf, delimiter))
			{
				tokens.push_back(buf);
			}
			return tokens;
		}
		string shared(vector<string> v)
		{
			string ret = "";
			unordered_map<char, bool> presentMap;
			//start out with every single character in the vector being true
			for (string s : v)
				for (char t : s)
					presentMap[t] = true;
			cout << "\t*********" << endl;
			//loop each set key (will only be the ones present in the vector)
			for (auto it : presentMap)
			{
				for (string s : v)
					if (s.find(it.first) == string::npos)
						it.second = false;
				cout << "\t" << it.first << "\t" << it.second << endl;
				if (it.second == true)
					ret.push_back(it.first);
			}
			cout << "\t*********" << endl;
			return ret;
		}
		string sharedLetters(string in)
		{
			vector<string> tok = getTokens(in, ' ');
			return shared(tok);
		}
		string removeChar(string base, char rem)
		{
			string baseprime = base;
			baseprime.erase(remove(baseprime.begin(), baseprime.end(), rem), baseprime.end());
			return baseprime;
		}
		//actually eye cancer
		string removeNthOccurence(unsigned short n, string s)
		{
			string sprime = s;
			unsigned int index = 0;
			while (index < sprime.size())
			{
				sprime.at(index) = -1;
				index += (n);
			}
			return removeChar(sprime, (char)-1);
		}
		vector<string> removeAboveThreshold(vector<string> data, unsigned short threshhold)
		{
			unordered_map<char, unsigned short> countMap;
			for (string str : data)
				for (char c : str)
					countMap[c]++;
			vector<string> ret = data;
			for (string &str : ret)
				for (auto it : countMap)
					if (it.second > threshhold)
						str.erase(remove(str.begin(), str.end(), it.first), str.end());
			return ret;
		}
		string removeAboveThreshold(string data, unsigned int threshold)
		{
			vector<string> t = { data };
			return removeAboveThreshold(t, threshold).at(0);
		}
	}
	namespace dataprocessor
	{
		template<typename T>
		T min(vector<T> v, T max)
		{
			T m = max;
			for (T t : v)
				if (t < m)
					m = t;
			return m;
		}
		template<typename T>
		T max(vector<T> v, T min)
		{
			T m = min;
			for (T t : v)
				if (t > m)
					m = t;
			return m;
		}
		template<typename T>
		class BinarySearchTree
		{
		public:
			struct Node
			{
				Node(T _v)
				{
					val = _v;
					less = nullptr;
					more = nullptr;
				}
				T val;
				Node* less;
				Node* more;
			};
			BinarySearchTree()
			{
				this->root = nullptr;
				this->nodeTree.clear();
			}
			BinarySearchTree(T _root)
			{
				this->root = new Node(_root);
				this->nodeTree.clear();
				this->nodeTree.push_back(this->root);
			}
			void insert(T val)
			{
				nodeTree.push_back(new Node(val));
				//ignore parameter from here
				T v = nodeTree.back()->val;
				Node* parent = this->root;
				while (parent != nullptr)
				{
					//is the less node not set and less than the parent
					if (parent->less == nullptr && v < parent->val)
					{
						parent->less = nodeTree.back();
						break;
					}
					else if (parent->more == nullptr && v >= parent->val)
					{
						parent->more = nodeTree.back();
						break;
					}
					else if (parent->val < parent->val)
					{
						parent = parent->less;
					}
					else
					{
						parent = parent->more;
					}
				}
			}
			T getMin()
			{
				Node* parent = this->root;
				while (parent->less != nullptr)
					parent = parent->less;
				return parent->val;
			}
			T getMax()
			{
				Node* parent = this->root;
				while (parent->more != nullptr)
					parent = parent->more;
				return parent->val;
			}
		private:
			Node* root;
			//container for all of our nodes, doesn't need to be sorted
			vector<Node*> nodeTree;
		};
	}
}