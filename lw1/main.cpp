#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>

using namespace std;

int main(int argc, char** argv)
{
	list <int> startChars;
	list <int> ::iterator it;
	bool firstLine = true;
	char buffer[257];
	int allChars = 0;

	FILE* file_in = fopen(argv[1], "r");
	FILE* file_out = fopen(argv[2], "w");

	if (file_in == NULL || file_out == NULL) perror("ERROR. File was not opened.");
	else
	{
		while (!feof(file_in))
		{
			if (fgets(buffer, 257, file_in) != NULL)
			{
				startChars.push_back(strlen(buffer) + 1);
				allChars += strlen(buffer) + 1;

				if (strlen(buffer) > 255)
				{
					cout << "ERROR. The maximum number of characters per line is 255." << endl;
					return 1;
				}
			}
		}

		for (int i = allChars; i > 0;)
		{
			fseek(file_in, allChars - startChars.back(), SEEK_SET);
			allChars -= startChars.back();
			i -= startChars.back();

			if (fgets(buffer, 255, file_in) != NULL)
			{
				if (!firstLine && strrchr(buffer, '\n'))
				{
					fputs(buffer, file_out);
				}
				else
				{
					fputs(buffer, file_out);
					fputs("\n", file_out);
					firstLine = false;
				}
			}
			startChars.pop_back();
		}

		fclose(file_in);
		fclose(file_out);
	}

	return 0;
}