#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <list>
#include<locale>

using namespace std;

class Error;
class Collection;
int  DLdist(const wstring &, const wstring &, bool &);
class Error
{
public:
	string data;
	Error(const string & str) : data(str) {}
};

class Collection
{
private:
	unordered_set<wstring> _data;
public:
	Collection() {}
	void push(const wstring &);
	friend wostream & operator<<(wostream &, const Collection &);
	list<wstring> find(wstring) const;
};
wostream & operator<<(wostream & wos, const Collection & col)
{
	if (!col._data.empty())
	{
		for (auto x : col._data)
		{
			wos << x << endl;
		}
		return wos;
	}
}

void Collection::push(const wstring & str)
{
	_data.insert(str);
}

list<wstring> Collection::find(wstring str) const
{
	transform(str.begin(), str.end(), str.begin(), towlower);
	list<wstring> answer;
	if (_data.find(str) != _data.end())
		answer.push_back(wstring(L" ok"));
	else
	{
		for (auto x : _data)
		{
			bool flag = false;
			if (DLdist(str, x, flag) == 1)  answer.push_back(x);
			//if (DLdist(str, x) == 2) answer.push_back(x);
		}
	}
	return answer;
}

int main(int argc, char *argv[])
{
	try {
		//std::locale::global(std::locale(""));
		setlocale(LC_ALL, "");
		//std::locale l_utf8(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>);
		//wcin.imbue(l_utf8);

		size_t N;
		wcin >> N;
		wcin.ignore();
		if (!wcin.good()) throw Error("error");
		Collection col;
		for (unsigned int i = 0; i < N; ++i)
		{
			wstring el;
			getline(wcin, el);
			transform(el.begin(), el.end(), el.begin(), towlower);
			wcout << el;
			col.push(el);
		}
		while (!wcin.eof())
		{
			wstring word;
			getline(wcin, word);
			if (word.length() != 0)
			{
				list<wstring> answer = col.find(word);
				wcout << word << L" -";
				if (answer.empty()) wcout << L" ?" << endl;
				else
				{
					if (answer.front() != wstring(L" ok")) wcout << L"> ";
					while (answer.size() != 1)
					{
						answer.sort();
						wcout << answer.front() << ", ";
						answer.pop_front();
					}
					wcout << answer.front() << endl;
				}
			}
		}
	}
	catch (Error err) { cout << err.data << endl; }
	system("pause");
	return 0;
}

int  DLdist(const wstring & s1, const wstring & s2, bool & trans) //cраное динамическое программирование
{
	size_t l1 = s1.length();
	size_t l2 = s2.length();

	vector<vector<size_t>> d(l1 + 1, vector<size_t>(l2 + 1));

	for (size_t i = 0; i <= l1; ++i)
		d[i][0] = i;
	for (size_t i = 0; i <= l2; ++i)
		d[0][i] = i;

	size_t cost = 0;

	for (size_t i = 1; i <= l1; i++)
	{
		for (size_t j = 1; j <= l2; j++)
		{
			cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			d[i][j] = min(
				min(d[i - 1][j] + 1, // deletion
					d[i][j - 1] + 1), //insertion
				d[i - 1][j - 1] + cost // substitution
				);

			if ((i > 1) && (j > 1))
			{
				if ((s1[i-1] == s2[j - 2]) && (s1[i - 2] == s2[j-1]))
				{
					d[i][j] = min(d[i][j], d[i - 2][j - 2] + cost); //transposition
					if (d[i - 2][j - 2] + cost == min(d[i][j], d[i - 2][j - 2] + cost)) trans = true;
				}
			}
			/*for (size_t i = 0; i <= l1; i++)
			{
				for (size_t j = 0; j <= l2; j++)
					wcout << d[i][j];
				wcout << endl;
			}*/
		}
	}
	
	return d[l1][l2];
}
