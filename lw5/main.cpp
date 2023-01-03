#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <int> MAX_COUNT;
void print_desk(string desk[8][8]);
void print_answer(int answer);
void find_maximum();
void copy_desk(string new_desk[8][8], string desk[8][8]);
void move(int current_position_y, int current_position_x, string desk[8][8], int count);
void white_figure_counter(int count);

int main()
{
	string desk[8][8];
	int position_by_x = -1;
	int position_by_y = -1;
	int white_figure_count = 0;

	string line;
	ifstream fin;

	fin.open("input6.txt");

	for (int y = 0; y < 8; y++)
	{
		getline(fin, line, '\n');
		for (int x = 0; x < 8; x++)
		{
			desk[y][x] = line[x];

			if (line[x] == '2')
			{
				white_figure_count++;
				position_by_x = x;
				position_by_y = y;
			}
		}
	}
	fin.close();

	if (white_figure_count != 1)
		white_figure_counter(white_figure_count);
	else
	{
		move(position_by_y, position_by_x, desk, 0);
		find_maximum();
	}

	return 0;
}

void print_desk(string desk[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << desk[i][j];
		}
		cout << endl;
	}
}
void print_answer(int answer)
{
	cout << "Max count: " << answer;
	ofstream fout("output.txt");
	fout << "Max count: " << answer;
	fout.close();
}
void find_maximum()
{
	int result = 0;

	for (int n : MAX_COUNT)
	{
		if (n > result)
			result = n;
	}
	print_answer(result);
}
void copy_desk(string new_desk[8][8], string desk[8][8])
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			new_desk[y][x] = desk[y][x];
		}
	}
}
void move(int current_position_y, int current_position_x, string desk[8][8], int count)
{
	MAX_COUNT.push_back(count);

	if (current_position_x >= 0 && current_position_x < 8)
	{
		if (current_position_y >= 0 && current_position_y < 8)
		{
			if (desk[current_position_y + 1][current_position_x - 1] == "1" && desk[current_position_y + 2][current_position_x - 2] != "1"
				&& (current_position_y + 2 <= 8 && current_position_y + 2 >= 0 && current_position_x - 2 <= 8 && current_position_x - 2 >= 0))
			{
				string new_desk[8][8];
				copy_desk(new_desk, desk);
				int new_count = count;
				new_count++;
				int position_x = current_position_x;
				int position_y = current_position_y;
				new_desk[position_y + 1][position_x - 1] = "0";
				move(position_y + 2, position_x - 2, new_desk, new_count);
			}
			if (desk[current_position_y - 1][current_position_x + 1] == "1" && desk[current_position_y - 2][current_position_x + 2] != "1"
				&& (current_position_y - 2 <= 8 && current_position_y - 2 >= 0 && current_position_x + 2 <= 8 && current_position_x + 2 >= 0))
			{
				string new_desk[8][8];
				copy_desk(new_desk, desk);
				int new_count = count;
				new_count++;
				int position_x = current_position_x;
				int position_y = current_position_y;
				new_desk[position_y - 1][position_x + 1] = "0";
				move(position_y - 2, position_x + 2, new_desk, new_count);
			}
			if (desk[current_position_y + 1][current_position_x + 1] == "1" && desk[current_position_y + 2][current_position_x + 2] != "1"
				&& (current_position_y + 2 <= 8 && current_position_y + 2 >= 0 && current_position_x + 2 <= 8 && current_position_x + 2 >= 0))
			{
				string new_desk[8][8];
				copy_desk(new_desk, desk);
				int new_count = count;
				new_count++;
				int position_x = current_position_x;
				int position_y = current_position_y;
				new_desk[position_y + 1][position_x + 1] = "0";
				move(position_y + 2, position_x + 2, new_desk, new_count);
			}
			if (desk[current_position_y - 1][current_position_x - 1] == "1" && desk[current_position_y - 2][current_position_x - 2] != "1"
				&& (current_position_y - 2 <= 8 && current_position_y - 2 >= 0 && current_position_x - 2 <= 8 && current_position_x - 2 >= 0))
			{
				string new_desk[8][8];
				copy_desk(new_desk, desk);
				int new_count = count;
				new_count++;
				int position_x = current_position_x;
				int position_y = current_position_y;
				new_desk[position_y - 1][position_x - 1] = "0";
				move(position_y - 2, position_x - 2, new_desk, new_count);
			}
		}
	}
}
void white_figure_counter(int count)
{
	if (count > 1)
		cout << "White figure more than one" << endl;
	else if (count < 1)
		cout << "White figure less than one" << endl;
}