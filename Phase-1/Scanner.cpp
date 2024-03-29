/*
Group Members :

Shetty Karthik Ravindra - 2018A7PS0141H
Koustubh Sharma - 2018A7PS0114H
Rishabh Baid - 2018A7PS0189H
Abhirath Singh Parmar - 2018A7PS0521H

*/

#include <bits/stdc++.h>
#define keyRange 1
#define opRange 50
#define delRange 100
using namespace std;

int token_no = 1;
int line_no = 0;
set<string> keyWords, operators, delimiters;

//set containing keywords
void putKeys()
{
    keyWords.insert("int");
    keyWords.insert("float");
    keyWords.insert("break");
    keyWords.insert("long");
    keyWords.insert("char");
    keyWords.insert("for");
    keyWords.insert("if");
    keyWords.insert("switch");
    keyWords.insert("else");
    keyWords.insert("while");
    keyWords.insert("goto");
    keyWords.insert("continue");
    keyWords.insert("return");
    keyWords.insert("auto");
    keyWords.insert("double");
    keyWords.insert("boolean");
    keyWords.insert("string");
    keyWords.insert("default");
    keyWords.insert("do");
    keyWords.insert("void");
    keyWords.insert("main");
    keyWords.insert("case");
    keyWords.insert("true");
    keyWords.insert("false");

    //Note : whitespace after using below two keywords in the language are mandatory
    keyWords.insert("printf");
    keyWords.insert("scanf");
}

//set containing operators
void putOperators()
{
    operators.insert("+");
    operators.insert("-");
    operators.insert("*");
    operators.insert("/");
    operators.insert("%");
    operators.insert("!");
    operators.insert("?");
    operators.insert(":");
    operators.insert(">");
    operators.insert("<");
    operators.insert(":=");
    operators.insert("==");
    operators.insert(">=");
    operators.insert("<=");
    operators.insert("&");
    operators.insert("|");
    operators.insert("^");
    operators.insert("||");
    operators.insert("&&");
    operators.insert("||");
    operators.insert("=");
    operators.insert("!=");
    operators.insert("&=");
    operators.insert("|=");
    operators.insert("-=");
    operators.insert("+=");
    operators.insert("*=");
    operators.insert("/=");
}

//set containing delimeters
void putDelimiters()
{
    delimiters.insert("{");
    delimiters.insert("}");
    delimiters.insert("(");
    delimiters.insert(")");
    delimiters.insert("[");
    delimiters.insert("]");
    delimiters.insert(";");
    delimiters.insert(",");
}

//function to check whether a character is operator or delimiter
int checkOpDel(char ch)
{
    for (auto x : operators)
    {
        if (x[0] == ch)
            return 1;
    }

    for (auto x : delimiters)
    {
        if (x[0] == ch)
            return 2;
    }

    return 0;
}

//global variable to keep track of the token sent to dfa
string temp;

//dfa
void dfa(string token)
{
    //return if token string is empty
    if (token.length() == 0)
        return;

    temp = token;

    //if the token string is a pre-defined keyword
    for (auto itr = keyWords.begin(); itr != keyWords.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token " << keyRange + distance(keyWords.begin(), itr) << ", "
                 << "keyword " << token << ", "
                 << "line number " << line_no << endl;
            return;
        }
    }

    //if the token string is a pre-defined operator
    for (auto itr = operators.begin(); itr != operators.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token " << opRange + distance(operators.begin(), itr) << ", "
                 << "operator " << token << ", "
                 << "line number " << line_no << endl;
            return;
        }
    }

    //if the token string is a pre-defined delimiter
    for (auto itr = delimiters.begin(); itr != delimiters.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token " << opRange + distance(delimiters.begin(), itr) << ", "
                 << "delimiter " << token << ", "
                 << "line number " << line_no << endl;
            return;
        }
    }

    //DFA for all other cases
    int state = 1;
    char ch;

    for (int i = 0; i < token.length(); i++)
    {
        ch = token[i];

        switch (state)
        {
        case 1:
            if (isalpha(ch))
                state = 2;
            else if (ch == '+' || ch == '-')
                state = 3;
            else if (isdigit(ch) && ch != '0')
                state = 4;
            else if (ch == '0')
                state = 5;
            else if (ch == '"')
                state = 6;
            else
                state = 10;
            break;
        case 2:
            if (isalpha(ch) || isdigit(ch) || ch == '_')
                state = 2;
            else
                state = 10;
            break;
        case 3:
            if (isdigit(ch) && ch != '0')
                state = 4;
            else if (ch == '0')
                state = 11;
            else
                state = 10;
            break;
        case 4:
            if (isdigit(ch))
                state = 4;
            else if (ch == '.')
                state = 7;
            else
                state = 10;
            break;
        case 5:
            if (ch == '.')
                state = 7;
            else
                state = 10;
            break;
        case 6:
            if (ch != '"')
                state = 6;
            else
                state = 9;
            break;
        case 7:
            if (isdigit(ch))
                state = 8;
            else
                state = 10;
            break;
        case 8:
            if (isdigit(ch))
                state = 8;
            else
                state = 10;
            break;
        case 9:
            state = 9;
            break;
        case 10:
            break;
        case 11:
            if (ch == '.')
                state = 7;
            else
                state = 10;
        }
    }

    //check final state and print result
    switch (state)
    {
    case 2:
        // Identifiers
        cout << "Token 150, "
             << "identifier " << token << ", "
             << "line number " << line_no << endl;
        break;
    case 4:
        //Integer literals except 0
        cout << "Token 151, "
             << "Integer " << token << ", "
             << "line number " << line_no << endl;
        break;
    case 5:
        // Specifically for integer literal 0
        cout << "Token 152, "
             << "Integer " << token << ", "
             << "line number " << line_no << endl;
        break;
    case 8:
        // Float literals
        cout << "Token 153, "
             << "Float " << token << ", "
             << "line number " << line_no << endl;
        break;
        //string literals
    case 9:
        cout << "Token 154, "
             << "String " << token << ", "
             << "line number " << line_no << endl;
        break;
    default:
        //invalid tokens
        cout << "Token 404, "
             << "invalid " << token << ", "
             << "line number " << line_no << "........" << endl;
        break;
    }
}

