#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

struct Position
{
	int row, column;
};

queue<Position> Queue;
stack<pair<Position, Position>> StackOfWays;

int Visited_nodes[8][8] =
{
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

bool Check(const Position& position)
{
	return (position.row >= 0 and position.row < 8 and position.column >= 0 and position.column < 8);
}

bool Equal(const Position& pos1, const Position& pos2)
{
	return (pos1.row == pos2.row && pos1.column == pos2.column);
}

void ShowTheWay(Position finish)
{
	char col; int sub;
	sub = finish.column + int('A');
	col = char(sub);
	cout << "Путь в нужную клетку: " << col << finish.row + 1;
	while (!StackOfWays.empty())
	{
		pair<Position, Position> couple = StackOfWays.top();
		if (Equal(couple.second, finish))
		{
			finish = couple.first;
			sub = finish.column + int('A');
			col = char(sub);
			cout << " <- " << col << finish.row + 1;
		}
		StackOfWays.pop();
	}
	cout << "\n";
}

void ShortWay(const Position& start, const Position& finish)//const чтобы не менять позиции
{
	Position tempPosition;

	int overall[4] = {-2, -1, 1, 2};
	int arr[2];
	for (int i = 0; i < 4; i++)
	{

		if (abs(overall[i]) == 2) {		
			arr[0] = 1;
			arr[1] = -1;
		}
		else {
			arr[0] = 2;
			arr[1] = -2;
		}

		for (int j = 0; j < 2; j++)
		{
			int row_dif = overall[i];
			int col_dif = arr[j];

			tempPosition.row = start.row + row_dif; tempPosition.column = start.column + col_dif;
			if (Check(tempPosition))
			{
				if (Equal(tempPosition, finish))
				{
					StackOfWays.push({ start,tempPosition });
					ShowTheWay(finish);
					return;
				}
				else
				{
					if (Visited_nodes[tempPosition.row][tempPosition.column] != 1)
					{
						Visited_nodes[tempPosition.row][tempPosition.column] = 1;
						Queue.push(tempPosition);
						StackOfWays.push({ start,tempPosition });
					}
				}
			}

		}
	}
	Position nextStart = Queue.front();
	Queue.pop();
	ShortWay(nextStart, finish);
}

int main()
{
	setlocale(LC_ALL, "ru");
	string a, b;
	char start_column, finish_column;
	string first_parse, second_parse;
	Position start, finish;


	bool check = true;
	string checkword = "yes";
	while (check) {

		if (checkword == "yes") {
			cout << "Введите изначальное положение коня" << endl;
			cout << "Например - H2" << endl;
			cout << "Введите: \n";
			getline(cin, first_parse);

			start_column = toupper(first_parse[0]);
			a = first_parse[1];
			start.row = stoi(a) - 1;
			start.column = int(start_column) - int('A');

			cout << "Введите конечное положение коня" << endl;
			cout << "Например - C3" << endl;
			cout << "Введите: \n";
			getline(cin, second_parse);

			finish_column = toupper(second_parse[0]);
			b = second_parse[1];
			finish.row = stoi(b) - 1;
			finish.column = int(finish_column) - int('A');

			ShortWay(start, finish);
		}

		cout << "Вы хотите продожить?" << endl;
		cout << "Введите \"yes\", если хотите\n";
		getline(cin, checkword);

		if (checkword != "yes")
			check = false;
	}
}