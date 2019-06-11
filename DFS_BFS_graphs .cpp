#include <iostream>
#include <set>
#include <map>
#include <string>
#include <unordered_set>
#include <deque>
#include <utility>
#include <algorithm>

#define GRAPH std::map<std::string, std::set<std::string>>

enum
{
	UDFS,
	DDFS,
	UBFS,
	DBFS,
};

using namespace std;

class Graph
{
	private:
		bool _directed;
		GRAPH _data;
		unordered_set<string> _white;
		unordered_set<string> _black;
		unordered_set<string> _gray;
		
		void _DFS(string);
		void _BFS(deque<string> &);
		
	public:
		Graph(){}
		Graph(bool b) : _directed(b) {}
		friend ostream & operator<<(ostream & os, Graph & graph);
		void push(pair<string, string>);
		void startDFS(string &);
		void startBFS(string  &);
};

void Graph::push(pair<string, string> p)
{
	_white.insert(p.first);
	_white.insert(p.second);
	auto it = _data.find(p.first);
	if (it != _data.end())
	{
		it->second.insert(p.second);
	}
	else
	{
		set<string> tmp;
		tmp.insert(p.second);
		_data.emplace(make_pair(p.first, tmp));
	}
	if (!_directed)
	{
		it = _data.find(p.second);
		if (it != _data.end())
		{
			it->second.insert(p.first);
		}
		else
		{
			set<string> tmp;
			tmp.insert(p.first);
			_data.emplace(make_pair(p.second, tmp));
		}
	}
}

ostream & operator<<(ostream & os, Graph & graph)
{
	for (auto x : graph._data)
	{
		os << x.first;
		for (auto y : x.second)
			os << " " << y;
		os << endl;
	}
	return os;
}

void Graph::startDFS(string & str)
{
	if (_white.find(str) == _white.end()) return;
	_data.erase("");
	deque<string> st;
	st.push_front(str);
	while (!st.empty())
	{
		string current = st.front();
		st.pop_front();
		if (_white.find(current) != _white.end())
		{
			cout << current << endl;
			_white.erase(current);
			auto it = _data.find(current);
			if (it != _data.end())
			{
				for (set<string>::reverse_iterator i = it->second.rbegin(); i != it->second.rend(); ++i)
					st.push_front(*i);
			}
		}
	}
	//_DFS(str);
}

void Graph::_DFS(string str)
{
	cout << str << endl;
	_white.erase(str);
	auto it = _data.find(str);
	if (it != _data.end())
	{
		for (auto x : it->second)
		{
			if (_white.find(x) != _white.end())
				_DFS(x);
		}
	}
}

void Graph::startBFS(string & str)
{
	if (_white.find(str) == _white.end()) return;
	deque<string> q;
	q.push_back(str);
	while (!q.empty())
	{
		string current = q.front();
		cout << current << endl;
		q.pop_front();
		_white.erase(current);
		auto it = _data.find(current);
		if (it != _data.end())
		{
			for (const auto x : it->second)
				if (_white.find(x) != _white.end())
				{
					q.push_back(x);
					_white.erase(x);
				}
		}
	}
	//_BFS(q);
}

void Graph::_BFS(deque<string> & q)
{
	string current = q.front();
	cout << current << endl;
	q.pop_front();
	_white.erase(current);
	auto it = _data.find(current);
	if (it != _data.end())
	{
		for (const auto x : it->second)
			if (_white.find(x) != _white.end())
			{
				q.push_back(x);
				_white.erase(x);
			}
	}
	if (q.empty()) return;
	else _BFS(q);
}


int main()
{
	string str;
	getline(cin, str);

	bool check1 = false, check2 = false;
	bool directed = false, type = false;
	if (*str.begin() == 'u') check1 = true; 
	if (*str.begin() == 'd') { check1 = true; directed = true; }
	if (*(str.end() - 1) == 'b') check2 = true;
	if (*(str.end() - 1) == 'd') { check2 = true; type = true; }
	string start(str.begin() + 2, str.end() - 2);
	str = start;
	if (check1 && check2)
	{
		Graph graph(directed);
		while (!cin.eof())
		{
			getline(cin, str);
		    graph.push(make_pair(str.substr(0, str.find_first_of(' ')), str.substr(str.find_first_of(' ')+1)));
		}
		if (type) graph.startDFS(start);
		else graph.startBFS(start);
	}
	return 0;
}
