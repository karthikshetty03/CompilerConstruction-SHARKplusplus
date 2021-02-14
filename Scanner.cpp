#include <bits/stdc++.h>
#define numKeywords 20
#define numOperators 18
#define numDelimiters 8
#define MaxTokenSize 100

#define keyRange 1
#define opRange 50
#define delRange 100
using namespace std;

int token_no = 1;
int line_no = 0;

set<string> keyWords, operators, delimiters;

void putKeys()
{
    keyWords.insert("int");
    keyWords.insert("float");
    keyWords.insert("long");
}

void putOperators()
{
    operators.insert("+");
    operators.insert("-");
    operators.insert("*");
    operators.insert("/");
}

void putDelimiters()
{
    delimiters.insert(";");
    delimiters.insert("(");
}

int checkOpDel(char ch)
{
    for (auto x : keyWords)
        if (x[0] == ch)
            return 1;

    for (auto x : operators)
        if (x[0] == ch)
            return 2;

    return 0;
}

int dfa(string token)
{
    if (token.length() == 0)
        return;

    for (auto itr = keyWords.begin(); itr != keyWords.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token" << keyRange + distance(keyWords.begin(), itr) << ","
                 << "keyword" << token << ","
                 << "line number " << line_no << endl;
            return;
        }
    }

    for (auto itr = operators.begin(); itr != operators.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token" << opRange + distance(operators.begin(), itr) << ","
                 << "operator" << token << ","
                 << "line number " << line_no << endl;
            return;
        }
    }

    for (auto itr = delimiters.begin(); itr != delimiters.end(); itr++)
    {
        if (*itr == token)
        {
            cout << "Token" << opRange + distance(delimiters.begin(), itr) << ","
                 << "delimiter" << token << ","
                 << "line number " << line_no << endl;
            return;
        }
    }

    //DFA for others
    int state = 1;
    char ch;

    for (int i = 0; i < token.length(); i++)
    {
        if (state == 10)
            break;

        ch = token[i];

        switch (state)
        {
        case 1:
            if (isalpha(t))
                state = 2;
            else if (t == '+' || t == '-')
                state = 3;
            else if (isdigit(t) && t != '0')
                state = 4;
            else if (t == '0')
                state = 5;
            else if (t == '"')
                state = 6;
            else
                state = 10;
            break;
        case 2:
            if (isalpha(t) || isdigit(t) || t == '_')
                state = 2;
            else
                state = 10;
            break;
        case 3:
            if (isdigit(t) && t != '0')
                state = 4;
            else if (t == '0')
                state = 11;
            else
                state = 10;
            break;
        case 4:
            if (isdigit(t))
                state = 4;
            else if (t == '.')
                state = 7;
            else
                state = 10;
            break;
        case 5:
            if (t == '.')
                state = 7;
            else
                state = 10;
            break;
        case 6:
            if (t != '"')
                state = 6;
            else
                state = 9;
            break;
        case 7:
            if (isdigit(t))
                state = 8;
            else
                state = 10;
            break;
        case 8:
            if (isdigit(t))
                state = 8;
            else
                state = 10;
            break;
        case 9:
            state = 10;
            break;
        case 10:
            printf("invalid token\n");
            return 10;
        case 11:
            if (t == '.')
                state = 7;
            else
                state = 10;
        }
    }

    switch (state)
    {
    case 2:
        // Identifier
        cout << "Token 150,"
             << "identifier " << token << ","
             << "line number " << line_no << endl;
        break;
    case 4:
        //Integers from 1-9
        cout << "Token 151,"
             << "Integer " << token << ","
             << "line number " << line_no << endl;
        break;
    case 5:
        // Specifically for integer =0
        cout << "Token 152,"
             << "Integer " << token << ","
             << "line number " << line_no << endl;
        break;
    case 8:
        // Float
        cout << "Token 153,"
             << "Float " << token << ","
             << "line number " << line_no << endl;
        break;
    case 9:
        //empty string
        cout << "Token 154,"
             << "String " << token << ","
             << "line number " << line_no << endl;
        break;
    default:
        cout << "Token 404,"
             << "invalid " << token << ","
             << "line number " << line_no << "........" endl;
        break;
    }

    return state;
}

void tokenizer(string token)
{
    int k = 0, flag = 0, curr;
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

            dfa(buffer);
            k = 0;
            if (flag == 2)
            {
                buffer += token[i];
            }
            flag = 0;
            i++;
            continue;
        }

        if (curr == 0)
        {
            buffer += token[i];
        }
        else if (curr == 1)
        {
            flag = 1;
            dfa(buffer);
            k = 0;
            buffer += token[i];
        }
        else if (curr == 2)
        {
            dfa(buffer);
            k = 0;
            buffer += token[i];
            dfa(buffer);
            k = 0;
        }

        i++;
    }
}

void Scanner(string line)
{
    int k = 0, flag = 0;
    string buffer;

    for (int i = 0; i < line.length(); i++)
    {
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
            else if (line[i] == ' ' or line[i] == '\n' or line[i] == '\0')
            {
                if (k == 0)
                    continue;

                buffer = "";
                tokenizer(buffer);
                k = 0;
            }
            else
            {
                buffer += line[i];
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

    if (k != 0)
    {
        tokenizer(buffer);
    }
}

int main()
{
    putKeys();
    putOperators();
    putDelimiters();
    string filename;
    cin >> filename;

    fstream file;

    if (file.is_open())
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