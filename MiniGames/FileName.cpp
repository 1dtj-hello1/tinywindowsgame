#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Sel {
	int i;
	int j;
	bool ifsel = 0;
	Sel() {
		i = 0;
		j = 0;
		ifsel = 0;
	}
};
struct Cur {
	int i;
	int j;
	Cur() {
		i = 0;
		j = 0;
	}
};
class Spidercard
{

#define WEIGHT 10
#define LONG 104 
public:
	Spidercard()
	{
		record = vector<int>(13, 0);
		showrecordstrat = vector<int>(10, 0);
		up = vector<string>(10, string(0, ' '));
		down = vector<string>(5, string(10, ' '));
		srand((unsigned int)time(NULL));
		int data[] = { 5,5,5,5,4,4,4,4,4,4 };
		for (int i = 0; i < 10; i++) {
			showrecordstrat[i] = data[i];
		}
	}
	~Spidercard()
	{
	}
	void init()
	{
		int count = 5;
		while (count--)
			for (int i = 0; i < 10; i++)
				up[i].push_back(getanewcard());
		up[0].push_back(getanewcard());
		up[1].push_back(getanewcard());
		up[2].push_back(getanewcard());
		up[3].push_back(getanewcard());
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				down[i][j] = getanewcard();
			}
		}

	}
	void start()
	{
		init();
		while (1)
		{
			show();
			if (!next_step())
				break;
			cout << endl;
			if (ifwin())
			{
				system("cls");
				cout << "you win!" << endl;
				break;
			}
		}
	}