//seperates tokens by operators and delimeters and passes it to dfa for final output
void tokenizer(string token)
{
    int flag = 0, curr;
    string buffer;
    char ch;

    for (int i = 0; i < token.length(); i++)
    {
        int curr = checkOpDel(token[i]);

        if (flag == 1)
        {
            if (token[i] == '=' or token[i] == '&' or token[i] == '|')
            {
                buffer += token[i];
                flag = 2;
            }
            else if (token[i - 1] == '-' or token[i - 1] == '+' and isdigit(token[i]) and token[i] != '0')
            {
                flag = 2;
                int cntDot = 0;

                while (i < token.length() and (isdigit(token[i]) or token[i] == '.'))
                {
                    buffer += token[i++];
                    if (token[i] == '.')
                        cntDot++;
                }

                i--;

                if (operators.find(temp) == operators.end())
                {
                    reverse(buffer.begin(), buffer.end());
                    string op;
                    op += buffer.back();
                    dfa(op);
                    buffer.pop_back();
                    reverse(buffer.begin(), buffer.end());
                }

                if (cntDot > 1)
                {
                    cout << "Token 404, "
                         << "invalid " << buffer << ", "
                         << "line number " << line_no << "........" << endl;
                    buffer = "";
                }
            }

            dfa(buffer);
            buffer = "";

            if (flag != 2)
                buffer += token[i];

            flag = 0;
            continue;
        }

        if (curr == 0)
            buffer += token[i];
        else if (curr == 1)
        {
            flag = 1;
            dfa(buffer);
            buffer = "";
            buffer += token[i];
        }
        else if (curr == 2)
        {
            dfa(buffer);
            buffer = "";
            buffer += token[i];
            dfa(buffer);
            buffer = "";
        }
    }

    if (buffer.length())
        dfa(buffer);

    temp = token;
}

//Scanner, which is repeatedly called by parser for each line
//Scanner eliminates whitepaces, new lines, tab spaces and sends it to tokenizer function
//in case of string literals, it is directly sent to dfa for final output
void Scanner(string line)
{
    int k = 0, flag = 0;
    string buffer;
    bool stringLiteral = false;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '"' and !stringLiteral)
        {
            tokenizer(buffer);
            buffer = "";
            stringLiteral = true;
            buffer += line[i];
            continue;
        }

        if (stringLiteral)
        {
            buffer += line[i];

            if (line[i] == '"')
            {
                dfa(buffer);
                buffer = "";
                stringLiteral = false;
            }

            continue;
        }

        if (flag == 0)
        {
            if (line[i] == '/' and i + 1 < line.length() and line[i + 1] == '*')
            {
                flag = 1;
                i++;
            }
            else if (line[i] == '/' and i + 1 < line.length() and line[i + 1] == '/')
            {
                flag = 2;
                i++;
            }
            else if (line[i] == ' ' or line[i] == '\n' or line[i] == '\t')
            {
                if (k == 0)
                    continue;

                if (buffer.length() >= 1 and (buffer.back() == '+' or buffer.back() == '-'))
                    continue;

                tokenizer(buffer);
                buffer = "";
                k = 0;
            }
            else
            {
                if (line[i] != ' ' and line[i] != '\n' and line[i] != '\t')
                {
                    buffer += line[i];
                    k++;
                }
            }
        }
        else if (flag == 1)
        {
            if (line[i] == '*' and i + 1 < line.length() and line[i + 1] == '/')
            {
                flag = 0;
                i++;
            }
        }
        else if (flag == 2)
        {
            if (line[i] == '\n')
                flag = 0;
        }
    }

    if (buffer.length() != 0)
    {
        if (stringLiteral)
            dfa(buffer);
        else
            tokenizer(buffer);
    }
}

//driver code : parser
int main()
{
    putKeys();
    putOperators();
    putDelimiters();
    string filename;
    cin >> filename;

    fstream file;
    file.open(filename, ios::in);

    //uncomment below line to print output to a file;
    //freopen("output.txt", "w", stdout);

    if (file)
    {
        string line;
        while (getline(file, line))
        {
            line_no++;
            Scanner(line);
        }

        file.close();
    }
    else
    {
        cout << "File cannot be opened !" << endl;
    }

    return 0;
}
