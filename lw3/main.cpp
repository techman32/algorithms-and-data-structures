#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct tree
{
	string name;
	int level;

	tree* root;
	vector<tree*> sons;
};

tree* root = NULL;

struct professor
{
	string name;
	vector<string> department;
};

void show_info(int color_number);
void print_professor_by_color(int color_number, string name);
void init_tree(string path, tree*& root);
int get_level(string line);
string get_name(string line);
void print_down(tree* p, int level, vector<professor>& counter, string department);
void print(vector<professor>& counter, int count);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const int count = 3;
	string path;
	ifstream fin;
	string department;
	tree* root = 0;
	vector <professor> counter;

	show_info(2);

	while (true)
	{
		cout << "Введите название файла: ";
		cin >> path;

		if (path == "exit") break;
		else fin.open(path);

		if (!fin)
		{
			cout << "Невозможно открыть файл, попробуйте снова." << endl;
			continue;
		}
		else
		{
			init_tree(path, root);
			print_down(root, 0, counter, department);
			print(counter, count);
		}
		fin.close();
	}

	return 0;
}

void show_info(int color_number)
{
	SetConsoleTextAttribute(hConsole, color_number);
	cout << "Для завершения работы программы введите \"exit\"." << endl;
	SetConsoleTextAttribute(hConsole, 7);
}
void show_professor_by_color(int color_number, string name)
{
	SetConsoleTextAttribute(hConsole, color_number);
	cout << name;
	SetConsoleTextAttribute(hConsole, 7);
}
void init_tree(string path, tree*& root)
{
	int level;
	string line;
	string name;

	tree* new_node;
	tree* last_node = nullptr;
	tree* last_node_dipper = nullptr;
	int level_last_node = -1;

	ifstream file(path);

	while (!file.eof())
	{
		getline(file, line);
		if (line.length() == 0) continue;

		level = get_level(line);
		name = get_name(line);

		new_node = new tree;
		new_node->level = level;
		new_node->name = name;

		if (level == 0)
		{
			root = new_node;
			last_node = root;
			level_last_node = 0;
			continue;
		}

		if (level > level_last_node)
		{
			last_node->sons.push_back(new_node);
			new_node->root = last_node;
		}
		else if (level == level_last_node)
		{
			last_node_dipper = last_node->root;
			last_node_dipper->sons.push_back(new_node);
			new_node->root = last_node_dipper;
		}
		else
		{
			last_node_dipper = last_node;

			for (int i = 0; i <= level_last_node - level; i++)
				last_node_dipper = last_node_dipper->root;
			last_node_dipper->sons.push_back(new_node);
			new_node->root = last_node_dipper;
		}

		level_last_node = level;
		last_node = new_node;
	}
	file.close();
}
int get_level(string line)
{
	int level = 0;

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '.') level++;
		else break;
	}

	return level;
}
string get_name(string line)
{
	string name = "";

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != '.') name.push_back(line[i]);
	}
	return name;
}
void print_down(tree* p, int level, vector<professor>& counter, string department)
{
	if (level == 2) department = p->name;

	if (p->sons.size())
	{
		for (int i = 0; i < p->sons.size(); i++)
		{
			print_down(p->sons[i], level + 1, counter, department);
		}
	}
	else
	{
		if (level <= 2) return;

		if (counter.size() == 0)
		{
			professor professor;
			professor.name = p->name;
			professor.department.push_back(department);
			counter.push_back(professor);
			return;
		}

		bool isName = false;
		bool isDep = false;
		professor professor;

		for (int i = 0; i < counter.size(); i++)
		{
			if (counter[i].name == p->name)
			{
				isName = true;
				for (int j = 0; j < counter[i].department.size(); j++)
				{
					if (counter[i].department[j] == department) isDep = true;
				}
			}
		}

		if (isName)
		{
			if (!isDep)
			{
				for (int i = 0; i < counter.size(); i++)
				{
					if (counter[i].name == p->name)
					{
						counter[i].department.push_back(department);
						break;
					}
				}
			}
		}
		else
		{
			professor.name = p->name;
			professor.department.push_back(department);
			counter.push_back(professor);
		}
	}
}
void print(vector <professor>& counter, int count)
{
	for (int i = 0; i < counter.size(); i++)
	{
		if (counter[i].department.size() >= count)
		{
			cout << "Преподаватель ";
			show_professor_by_color(3, counter[i].name);
			cout << " ведет занятия на " << count << " или более кафедрах." << endl;
			cout << "А именно на кафедрах: ";

			for (int j = 0; j < counter[i].department.size(); j++)
			{
				if (counter[i].department.size() - j != 1)
					cout << counter[i].department[j] << ", ";
				else
					cout << counter[i].department[j] << ".";
			}
			cout << endl << endl;
		}
	}
}