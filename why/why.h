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
		string sharedLetters(string in)
		{
			
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
}