#pragma once
/*
Everything breaks when including winapi headers lol
So this is really just an extension of stl
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <functional>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <chrono>

using namespace std;

#define PATHFIND_NORMAL (1 << 0)
#define PATHFIND_DIAGONAL (1 << 1)

string operator*(string left, int right)
{
	string ret = "";
	for (int i = 0; i < right; i++)
		ret += left;
	return ret;
}

//named the namespace the wrong thing because i was thinking of something else, so I guess it stands for "copy-paste helper"
namespace CPHelper
{
	namespace bitwise
	{
		template<typename T>
		bool testBit(T data, unsigned short pos)
		{
			return (data) & (1 << pos);
		}
		template<typename T>
		unsigned short numBits()
		{
			return sizeof(T) * 8;
		}
		template<typename T>
		string rawData(T data)
		{
			string b(numBits<T>(), '0');
			const unsigned int uFlag = 1;
			for (unsigned short l = 0; l < numBits<T>(); l++)
			{
				b.at(numBits<T>() - l - 1) = (testBit<T>(data, l)) ? '1' : '0';
			}
			return b;
		}
		unsigned short estimateBits(unsigned long value)
		{
			//log base 2 value
			return (unsigned short)floorl((log(value) / log(2)));
		}
	}
	namespace stringprocessor
	{
		vector<string> getTokens(string, char);
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
		class Element
		{
		public:
			Element(string data)
			{
				this->data = data;
			}
			~Element()
			{
				this->data.clear();
			}
			long getLong()
			{
				return atol(this->data.c_str());
			}
			long long getLongLong()
			{
				return atoll(this->data.c_str());
			}
			int getInt()
			{
				return atoi(this->data.c_str());
			}
			float getFloat()
			{
				return atof(this->data.c_str());
			}
			string getString()
			{
				return this->data;
			}
		private:
			string data;
		};
		class Line
		{
		public:
			Line(vector<Element*> elements)
			{
				this->elements = elements;
			}
			~Line()
			{
				this->elements.clear();
			}
			Element* getElement(unsigned int loc)
			{
				return this->elements.at(loc);
			}
			string getData()
			{
				string rebuilt = "";
				for (auto e : this->elements)
					rebuilt += e->getString() + " ";
				//remove the last space in the rebuilt string
				rebuilt.pop_back();
				return rebuilt;
			}
			unsigned int numElements()
			{
				return this->elements.size();
			}
		private:
			vector<Element*> elements;
		};
		class Input
		{
		public:
			Input()
			{
				this->lines.clear();
			}
			~Input()
			{
				this->lines.clear();
			}
			Line* getLine(unsigned short loc)
			{
				return this->lines.at(loc);
			}
			void getInput(string terminator, istream &stream = cin)
			{
				auto in = CPHelper::input::getInput(stream, terminator);
				this->set(in);
			}
			void getInput(unsigned int numLines, istream &stream = cin)
			{
				vector<string> in;
				for (unsigned int i = 0; i < numLines; i++)
					in.push_back(CPHelper::input::getSingleLine());
				this->set(in);
			}
			unsigned int numLines()
			{
				return this->lines.size();
			}
		private:
			void set(vector<string> in)
			{
				vector<Line*> lns;
				for (string s : in)
				{
					vector<string> tok = CPHelper::stringprocessor::getTokens(s, ' ');
					vector<Element*> elem;
					for (string t : tok)
						elem.push_back(new Element(t));
					lns.push_back(new Line(elem));
				}
				this->lines = lns;
			}
			vector<Line*> lines;
		};
		unsigned int getFileLines(string inFile)
		{
			ifstream i(inFile);
			string tmp;
			unsigned int counter = 0;
			while (getline(i, tmp))
				counter++;
			return counter;
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
		float avg(vector<T> v)
		{
			float sum = 0.f;
			for (T t : v)
				sum += (float)t;
			return sum / v.size();
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
			Node * root;
			//container for all of our nodes, doesn't need to be sorted
			vector<Node*> nodeTree;
		};
		template<typename T, typename V>
		void setUnorderedMapDefault(unordered_map<T, V> &m, vector<T> initializers, V def)
		{
			for (T t : initializers)
				m[t] = def;
		}
		template<typename T, typename V>
		void setMapDefault(map<T, V> &map, vector<T> initializers, V def)
		{
			for (T t : initializers)
				m[t] = def;
		}
		template<typename T>
		T listSum(vector<T> list)
		{
			T sum = NULL;
			for (T t : list)
				sum += t;
			return sum;
		}
		//push the contents of list1 to list 0
		template<typename T>
		void mergeList(vector<T> &list0, vector<T> list1)
		{
			for (T t : list1)
				list0.push_back(t);
		}
		template<typename T>
		vector<T> splitList(vector<T> &list)
		{
			unsigned int middle = (list.size() / 2) - 1;
			vector<T> ret = list;
			//remove the indices from the parameter
			list.erase(middle, list.size());
			ret.erase(0, middle);
			return ret;
		}
		template<typename T>
		T cap(T in, T tmax)
		{
			if (in > tmax)
				return tmax;
			return in;
		}
		template <typename T>
		vector<T> slice(vector<T> vec, int start, int end) 
		{
			auto first = vec.begin() + start;
			auto last = vec.begin() + end;
			vector<T> newVec(first, last);
			return newVec;
		}
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
		//use to remove multiple different chars at once
		string removeChars(string base, string rem)
		{
			string ret = base;
			for (char c : rem)
			{
				ret.erase(remove(ret.begin(), ret.end(), c), ret.end());
			}
			return ret;
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
		string escapeHexCode(string hexVal)
		{
			string ret;
			for (int i = 0; i< hexVal.length(); i += 2)
			{
				string byte = hexVal.substr(i, 2);
				char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
				ret.push_back(chr);
			}
			return ret;
		}
		string escapeBinary(string binVal)
		{
			stringstream ss(binVal);
			string ret;
			while (ss.good())
			{
				bitset<8> bits;
				ss >> bits;
				char c = char(bits.to_ulong());
				ret.push_back(c);
			}
			return ret;
		}
		string escapeDecimal(string decVal)
		{
			string ret;
			ret.push_back((char)atoi(decVal.c_str()));
			return ret;
		}
		string escapeOctal(string octVal)
		{
			string ret;
			ret.push_back((char)stoi(octVal.c_str(), 0, 8));
			return ret;
		}
		string toHex(char c)
		{
			char buf[128];
			sprintf(buf, "%X", c);
			string ret = buf;
			return ret;
		}
		string toBinary(char c)
		{
			return CPHelper::bitwise::rawData<char>(c);
		}
		string toOctal(char c)
		{
			int rem, i = 1, o = 0;
			while (c != 0)
			{
				rem = c % 8;
				c /= 8;
				o += rem * i;
				i *= 10;
			}
			return to_string(o);
		}
		bool containsChar(string base, string cmp)
		{
			for (char c : cmp)
				if (base.find(c) != string::npos)
					return true;
			return false;
		}
		bool containsChar(string base, vector<char> cmp)
		{
			string cmpStr;
			cmpStr.clear();
			for (char c : cmp)
				cmpStr.push_back(c);
			return containsChar(base, cmpStr);
		}
		bool containsChar(string base, char ch)
		{
			return base.find(ch) != string::npos;
		}
		void generateOccuranceMap(string base, unordered_map<char, unsigned int> &umap)
		{
			//make sure map is already clear
			umap.clear();
			//convert string to char array
			vector<char> chList;
			for (char c : base)
				chList.push_back(c);
			//set all values we need to 0
			CPHelper::dataprocessor::setUnorderedMapDefault<char, unsigned int>(umap, chList, 0);
			//set occurances
			for (char c : base)
				umap[c]++;
		}
		class Dictionary
		{
		public:
			Dictionary()
			{
				translationMap.clear();
			}
			Dictionary(vector<char> base, vector<string> translation)
			{
				for (unsigned int i = 0; i < base.size(); i++)
					this->translationMap[base.at(i)] = translation.at(i);
			}
			void dumpDictionary()
			{
				for (auto it : this->translationMap)
				{
					cout << "\t" << it.first << "\t" << it.second << endl;
				}
			}
			string translate(string str)
			{
				string ret = "";
				for (char c : str)
					ret += this->translationMap[c];
				return ret;
			}
		private:
			unordered_map<char, string> translationMap;
			string alphabet = "abcdefghijklmnopqrstuvwxyz";
		};
		vector<int> translateToInt(vector<string> tok)
		{
			vector<int> ret;
			for (string s : tok)
			{
				ret.push_back(atoi(s.c_str()));
			}
			return ret;
		}
		vector<int> translateToInt(string str)
		{
			return translateToInt(getTokens(str, ' '));
		}
		vector<float> translateToFloat(vector<string> tok)
		{
			vector<float> ret;
			for (string s : tok)
			{
				ret.push_back((float)atof(s.c_str()));
			}
			return ret;
		}
		vector<float> translateToFloat(string str)
		{
			return translateToFloat(getTokens(str, ' '));
		}
		string reverseString(string in)
		{
			string t = in;
			reverse(t.begin(), t.end());
			return t;
		}
		template<typename T>
		string toString(T val)
		{
			return to_string(val);
		}
		template<typename T>
		vector<string> toString(vector<T> vals)
		{
			vector<string> ret;
			for (T t : vals)
				ret.push_back(to_string(t));
			return ret;
		}
		string toUppercase(string in)
		{
			string ret = in;
			for (unsigned int i = 0; i < ret.size(); i++)
				ret.at(i) = toupper(ret.at((int)i));
			return ret;
		}
		string toLowercase(string in)
		{
			string ret = in;
			for (unsigned int i = 0; i < ret.size(); i++)
				ret.at(i) = tolower(ret.at((int)i));
			return ret;
		}
		string narrowString(wstring win)
		{
			string ret = "";
			for (wchar_t wc : win)
			{
				unsigned int castVal = (unsigned int)wc;
				ret.push_back((char)CPHelper::dataprocessor::cap<unsigned int>(wc, CHAR_MAX));
			}
			return ret;
		}
		string append(string base, string end)
		{
			return base + end;
		}
		string prepend(string base, string start)
		{
			return start + base;
		}
	}
	namespace math
	{
		//n: number b: base
		double logBase(double n, double b)
		{
			return (log(n) / log(b));
		}
		const double PI = 3.1415926535897932384626433832795028;
		const double E = 2.71828182845904523536028747135266249;
		template<typename T>
		vector<T> invert(vector<T> v)
		{
			vector<T> ret;
			for (T t : v)
			{
				ret.push_back(-t);
			}
			return t;
		}
		//returns the vector with the largest dimension, with sum of elements at each of the lower indecies
		template<typename T>
		vector<T> sum(vector<T> l, vector<T> r)
		{
			vector<T> ret;
			bool modLeft = l.size() > r.size();
			if (modLeft)
			{
				ret = l;
				for (unsigned int i = 0; i < r.size(); i++)
					ret.at(i) += r.at(i);
			}
			else
			{
				ret = r;
				for (unsigned int i = 0; i < l.size(); i++)
					ret.at(i) += l.at(i);
			}
			return ret;
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
				this->lockBuffer.clear();
			}
			//construct based on height and width and have a blank buffer
			OutputBuffer(unsigned short _width, unsigned short _height)
			{
				this->bufHeight = _height;
				this->bufWidth = _width;
				outBuffer.clear();
				this->lockBuffer.clear();
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
				else if (CPHelper::stringprocessor::containsChar(this->lockBuffer, this->outBuffer.at(y).at(x)))
					cout << "error: cannot write to locked character: " << "(" << x << ", " << y << ")" << " character: " << this->outBuffer.at(y).at(x) << endl;
				else
					this->outBuffer.at(y).at(x) = c;
			}
			char readBuffer(unsigned short x, unsigned short y)
			{
				return this->outBuffer.at(y).at(x);
			}
			void display()
			{
				for (string ln : this->outBuffer)
					cout << ln << endl;
			}
			bool writable(unsigned int x0, unsigned int y0)
			{
				return CPHelper::stringprocessor::containsChar(this->lockBuffer, this->outBuffer.at(y0).at(x0));
			}
			bool writable(unsigned int x0, unsigned int y0, char check)
			{
				return this->outBuffer.at(y0).at(x0) == check;
			}
			//set unwritable character
			void lock(char chLock)
			{
				for (char c : this->lockBuffer)
					if (c == chLock)
						return;
				this->lockBuffer.push_back(chLock);
			}
			//set writable character (has to be locked)
			void unlock(char chLock)
			{
				lockBuffer = CPHelper::stringprocessor::removeChar(lockBuffer, chLock);
			}
		private:
			unsigned short bufWidth, bufHeight;
			vector<string> outBuffer;
			string lockBuffer;
		};
		void Bododo()
		{
			cout << "\a";
		}
		template<typename T>
		void printVector(vector<T> vec)
		{
			for (T t : vec)
				cout << t << endl;
		}
		void pause(string msg = "")
		{
			cout << msg << endl;
			//wait for input
			while (!_kbhit()) {};
			//clear buffer
			_getch();
		}
	}
	namespace pathfinding
	{
		struct Node
		{
			Node* parent;
			int x, y;
			float g, h, f;


			bool operator==(const Node& right)
			{
				return x == right.x && y == right.y;
			}

			Node(Node* p, int _x, int _y, float _g, float _h, float _f)
			{
				parent = p;
				x = _x;
				y = _y;
				g = _g;
				h = _h;
				f = _f;
			}

			Node() {};
		};

		bool isInVector(int x, int y, vector<Node> list)
		{
			for (Node n : list)
				if (n.x == x && n.y == y)
					return true;
			return false;
		}

		Node getBestNode(priority_queue<Node, vector<Node>, greater<Node>>& queue, vector<Node> closed)
		{
			bool valid = false;
			Node cBest;
			while (valid == false)
			{
				cBest = queue.top();
				if (isInVector(cBest.x, cBest.y, closed) == false)
					valid = true;
				else
					queue.pop(); //remove the top node, we do this to the queue list, because this means less computation in future
			}
			return cBest;
		}

		enum HEURISTIC : unsigned int
		{
			MANHATTAN = 0,
			EUCLIDEAN,
			DIAGONAL
		};

		float dist(int x0, int y0, int x1, int y1, HEURISTIC h = HEURISTIC::EUCLIDEAN)
		{
			float dist;
			switch (h)
			{
				case HEURISTIC::EUCLIDEAN: dist = (float)sqrt(pow(fabs(x0 - x1), 2) + pow(fabs(y0 - y1), 2)); break;
				case HEURISTIC::MANHATTAN: dist = (float)fabs(x0 - x1) + (float)fabs(y0 - y1);
			}
			//1 + (1/p); p is the predicted maximum path length (if it is to low the results may be innacurate)
			//dist *= (1.f + (1 / 1000));
			return dist;
		}

		int nodeExists(Node n, vector<Node> list)
		{
			for (unsigned int i = 0; i < list.size(); i++)
			{
				Node tmp = list.at(i);
				if (tmp.x == n.x && tmp.y == n.y)
					return i;
			}
			return -1;
		}

		class Field
		{
		public:
			Field(vector<string> field)
			{
				this->data = field;
			}

			bool canMove(Node n, string movable)
			{
				return (n.x >= 0 && n.y >= 0 && n.x < this->data.at(0).size() && n.y < this->data.size() && CPHelper::stringprocessor::containsChar(movable, this->data.at(n.y).at(n.x)));
			}

			void display(Node n, Node start, Node end, char chStart, char chEnd)
			{
				vector<string> tmpData = this->data;
				Node tmpNode = n;
				tmpData.at(tmpNode.y).at(tmpNode.x) = '*';
				do
				{
					tmpNode = *tmpNode.parent;
					tmpData.at(tmpNode.y).at(tmpNode.x) = '*';
				} while (tmpNode.parent != nullptr);

				tmpData.at(start.y).at(start.x) = chStart;
				tmpData.at(end.y).at(end.x) = chEnd;

				for (string ln : tmpData)
					cout << ln << endl;
			}

			vector<Node> getBarriers(string movable)
			{
				vector<Node> vRet;
				for (unsigned int h = 0; h < this->data.size(); h++)
				{
					string ln = this->data[h];
					for (unsigned int w = 0; w < this->data.size(); w++)
					{
						char c = ln[w];
						if (!CPHelper::stringprocessor::containsChar(movable, c))
						{
							Node tmp;
							tmp.x = w;
							tmp.y = h;
							vRet.push_back(tmp);
						}
					}
				}
				return vRet;
			}

			void setBarrier(int x, int y, char bar)
			{
				this->data.at(y).at(x) = bar;
			}

			void removeBarrier(int x, int y, char bar)
			{
				this->data.at(y).at(x) = bar;
			}

			void reset(char chReset)
			{
				for (string& str : this->data)
					str = string(str.size(), chReset);
			}
		private:
			vector<string> data;
		};

		vector<Node> getSuccessors(Node* n, Node end, Field* field, string movable, unsigned int flags)
		{
			bool useDiagonal = flags & PATHFIND_DIAGONAL;
			bool useNormal = flags & PATHFIND_NORMAL;
			vector<Node> vecRet;
			Node x;
			if (useNormal)
			{
				x = { n, n->x + 1, n->y, n->g + 1, dist(n->x + 1, n->y, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x + 1, n->y, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x - 1, n->y, n->g + 1, dist(n->x - 1, n->y, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x - 1, n->y, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x, n->y + 1, n->g + 1, dist(n->x, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x, n->y - 1, n->g + 1, dist(n->x, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
			}
			if (useDiagonal)
			{
				x = { n, n->x + 1, n->y + 1, n->g + 1, dist(n->x + 1, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x + 1, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x - 1, n->y - 1, n->g + 1, dist(n->x - 1, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x - 1, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x - 1, n->y + 1, n->g + 1, dist(n->x - 1, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x - 1, n->y + 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
				x = { n, n->x + 1, n->y - 1, n->g + 1, dist(n->x + 1, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN), (n->g + 1) + dist(n->x + 1, n->y - 1, end.x, end.y, (flags & PATHFIND_DIAGONAL) ? HEURISTIC::EUCLIDEAN : HEURISTIC::MANHATTAN) };
				if (field->canMove(x, movable))
					vecRet.push_back(x);
			}

			return vecRet;
		}
		template <class T, class S, class C>
		S& container(priority_queue<T, S, C>& q)
		{
			struct HackedQueue : private priority_queue<T, S, C>
			{
				static S& container(priority_queue<T, S, C>& q)
				{
					return q.*&HackedQueue::c;
				}
			};
			return HackedQueue::container(q);
		}

		template <class T, class S, class C>
		void rep(priority_queue<T, S, C>& q, vector<T> v)
		{
			struct HackedQueue : private priority_queue<T, S, C>
			{
				static void rep(priority_queue<T, S, C>& q, vector<T> v)
				{
					q.*&HackedQueue::c = v;
				}
			};
			HackedQueue::rep(q, v);
		}
		bool operator<(const Node left, const Node right)
		{
			return left.f < right.f;
		}

		bool operator>(const Node left, const Node right)
		{
			return left.f > right.f;
		}
		//solve a path using the A* algorithm
		//parameters: start, end, field that the algorithm uses, characters that can be moved to, moveset
		vector<Node> aStar(Node start, Node end, Field* field, string movable, unsigned int flags)
		{
			priority_queue<Node, vector<Node>, greater<Node>> open;
			vector<Node> closed;

			open.push(start);
			vector<Node*> parents;

			while (open.empty() == false)
			{
				//the current node which is the node with the least f value in the open list
				Node q = getBestNode(open, closed);
				//cout << "q: " << "(" << q.x << ", " << q.y << ")" << endl;
				//add q to a list of parent nodes, to make sure we don't lose the parent node
				Node* parent = new Node(q.parent, q.x, q.y, q.g, q.h, q.f);
				//now we need to get the successors (assume that this works for now)
				parents.push_back(parent);
				vector<Node> successors = getSuccessors(parents.back(), end, field, movable, flags);
				//cout << q.x << "," << q.y << endl;
				//check what successor we should use
				for (Node s : successors)
				{
					//is the successor the end node
					//cout << s.x << "," << s.y << endl;
					if (s == end)
					{
						closed.push_back(s);
					
						Node tmpNode = closed.back();

						vector<Node> ret;
						ret.push_back(tmpNode);
						do
						{
							tmpNode = *tmpNode.parent;
							ret.push_back(tmpNode);
						} while (tmpNode.parent != nullptr);
						return ret;
					}
					else if (field->canMove(s, movable))
					{
						int index;
						bool replaced = false;
						vector<Node> cont = container(open);
						//if the node exists in the open list
						if ((index = nodeExists(s, cont)) != -1)
						{
							//if the successor has a lower f value than the one that already exists
							if (s.f < cont[index].f)
							{
								//replace the item in the open list
								cont[index] = s;
								//open = { cont };
								rep(open, cont);
								replaced = true;
							}
						}
						//if we found this node in the closed list
						if ((index = nodeExists(s, closed)) != -1)
						{
							//if the found node has a lower f value than the one that already exists
							if (s.f < closed[index].f)
							{
								//replace the node with our successor
								closed[index] = s;
								replaced = true;
							}
						}
						//add the successor to the open list
						if (replaced == false)
							open.push(s);
					}
				}

				//add q to the closed list
				//check for size because of the end node being weird
				if (open.size() != 0)
					closed.push_back(q);
			}
			return vector<Node>();
		}
	}
	namespace time
	{
		using namespace chrono;
		milliseconds recordedTime;
		milliseconds timeSinceEpoch()
		{
			return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		}
		unsigned long long getTimeDifference(milliseconds m0, milliseconds m1)
		{
			return duration_cast<milliseconds>(m0 - m1).count();
		}
		void startRecording()
		{
			recordedTime = timeSinceEpoch();
		}
		unsigned long long stopRecording()
		{
			auto now = timeSinceEpoch();
			return getTimeDifference(now,recordedTime);
		}
	}
}