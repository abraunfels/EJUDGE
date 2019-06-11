#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

class Knapsack
{
	private:
		vector<pair<size_t, size_t>> _data;
		size_t _W;
		vector<vector<size_t>> _mtrx;
		vector<size_t> _answer;
		void _ans(int, int);
	public:
		Knapsack(size_t size) : _W(size) {}
		void push(pair <size_t, size_t>);
		int solve();
		vector<pair<size_t, size_t>> get_ans();
		friend ostream & operator<<(ostream &, Knapsack &);
};

ostream & operator<<(ostream & os, Knapsack & knap)
{
	for (auto x : knap._data)
		cout << x.first << " " << x.second << endl; 
	return os;
}

void Knapsack::push(pair <size_t, size_t> pair)
{
	_data.push_back(pair);
}

int Knapsack::solve()
{
	size_t n = _data.size();
	_mtrx = vector<vector<size_t>> (_W + 1, vector<size_t>(n + 1)); //??????? ???? ?????????????? ??????????
	for (size_t j = 1; j <= n; j++)
	{
		for (unsigned int w = 1; w <= _W; ++w)
		{
			if (_data[j - 1].first <= w) //???? ??????? ??????? ??????? ? ??????? ??????
			{
				_mtrx[w][j] = max(_mtrx[w][j - 1], _mtrx[w - _data[j - 1].first][j - 1] + _data[j - 1].second); //?????????? ????????? ? ??? ? ??? ? ? ??????????? ?? ????? ?????? ????? ?????????
			}
			else //???? ?? ?? ???????
			{
				_mtrx [w][j] = _mtrx[w][j - 1]; //?? ??????
			}
		}
	}
	for (size_t j = 0; j <= n; j++)
	{
		for (unsigned int w = 0; w <= _W; ++w)
			cout << _mtrx[w][j] << " ";
		cout << endl;
	}
	return _mtrx[_W][n]; //????????? ???????????? ???????????? ??????? ????????
}

void Knapsack::_ans(int w, int s) //k s ??? ???? ??? ????? ???????
{
	if (_mtrx[w][s] == 0)
		return;
	if (_mtrx[w][s - 1] == _mtrx[w][s])
		_ans(w, s - 1);
	else
	{
		_answer.push_back(s - 1);
		_ans(w - _data[s - 1].first, s-1);
	}

}

vector<pair<size_t, size_t>> Knapsack::get_ans()
{
	_ans(_W, _data.size());
	vector<pair<size_t, size_t>> res;
	for (auto x : _answer)
	{
	//	cout << x << " " <<  _data.at(x - 1).second << endl;
		res.emplace_back(make_pair(x, _data.at(x - 1).second));
	}
	return res;
}

int main()
{
	int weight;
	int cost;
	int size;
	
	cin >> size;

	if (cin.good())
	{
		Knapsack knap (size);
		while (!cin.eof())
		{
			cin >> weight >> cost;
			if (cin.good()) knap.push(make_pair(weight, cost));
		}
		cout << knap.solve() << endl;
		vector<pair<size_t, size_t>> answer = knap.get_ans();
		for (auto x : answer)
			cout << x.first << " " << x.second << endl;
	}
	return 0;
}
