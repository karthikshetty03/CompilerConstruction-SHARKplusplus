#ifndef PARSER
#define PARSER
#include "parsetree.hpp"
#include "productionsave.hpp"
#include "Token.hpp"
#include <string>
#include <map>

map<string, int> nmtocol;
int flag = 0;
const int N = 1e3;
string movestuff[N][N];

class Parser
{
public:
	int errorcount = 0;
	string input;
	stack<int> STACKList;
	stack<string> SymStack;
	string col[N];
	map<string, bool> gotoornot;
	string colid[N];
	int prodn[N];

	string removesapces(string &lel)
	{
		string ret = "";

		for (int i = 0; i < lel.length(); i++)
		{
			if (lel[i] >= 'a' && lel[i] <= 'z')
			{
				ret += lel[i];
			}
			else if (lel[i] >= 'A' && lel[i] <= 'Z')
			{
				ret += lel[i];
			}
			else if (lel[i] >= '0' && lel[i] <= '9')
			{
				ret += lel[i];
			}
			else if (lel[i] >= 0 && lel[i] <= 127)
				ret += lel[i];
		}

		return ret;
	}

	std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream &str)
	{
		std::vector<std::string> result;
		std::string line;

		if (std::getline(str, line))
		{
			std::stringstream lineStream(line);
			std::string cell;

			while (std::getline(lineStream, cell, ','))
			{
				result.push_back(removesapces(cell));
			}
			if (!lineStream && cell.empty())
			{
				result.push_back("");
			}

			return result;
		}
		else
		{
			return result;
		}
	}

	// read grammar from csv file
	Parser(string toBeParsed)
	{
		input = toBeParsed;
		ifstream fin;
		fin.open("helpers/parsing-table.csv");

		if (!fin)
		{
			cout << "FNO" << endl;
		}

		auto ans = getNextLineAndSplitIntoTokens(fin);
		int k = 0;
		bool gorn = 0;
		for (auto x : ans)
		{
			if (x[0] == '\'')
			{
				x = string(x.begin() + 1, x.end() - 1);
			}
			nmtocol[x] = k - 1;
			gotoornot[x] = gorn;
			if (x[0] == '$')
				gorn = false;
			col[k++] = x;
		}

		int rowreadin = 1;

		while (true)
		{
			k = 0;
			int colreadin = 0;
			ans = getNextLineAndSplitIntoTokens(fin);

			if (ans.size() == 0)
			{
				break;
			}

			for (auto x : ans)
			{
				if (k == 0)
				{
					k++;
					prodn[rowreadin] = stoi(x) + 1;
				}
				else
				{
					movestuff[rowreadin][colreadin++] = x;
				}
			}
			rowreadin++;
		}

		startparsin(toBeParsed);
	}

	void startparsin(string &toBeParsed)
	{
		prods P;
		istringstream streamofinput(toBeParsed);
		int statestate = 0;
		string loookahead = "";
		STACKList.push(statestate);
		int parsedtill = -1;
		streamofinput >> loookahead;

		while (true)
		{
			int next = nmtocol[string(loookahead)];
			int toppostack = STACKList.top() + 1;
			if (gotoornot[string(loookahead)] == true)
			{
				STACKList.pop();
				if (movestuff[toppostack][next].size() == 0)
				{
					errormode();
					return;
				}
				STACKList.push(stoi(movestuff[toppostack][next]));
				continue;
			}

			cout << " State chosen : ";
			cout << loookahead << " " << toppostack << " " << next << endl;
			string next_move = movestuff[toppostack][next];
			next_move = removesapces(next_move);

			if (next_move == "" || next_move == " ")
			{
				cout << endl
						 << endl;
				if (errormode() == false)
				{
					cout << endl;
					cout << "The program has compilation errors." << endl;
					cout << endl;
					return;
				}
				cout << endl
						 << endl;
				continue;
			}

			if (next_move[0] == 'a')
			{
				cout << endl;
				if (flag == 0)
					cout << "The program compiled successfully !!" << endl;
				else
					cout << "The program has compilation errors." << endl;
				cout << endl;

				return;
			}

			if (next_move[0] == 's')
			{
				//Handle shift
				int num = stoi(string(next_move.begin() + 1, next_move.end()));
				STACKList.push(num);
				SymStack.push(loookahead);

				if (!(streamofinput >> loookahead))
				{
					break;
				}
			}
			else
			{
				int num = stoi(string(next_move.begin() + 1, next_move.end()));
				rule used_rule = P.rulenumber[num + 1];
				\
				P.printrule(used_rule);
				
				cout << endl
						 << endl;

				for (int i = 0; i < used_rule.ss.size(); i++)
				{
					if (SymStack.size() == 0)
						errormode();
					STACKList.pop();
					SymStack.pop();
				}
				auto newtop = STACKList.top() + 1;
				string next_move = movestuff[newtop][nmtocol[used_rule.ff]];

				if (next_move == "")
				{
					cout << endl
							 << endl;

					if (errormode() == false)
					{
						cout << endl;
						cout << "The program has compilation errors." << endl;
						cout << endl;
						return;
					}
					cout << endl
							 << endl;
					continue;
				}

				STACKList.push(stoi(movestuff[newtop][nmtocol[used_rule.ff]]));
				SymStack.push(used_rule.ff);
			}
		}
	}

	bool errormode()
	{
		errorcount++;
		cout << "---X--- Errors detected ---X---" << endl;
		flag = 1;

		// pop
		if (SymStack.size() == 0)
		{
			return false;
		}

		cout << "Moving ahead to continue parsing...." << endl;
		STACKList.pop();
		SymStack.pop();
		return true;
	}
};

#endif