private:
	vector<int> record;
	vector<int> showrecordstrat;
	Cur cur;
	Sel sel;
	vector<string> up;
	vector<string> down;
	char getanewcard() {
		int t;
		while (1) {
			t = rand() % 13;
			if (record[t] < 8)
				break;
		}
		record[t]++;

		if (t == 0)       return 'A';
		else if (t == 9)  return 'T';   // T 代表牌面10
		else if (t == 10) return 'J';
		else if (t == 11) return 'Q';
		else if (t == 12) return 'K';
		else              return '2' + (t - 1); // t=1→'2' ... t=8→'9'
	}
	void getnewcard()
	{
		string temp = down.back();
		down.pop_back();
		for (int i = 0; i < 10; i++)
		{
			up[i].push_back(temp.back());
			temp.pop_back();
		}
	}
	bool ifisnext(char i, char j)
	{
		if (i+1 == j)
			return true;
		else if (i == 'A' && j == '2')
			return true;
		else if (i == '9' && j == 'T')
			return true;
		else if (i == 'T' && j == 'J')
			return true;
		else if (i == 'J' && j == 'Q')
			return true;
		else if (i == 'Q' && j == 'K')
			return true;
		else
			return false;
	}
	bool next_step()
	{
 		char temp = _getch();
		if (cur.i < 0)
			cur.i = 0;
		if (cur.j < 0)
			cur.j = 0;
		if (temp == 'w' && cur.i > 0)
			cur.i--;
		else if (temp == 'a' && cur.j > 0)
			cur.j--;
		else if (temp == 's' && cur.i < 10)
			cur.i++;
		else if (temp == 'd' && cur.j < up[cur.i].size() - 1)
			cur.j++;
		else if(temp=='p')
		{
			if (down.size() != 0)
				getnewcard();
		}
		else if (temp == ' ')
		{
			if (sel.ifsel)
			{
				if (up[cur.i].length() == 0||ifisnext(up[sel.i][sel.j], up[cur.i][cur.j]))
				{
					string temp = up[sel.i].substr(sel.j, up[sel.i].length() - sel.j);
					up[sel.i].erase(up[sel.i].begin() + sel.j, up[sel.i].end());
					up[cur.i]+=temp;
					iffull(cur.i);
				}
				sel.ifsel = false;
			}
			else
			{	
				auto it = up[cur.i].begin() + cur.j;
				while (it != (up[cur.i].end() - 1) && ifisnext(*(it + 1), *it))
					it++;
				if (it == (up[cur.i].end() - 1))
				{
					sel.i = cur.i;
					sel.j = cur.j;
					sel.ifsel = true;
				}
			}
			dealwithshow();
		}
		else if (temp == 'e')
		{
			return false;
		}
		if (cur.i == 10)
		{
			cur.j = down.size() - 1;
			cur.i --;
		}
		cur.j = min(cur.j, (int)(up[cur.i].size() - 1));
	}
	void iffull(int i)
	{
		auto& s = up[i];
		if (s.empty())
			return;
		int start = showrecordstrat[i];
		for (int idx = start; idx < (int)s.size() - 1; )
		{
			if (s[idx] == 'K')
			{
				int count = 0;
				while ((idx + count + 1) < (int)s.size() && ifisnext(s[idx + count + 1], s[idx + count]))
				{
					count++;
				}
				if (count >= 12)
				{
					s.erase(idx, count + 1);
					continue;
				}
			}
			idx++;
		}
	}
	void dealwithshow()
	{
		for (int i = 0; i < 10; i++)
		{
			if (up[i].length() <= showrecordstrat[i])
				showrecordstrat[i] = up[i].length()-1;
			if (showrecordstrat[i] < 0)
			{
				showrecordstrat[i] = 0;
			}
		}

	}
	bool ifwin()
	{
		for (int i = 0; i < 10; i++)
		{
			if (up[i].length() != 0)
				return false;
		}
		return true;
	}
	void show()
	{
		system("cls");
		for (int i = 0; i < WEIGHT; i++)
		{
			for (int j = 0; j < up[i].length(); j++)
			{

				if (cur.i == i && cur.j == j) cout << "\033[31m";// 红色文本
				else if (sel.ifsel && sel.i == i && sel.j <= j && j <= up[i].length() - 1) cout << "\033[32m";// 绿色文本
				else cout << "\033[0m";// 恢复默认颜色文本
				if (j < showrecordstrat[i])
					cout << "n";
				else
					cout << up[i][j];

			}
			if (cur.i == i) cout << "\033[31m";// 红色文本
			else cout << "\033[0m";// 恢复默认颜色文本

			if (up[i].length() == 0)
				cout << "t";
			cout << endl;
		}
		for (int i = 0; i < down.size(); i++)
			cout << "\033[0m" << "n";
		//if (cur.i == 10) 
		//	cout << "\033[31m" << "n";

		cout <<endl<< "Controls: w/a/s/d to move, space to select/move cards, p to draw new cards,e to exit." << endl;
	}

};
class Minesweeper
{
public:
	Sel sel;
	Cur cur;
	vector<vector<int>> open; // 0是没开，1是开了,2是标记，
	vector<vector<bool>> bomb;// 0是没有，1是有雷
	vector<vector<int>> count;
	int dir[8][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
	int bombsum = 0;
	int level = 0;
	Minesweeper(int l, int bs) :level(l), bombsum(bs)
	{
		cur = Cur();
		sel = Sel();
		//dir[8][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
		srand(time(0)); // 设置种子
		bomb.resize(level, vector<bool>(level, 0));
		open.resize(level, vector<int>(level, 0));
		count.resize(level, vector<int>(level, 0));
		for (int i = 0; i < bombsum; i++)
		{
			int i1 = rand() % level, j1 = rand() % level;
			if (!bomb[i1][j1])
				bomb[i1][j1] = 1;
		}
		for (int i = 0; i < level; i++)
			for (int j = 0; j < level; j++)
			{
				int bombsum = 0;
				for (int t = 0; t < 8; t++)
				{
					int it = i + dir[t][0];
					int jt = j + dir[t][1];
					if ((it >= 0 && it < level) && (jt >= 0 && jt < level))
						if (bomb[it][jt])
							bombsum++;
				}
				count[i][j] = bombsum;
			}
	}
	void sp(int i, int j)
	{
		open[i][j] = 1;
		if (count[i][j])
		{
			return;
		}
		else
		{
			;
			for (int t = 0; t < 8; t++)
			{
				int it = i + dir[t][0];
				int jt = j + dir[t][1];
				if ((it >= 0 && it < level) && (jt >= 0 && jt < level))
					if (!open[it][jt])
						sp(it, jt);
			}

		}
	}
	bool click()
	{
		char temp = _getch();
		if (temp == 'w' && cur.i > 0)
			cur.i--;
		else if (temp == 'a' && cur.j > 0)
			cur.j--;
		else if (temp == 's' && cur.i < level-1)
			cur.i++;
		else if (temp == 'd' && cur.j < level-1)
			cur.j++;
		else if (temp == 'j')
		{
			if (bomb[cur.i][cur.j])
				return false;
			else
				sp(cur.i, cur.j);
		}
		else if (temp == 'k')
		{
			if (open[cur.i][cur.j] == 0)
				open[cur.i][cur.j] = 2;
			else if (open[cur.i][cur.j] ==2)
				open[cur.i][cur.j] = 0;
		}
		else if(temp== 'e')
		{
			return false;
		}
		return true;
	}
	void show()
	{
		system("cls");
		for (int i = 0; i < level; i++)
		{
			for (int j = 0; j < level; j++)
			{
				if (open[i][j] == 1)
					cout << "\033[32m" ;
				else if (open[i][j] == 2)
					cout << "\033[33m";
				else if (open[i][j] == 0) {
					cout << "\033[0m";
				}
				if (cur.i == i && cur.j == j)
					cout << "\033[31m";// 红色文本
				if (open[i][j] == 1)
					cout << count[i][j] << " ";
				else if (open[i][j] == 2)
					cout <<  "f " ;
				else if(open[i][j]==0) {
					cout << "n ";
				}

			}
			cout << endl;
		}
		cout << endl << "Controls: w/a/s/d to move, j to open, k to flag，e to exit" << endl;
	}
	bool success()
	{
		int flag = 0;
		for (int i = 0; i < level; i++)
			for (int j = 0; j < level; j++)
				if ((open[i][j] == 0) || (open[i][j] == 2 && bomb[i][j] == 1))
					flag++;
		return flag == bombsum;
	}
	void start() {
		int flag = 1;
		while (1)
		{
			show();
			if(!click())
			{
				flag = 0;
				break;
			}
			if (success())
				break;
		}
		system("cls");
		if (flag)
			cout << "\033[32m" << "win";//green
		else
			cout << "\033[31m" << "fail";//red

		cout << "\033[0m";
	}
};
int main()
{
	vector<string> games = { "Spidercard", "Minesweeper" };
	cout << "Welcome to the game!" << endl;
	for (int i = 0; i < games.size(); i++)
	{
		cout << i + 1 << ". " << games[i] << endl;
	}
	cout << "Please enter the game you want to play: ";

	int choice;
	cin >> choice;
	while (1)
	{
		if (choice == 1)
		{
			Spidercard spidercard;
			spidercard.start();
		}
		else if (choice == 2)
		{
			int level;
			int minesum;
			cout << "Please enter the level of Minesweeper (e.g., 10 for 10x10 grid): ";
			cin >> level;
			cout << "Please enter the number of mines: ";
			cin >> minesum;
			Minesweeper minesweeper(level, minesum);
			minesweeper.start();
		}
		cout <<endl<< "Do you want to play again? (y/n): ";
		char again;
		cin >> again;
		if (again == 'y' || again == 'Y')
		{
			cout << "Please enter the game you want to play: ";
			cin >> choice;
		}
		else
		{
			break;
		}
	}
	return 0;
}

