#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename T>
struct NodeStack
{
	T item;
	NodeStack<T>* next;
};

template <typename T>
class def_stack
{
private:
	NodeStack<T>* pTop;
	int count;
public:
	def_stack() { pTop = nullptr; count = 0; }

	def_stack(const def_stack& ds)
	{
		NodeStack<T>* p;
		NodeStack<T>* p2;
		NodeStack<T>* p3;

		pTop = nullptr;
		p3 = nullptr;

		p = ds.pTop;
		while (p != nullptr)
		{
			try
			{
				p2 = new NodeStack<T>;
			}
			catch (bad_alloc e)
			{
				cout << e.what() << endl;
				return;
			}
			p2->item = p->item;
			p2->next = nullptr;

			if (pTop == nullptr)
			{
				pTop = p2;
				p3 = p2;
			}
			else
			{
				p3->next = p2;
				p3 = p3->next;
			}
			p = p->next;
		}
	}

	void push(T item)
	{
		NodeStack<T>* p;

		try
		{
			p = new NodeStack<T>;
		}
		catch (bad_alloc e)
		{
			cout << e.what() << endl;
			return;
		}
		p->item = item;
		p->next = pTop;
		count++;
		pTop = p;
	}

	void clear()
	{
		NodeStack<T>* p;
		NodeStack<T>* p2;

		p = pTop;

		while (p != nullptr)
		{
			p2 = p;
			p = p->next;
			delete p2;
		}
		count = 0;
		pTop = nullptr;
	}

	~def_stack()
	{
		count = 0;
		clear();
	}

	T pop() {
		if (pTop == nullptr)
			return 0;

		NodeStack<T>* p2;
		T item;
		item = pTop->item;

		p2 = pTop;
		pTop = pTop->next;

		delete p2;
		count--;
		return item;
	}

	T get_last()
	{
		if (pTop == nullptr)
			return 0;
		else
			return pTop->item;

	}

	bool is_empty()
	{
		if (pTop == nullptr)
			return true;
		else
			return false;
	}

	int size()
	{
		return count;
	}
};

bool isOperator(char x)
{
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
		return true;
	}
	return false;
}

void print_error(string error_text)
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << error_text << endl;
	SetConsoleTextAttribute(hConsole, 7);
}

string prefix_to_postfix(string prefix_exp)
{
	std::ostringstream o;
	def_stack<string> s;
	int length = prefix_exp.size();
	int count_operators = 0;
	int count_operands = 0;

	for (int i = length - 1; i >= 0; i--)
	{
		if (isOperator(prefix_exp[i]))
		{
			string op1, op2;

			if (!s.is_empty())
			{
				op1 = s.get_last();
				s.pop();
			}
			else
			{
				o << "Позиция ошибки: " << i + 1;
				print_error(o.str());
				return "ERROR";
			}
			if (!s.is_empty())
			{
				op2 = s.get_last();
				s.pop();
			}
			else
			{
				o << "Позиция ошибки: " << i + 1;
				print_error(o.str());
				return "ERROR";
			}

			string temp = op1 + op2 + prefix_exp[i];
			count_operators++;
			s.push(temp);
		}
		else
		{
			count_operands++;
			s.push(string(1, prefix_exp[i]));
		}
	}

	if (count_operands - count_operators != 1)
	{
		o << "Ошибка: количество операторов должно быть на один меньше чем количество операндов!";
		print_error(o.str());
		return "ERROR";
	}

	return s.get_last();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string prefix_exp;
	string postfix_exp;

	while (true)
	{
		cout << "Введите выражение в префиксной форме: ";
		cin >> prefix_exp;
		if (prefix_exp == "exit")
			break;
		postfix_exp = prefix_to_postfix(prefix_exp);
		if (postfix_exp != "ERROR")
			cout << "Постфиксная форма: " << postfix_exp << endl;
	}
	return 0;
}