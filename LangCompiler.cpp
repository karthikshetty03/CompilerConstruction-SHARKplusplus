using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cassert>

#define US unordered_set
#define ll long long
#define ss second
#define ff first
#define pb push_back

#include "helpers/Buffer.hpp"
#include "helpers/Table.hpp"
#include "helpers/DFA.hpp"
#include "helpers/Token.hpp"
#include "helpers/paser.hpp"
#include "helpers/Scanner.hpp"

string DATATYPE(string k, string s)
{
	if (k == "keyword")
	{
		if (s == "if")
			return "IF";
		if (s == "else")
			return "ELSE";
		if (s == "while")
			return "WHILE";
		if (s == "int" || s == "float" || s == "long" || s == "char" || s == "double")
			return "TYPE";
		if (s == "true")
			return "TRUE";
		if (s == "false")
			return "FALSE";
	}
	if (k == "identifier")
		return "ID";
	if (k == "comment")
		return "";
	if (k == "single")
	{
		if (s == "<" || s == ">" || s == "<=" || s == ">=" || s == "!=" || s == "==")
			return "REL_OPT";
		if (s == "||")
			return "OR";
		if (s == "&&")
			return "AND";
		if (s == "!")
			return "NOT";
		else
			return s;
	}

	if (k == "integer")
		return "DIGIT";
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cout << "Error! Please input sufficient arguments" << endl;
		return 1;
	}

	string fileName(argv[1]);
	Data tokens = Scanner::LangScanner(fileName);

	string fin = "";
	cout << endl;
	cout << "**************** Print token list ************************" << endl;
	cout << endl;

	for (int i = 0; i < tokens.tok.size(); ++i)
	{
		cout << "name: " << tokens.tok[i].m_name;
		cout << " value:" << tokens.tok[i].m_value;
		cout << " Line: " << tokens.tok[i].m_line;
		cout << " tok id: " << tokens.symbol_table[tokens.tok[i].m_value] << endl;
		fin += " " + DATATYPE(tokens.tok[i].m_name, tokens.tok[i].m_value) + " ";
	}

	cout << endl
			 << endl;
	cout << "******************* Print level-wise parsing *****************" << endl;
	cout << endl;

	fin += "$";
	Parser p(fin);

	if (!flag)
	{
		cout << endl
				 << endl;
		cout << "******************* Print Abstract Syntax Tree (AST) *****************" << endl;
		cout << endl;
		cout << fin << endl;
	}

	return 0;
}
