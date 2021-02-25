#include "Console.h"

using namespace std;

Console console;
Minimap minimap;

const char CDfv[] = "map.txt";
const char CDfv0[] = "map_0.txt";
const char CDfv1[] = "map_1.txt";
const char CDfv2[] = "map_2.txt";
const char CDfv3[] = "map_3.txt";
const char CDfv4[] = "map_4.txt";
const char CDfv5[] = "map_5.txt";
const char CDfv6[] = "map_6.txt";
const char CDfv7[] = "map_7.txt";
const char CDfv8[] = "map_8.txt";
const char CDfvW[] = "world.txt";

bool gamerunning = true;
bool stop = false;
char map[13][21];
char world[16][21];

void Walking();
void Jumping(int information, bool jump, char map[13][21], const char CDfv0[], const char CDfv1[], const char CDfv2[], const char CDfv3[], const char CDfv4[], const char CDfv5[], const char CDfv6[], const char CDfv7[], const char CDfv8[]);

int main() {
	console.Create(map, CDfv);
	while (gamerunning) {
		Jumping(information, jump, map, CDfv0, CDfv1, CDfv2, CDfv3, CDfv4, CDfv5, CDfv6, CDfv7, CDfv8);

		stringstream ss;
		ss << number_of_coins;
		string gold = "Coins: ";
		gold += ss.str();

		system("cls");
		if (stop) {
			for (int i = 0; i < 16; i++) {
				cout << world[i] << endl;
			}
			cout << endl;
		}
		else {
			for (int i = 0; i < 13; i++) {
				cout << map[i] << endl;
			}
			cout << endl;
		}

		cout << "------" << endl;
		cout << "| " << gold << endl;
		cout << "|" << endl;
		cout << "| You have a pickaxe, durability: ";
		for (char const& Durability : Pickaxe) {
			cout << Durability << " ";
		}
		cout << endl;
		set <char> ::iterator itr;
		cout << "| You have these keys: " << endl;
		for (itr = Keys.begin(); itr != Keys.end(); ++itr) {
			cout << "| " << *itr << " ";
		}
		cout << endl;
		cout << "------" << endl;
		//cout << "map[" << y << "][" << x << "]" << endl;
		//cout << information << endl;
		cout << dialog << endl;

		dialog = "";

		system("pause>nul");
		Walking();
	}
	return 0;
}

void Walking() {
	if (stop == false) {
		if (GetAsyncKeyState(VK_UP)) {
			console.Move(-1, 0);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			console.Move(1, 0);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			console.Move(0, 1);
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			console.Move(0, -1);
		}
		if (GetAsyncKeyState(VK_TAB)) {
			stop = true;
			minimap.DrawMinimap(world, CDfvW);
			if (information == 0) world[7][9] = 'X';
			if (information == 1) world[7][15] = 'X';
			if (information == 2) world[11][15] = 'X';
			if (information == 3) world[11][9] = 'X';
			if (information == 4) world[3][15] = 'X';
			if (information == 5) world[3][9] = 'X';
			if (information == 6) world[7][3] = 'X';
			if (information == 7) world[3][3] = 'X';
			if (information == 8) world[11][3] = 'X';
		}
	}
	else {
		if (GetAsyncKeyState(VK_TAB)) {
			stop = false;
		}
	}
}
void Jumping(int information, bool jump, char map[13][21], const char CDfv0[], const char CDfv1[], const char CDfv2[], const char CDfv3[], const char CDfv4[], const char CDfv5[], const char CDfv6[], const char CDfv7[], const char CDfv8[]) {
	if (information == -1 && jump) {
		console.Create(map, CDfv0);
		map[1][1] = '@';
	}
	if (information == 0 && jump) {
		if (y == 11 && x == 3) {
			console.Create(map, CDfv3);
			map[1][3] = '@';
			auto search = Keys.find('x');
			if (search == Keys.end()) map[7][16] = 'x';
			auto search1 = Keys.find('y');
			if (search1 == Keys.end()) map[9][16] = 'y';
		}
		else if (y == 1 && x == 19) {
			console.Create(map, CDfv1);
			map[1][1] = '@';
			if (lever) {
				map[9][11] = '/';
				map[8][18] = ' ';
			}
		}
		else if (y == 3 && x == 0) {
			console.Create(map, CDfv6);
			map[3][18] = '@';
		}
	}
	if (information == 1 && jump) {
		if (y == 11 && x == 18) {
			console.Create(map, CDfv2);
			map[1][18] = '@';
		}
		else if (y == 1 && x == 0) {
			console.Create(map, CDfv0);
			map[1][18] = '@';
		}
		else if (y == 0 && x == 8) {
			console.Create(map, CDfv4);
			map[10][8] = '@';
		}
	}
	if (information == 2 && jump) {
		if (y == 3 && x == 0) {
			console.Create(map, CDfv3);
			map[3][18] = '@';
			auto search2 = Keys.find('x');
			if (search2 == Keys.end()) map[7][16] = 'x';
			auto search3 = Keys.find('y');
			if (search3 == Keys.end()) map[9][16] = 'y';
		}
		else if (y == 0 && x == 18) {
			console.Create(map, CDfv1);
			map[10][18] = '@';
			if (lever) {
				map[9][11] = '/';
				map[8][18] = ' ';
			}
		}
	}
	if (information == 3 && jump) {
		if (y == 0 && x == 3) {
			console.Create(map, CDfv0);
			map[10][3] = '@';
		}
		else if (y == 3 && x == 19) {
			console.Create(map, CDfv2);
			map[3][1] = '@';
		}
	}
	if (information == 4 && jump) {
		if (y == 9 && x == 0) {
			console.Create(map, CDfv5);
			map[9][18] = '@';
			auto search = Keys.find('z');
			if (search == Keys.end()) map[1][1] = 'z';
		}
		else if (y == 11 && x == 8) {
			console.Create(map, CDfv1);
			map[1][8] = '@';
			if (lever) {
				map[9][11] = '/';
				map[8][18] = ' ';
			}
		}
	}
	if (information == 5 && jump) {
		console.Create(map, CDfv4);
		map[9][1] = '@';
	}
	if (information == 6 && jump) {
		if (y == 0 && x == 17) {
			console.Create(map, CDfv7);
			map[10][17] = '@';
			auto search = Keys.find('v');
			if (search == Keys.end()) map[6][11] = 'v';
		}
		else if (y == 3 && x == 19) {
			console.Create(map, CDfv0);
			map[3][1] = '@';
		}
		else if (y == 11 && x == 6) {
			console.Create(map, CDfv8);
			map[1][6] = '@';
		}
	}
	if (information == 7 && jump) {
		console.Create(map, CDfv6);
		map[1][17] = '@';
	}
	if (information == 8 && jump) {
		console.Create(map, CDfv6);
		map[10][6] = '@';
	}
}