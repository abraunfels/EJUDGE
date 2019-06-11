#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Error;
class Stack;
void get_error(string);
void check_key(string &, Stack &);
void check_size(string &);

class Error
{
	string _s;
public:
	Error(string & str) : _s(str) {}
	string get_data() const
	{
		return _s;
	}
};

class Stack
{
private:
	vector<string> _data;
	size_t _size;
	size_t _capacity;
	string _pop();
	void _push(string &);
public:
	Stack() = delete;
	Stack(const Stack &) = delete;
	Stack & operator= (const Stack &) = delete;
	Stack(Stack &&) = delete;
	Stack & operator= (Stack &&) = delete;
	Stack(size_t);
	friend std::ostream & operator<<(std::ostream &, const Stack &);
	void check_key(string &);
};

Stack::Stack(size_t n)
{
	_data.reserve(n);
}

void Stack::_push(string & str)
{
	if (_data.size()<_data.capacity())
		_data.push_back(str);
	else get_error(string("overflow"));
}

string Stack::_pop()
{
	if (!_data.empty())
	{
		string str = _data.back();
		_data.pop_back();
		return str;
	}
	else get_error(string("underflow"));

}

std::ostream & operator<<(std::ostream & os, const Stack & stack)
{
	if (!stack._data.empty())
	{
		for (unsigned int i = 0; i < stack._data.size()-1; ++i) 
			os << stack._data.at(i) << ' ';
		os << stack._data.at(stack._data.size()-1);
		os << endl;
		return os;
	}
	else get_error(string("empty"));
}

void Stack::check_key(string & key_word)
{
	std::array<string, 3> keys = { string("push "),string("pop"),string("print") };
	if (key_word.empty()); 
	else if (key_word.substr(0, 5) == keys.at(0))
	{
		if (key_word.find_first_of(' ', keys.at(0).size()+1) == string::npos)
		{
			string temp = key_word.substr(5);
			this->_push(temp);
		}
		else get_error(string("error"));
	}
	else if (key_word == keys.at(1))
		cout << this->_pop() << endl;
	else if (key_word == keys.at(2))
		cout << *this;
	else get_error(string("error"));
}

void get_error(string str)
{
	Error err(str);
	throw err;
}

void check_size(string & key_size)
{
	if (key_size.empty());
	else if (key_size.substr(0, 9) == "set_size ")
	{
		int n = std::stoi(key_size.substr(9, string::npos));
		if (n > 0)
		{
			Stack stack(n);
			while (!cin.eof())
			{
				
				string key_world;
				getline(cin, key_world);
				try {
					stack.check_key(key_world);
				}
				catch (Error err)
				{
					cout << err.get_data() << endl;
					continue;
				}
			}
		}
		else get_error(string("error"));
	}
	else get_error(string("error"));
}




int main()
{
	Stack * stack = nullptr;
	bool exist = false;
	while (!cin.eof())
	{
		try
		{
			string key_size;
			getline(cin, key_size);
			check_size(key_size);
		}
		catch (Error err)
		{
			cout << err.get_data() << endl;
			continue;
		}
		catch (std::exception e)
		{
			cout << "error" << endl;
			continue;
		}
	}
	return 0;
}

