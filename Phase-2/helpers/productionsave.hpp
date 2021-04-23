#ifndef PRODS_H
#define PRODS_H
typedef pair<string, vector<string>> rule;

class prods
{
public:
	multimap<string, vector<string>> productionset;
	map<int, rule> rulenumber;

	prods()
	{
		string inp;
		ifstream set_stre;
		set_stre.open("helpers/final_grammer.md");
		productionset.clear();
		int k = 0;
		string line;

		while (getline(set_stre, line))
		{
			if (line.length() == 0)
				continue;
			stringstream toknes(line);
			string lhs;
			toknes >> lhs;
			string dummy;
			toknes >> dummy;
			std::vector<string> rhs;

			while (toknes >> dummy)
			{
				rhs.push_back(dummy);
			}

			rule thsirul;
			thsirul.first = lhs;
			thsirul.second = rhs;
			rulenumber[++k] = thsirul;
			string haha = thsirul.first;
			vector<string> ffaf = thsirul.second;
			productionset.insert({thsirul.first, thsirul.second});
		}
	}

	void print_prods()
	{
		for (auto x : productionset)
		{
			cout << x.ff << " -->> ";
			for (auto y : x.ss)
			{
				cout << y << " ";
			}
			cout << endl;
		}
	}

	void printrule(rule x)
	{
		cout << x.ff << " -->> ";
		for (auto y : x.ss)
		{
			cout << y << " ";
		}
		cout << endl;
	}
};

#endif