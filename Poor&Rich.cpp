#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

deque<size_t> convert(size_t);


int main(int argc, char *argv[])
{
	size_t value, value1;
	stack<string> steps;
	stack<string> steps1;



	//value = stoi(argv[1]);
	cin >> value;

	value1 = value;

	if (cin.good())
	{
		while (value != 0)
		{
			if (value % 2 == 0)
			{
				value /= 2;
				steps.push("dbl");
			}
			if (value == 1)
			{
				--value;
				steps.push("inc");
			}
			if (value % 2 == 1)
			{
				deque<size_t> Uvalue = convert(value + 1);
				deque<size_t> Lvalue = convert(value - 1);

				Uvalue.pop_back();
				Lvalue.pop_back();

				int Ucount = 0;
				int Lcount = 0;
	
				for (auto x : Uvalue)
					if (x == 1) 
						++Ucount;
				for (auto x : Lvalue)
					if (x == 1) 
						++Lcount;

				if (Ucount < Lcount)
				{
					++value;
					steps.push("dec");
				}
				if (Ucount > Lcount)
				{
					steps.push("inc");
					--value;
				}
				if (Ucount == Lcount)
				{
					int len = Uvalue.size() / 2;

					for (size_t i = len - 1 ; i < Uvalue.size() - 1; ++i) //первое где не равны
					{
						if (Uvalue[i] > Lvalue[i])
						{
							steps.push("dec");
							++value;
							break;
						}
						if (Uvalue[i] < Lvalue[i] || Lvalue.size() < Uvalue.size())
						{
							steps.push("inc");
							--value;
							break;
						}
					}

				}
			}
		}
		
		while (value1 != 0)
		{
			if (value1 % 2 == 0)
			{
				value1 /= 2;
				steps1.push("dbl");
			}
			if (value1 == 1)
			{
				--value1;
				steps1.push("inc");
			}
			if (value1 % 2 == 1)
			{
				deque<size_t> Uvalue = convert(value1 + 1);
				deque<size_t> Lvalue = convert(value1 - 1);

				int Ucount = 0;
				int Lcount = 0;

				for (auto x : Uvalue)
					if (x == 1)
						++Ucount;
				for (auto x : Lvalue)
					if (x == 1)
						++Lcount;
				if (Ucount < Lcount)
				{
					steps1.push("dec");
					++value1;
				}
				if (Ucount == Lcount)
				{
					steps1.push("inc");
					--value1;
				}
				if (Ucount > Lcount)
				{
					steps1.push("inc");
					--value1;
				}
			}
		}
		if (steps.size() < steps1.size())
		{
			while (!steps.empty())
			{
				cout << steps.top() << endl;
				steps.pop();
			}
		}
		if (steps.size() >= steps1.size())
		{
			while (!steps1.empty())
			{
				cout << steps1.top() << endl;
				steps1.pop();
			}
		}
	}
	return 0;
}

deque<size_t> convert(size_t a)
{
	deque<size_t> res;
	while (a != 0)
	{
		res.push_front(a % 2);
		a /= 2;
	}
	return res;
}