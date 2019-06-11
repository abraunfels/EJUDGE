#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <array>
#include <fstream>


using std::endl;
using std::string;
using std::vector;

class Error;
class Queue;
void get_error(string);
void check_size(string &, std::ifstream &, std::ofstream &);

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

class Queue
{
private:
	vector<string> _data;
	size_t _size;
	size_t _top;
	string _pop();
	void _push(string &);
public:
	Queue() = delete;
	Queue(const Queue &) = delete;
	Queue & operator= (const Queue &) = delete;
	Queue(Queue &&) = delete;
	Queue & operator= (Queue &&) = delete;
	Queue(size_t);
	friend std::ofstream & operator<<(std::ofstream &, Queue &);
	void check_key(string &, std::ofstream &);
};

Queue::Queue(size_t n)
{
	_data.reserve(n);
	_size = 0;
	for (unsigned int i = 0; i < _data.capacity(); ++i) //??? ????? ?????????
		_data.push_back("");
	_top = 0;
}

void Queue::_push(string & str)
{
	if (_size < _data.capacity())
	{
		_data[(_top+_size)%_data.capacity()] = str;
		++_size;
	}
	else get_error(string("overflow"));
}

string Queue::_pop()
{
	if (_size)
	{
		string str = _data.at(_top);
		_data[_top] = "";
		++_top;
		if (_top == _data.capacity()) _top = 0;
		--_size;
		return str;
	}
	else get_error(string("underflow"));
}

std::ofstream & operator<<(std::ofstream & os, Queue & queue)
{
	if (queue._size)
	{
		for (unsigned int i = 0; i < queue._size - 1; ++i)
			os << queue._data.at((queue._top+i) % queue._data.capacity()) << " ";
		os << queue._data.at((queue._top + queue._size - 1) % queue._data.capacity()) << endl;
		return os;
	}
	else get_error(string("empty"));
}

void Queue::check_key(string & key_word, std::ofstream & ofile)
{
	std::array<string, 3> keys = { string("push "),string("pop"),string("print") };
	if (key_word.empty());
	else if (key_word.substr(0, 5) == keys.at(0))
	{
		if (key_word.find_first_of(' ', keys.at(0).size() + 1) == string::npos)
		{
			string temp = key_word.substr(5);
			this->_push(temp);
		}
		else get_error(string("error"));
	}
	else if (key_word == keys.at(1))
		ofile << this->_pop() << endl;
	else if (key_word == keys.at(2))
		ofile << *this;
	else get_error(string("error"));
}

void get_error(string str)
{
	Error err(str);
	throw err;
}

void check_size(string & key_size, std::ifstream & ifile, std::ofstream & ofile)
{
	if (key_size.empty());
	else if (key_size.substr(0, 9) == "set_size ")
	{
		int n = std::stoi(key_size.substr(9, string::npos));
		if (n > 0)
		{
			Queue queue(n);
			while (!ifile.eof())
			{

				string key_world;
				getline(ifile, key_world);
				try {
					queue.check_key(key_world, ofile);
				}
				catch (Error err)
				{
					ofile << err.get_data() << endl;
					continue;
				}
			}
		}
		else get_error(string("error"));
	}
	else get_error(string("error"));
}




int main(int argc, char *argv[])
{
	if(argc != 3) exit(1);

	std::ifstream ifile;
	std::ofstream ofile;
	ifile.open(argv[1], std::ios_base::in);
	ofile.open(argv[2], std::ios_base::out);
	if ((!ifile) || (!ofile)) 
	{
		std::cerr << "hui";
		exit(EXIT_FAILURE);
	}
	while (!ifile.eof())
	{
		try
		{
			string key_size;
			getline(ifile, key_size);
			check_size(key_size, ifile, ofile);
		}
		catch (Error err)
		{
			ofile << err.get_data() << endl;
			continue;
		}
		catch (std::exception e)
		{
			ofile << "error" << endl;
			continue;
		}
	}
	return 0;
}

