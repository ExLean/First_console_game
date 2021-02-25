#include "Console.h"

int x = 8;
int y = 5;
int number_of_coins = 999;
int information = -1;
string dialog = "";
bool jump = false;
bool lever = false;
bool pickaxe = false;
int durability = 3;
set <char> Keys = { 'x', 'y', 'z' };

vector <char> Pickaxe = { '*', '*', '*' };

Console::Console() {}
Console::~Console() {}

Minimap::Minimap() {}
Minimap::~Minimap() {}

void Console::Create(char map[13][21], const char CDfv[]) {
	ifstream Duo(CDfv);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 13; i++) {
		Duo.getline(map[i], 21);
	}
	Duo.close();
}

void Minimap::DrawMinimap(char world[16][21], const char CDfv[]) {
	ifstream Duo(CDfv);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 16; i++) {
		Duo.getline(world[i], 21);
	}
	Duo.close();
}

void Console::Move(int V, int H) {
	// ----------------------------Infomacijos ir zaidejo koordinaciu keitimas---
	if (information == -1 && jump) {
		y = 1; x = 1;
		information = 0;
		jump = false;
	}
	if (information == 0 && jump) {
		if (y == 11 && x == 3) {
			y = 1; x = 3;
			information = 3;
			jump = false;
		}
		else if (y == 1 && x == 19) {
			y = 1; x = 1;
			information = 1;
			jump = false;
		}
		else if (y == 3 && x == 0) {
			y = 3; x = 18;
			information = 6;
			jump = false;
		}
	}
	if (information == 1 && jump) {
		if (y == 11 && x == 18) {
			y = 1; x = 18;
			information = 2;
			jump = false;
		}
		else if (y == 1 && x == 0) {
			y = 1; x = 18;
			information = 0;
			jump = false;
		}
		else if (y == 0 && x == 8) {
			y = 10; x = 8;
			information = 4;
			jump = false;
		}
	}
	if (information == 2 && jump) {
		if (y == 3 && x == 0) {
			y = 3; x = 18;
			information = 3;
			jump = false;
		}
		else if (y == 0 && x == 18) {
			y = 10; x = 18;
			information = 1;
			jump = false;
		}
	}
	if (information == 3 && jump) {
		if (y == 0 && x == 3) {
			y = 10; x = 3;
			information = 0;
			jump = false;
		}
		else if (y == 3 && x == 19) {
			y = 3; x = 1;
			information = 2;
			jump = false;
		}
	}
	if (information == 4 && jump) {
		if (y == 9 && x == 0) {
			y = 9; x = 18;
			information = 5;
			jump = false;
		}
		else if (y == 11 && x == 8) {
			y = 1; x = 8;
			information = 1;
			jump = false;
		}
	}
	if (information == 5 && jump) {
		y = 9; x = 1;
		information = 4;
		jump = false;
	}
	if (information == 6 && jump) {
		if (y == 0 && x == 17) {
			y = 10; x = 17;
			information = 7;
			jump = false;
		}
		else if (y == 3 && x == 19) {
			y = 3; x = 1;
			information = 0;
			jump = false;
		}
		else if (y == 11 && x == 6) {
			y = 1; x = 6;
			information = 8;
			jump = false;
		}
	}
	if (information == 7 && jump) {
		y = 1; x = 17;
		information = 6;
		jump = false;
	}
	if (information == 8 && jump) {
		y = 10; x = 6;
		information = 6;
		jump = false;
	}

	int y2 = y + V;
	int x2 = x + H;
	bool plius = false;

	// ------------------------------Lever---------------------------------------
	if (lever == false && information == 1) {
		if (y2 == 9 && x2 == 11) {
			map[9][11] = '/';
			map[8][18] = ' ';
			lever = true;
		}
	}

	// ------------------------------Shop----------------------------------------
	if (information == 2) {
		if (y2 == 10 && x2 == 16) {
			if (number_of_coins >= 15 && Pickaxe.size() == 0) {
				number_of_coins -= 15;
				Pickaxe = { '*', '*', '*' };
				dialog = "You bought a pickaxe.";
			}
			else dialog = "You don`t have enough coins or you already have a pickaxe.";
		}
		if (y2 == 10 && x2 == 18) {
			if (number_of_coins >= 25) {
				number_of_coins -= 25;
				Keys.insert('t');
				dialog = "You bought a t key.";
			}
			else dialog = "You don`t have enough coins or you already have a pickaxe.";
		}
	}

	// ------------------------------Picking stuff-------------------------------
	if (map[y2][x2] == '*') {
		number_of_coins++;
	}
	if (map[y2][x2] == '+') {
		number_of_coins += 5;
		dialog = "You found a treasure chest!";
	}
	if (map[y2][x2] == 'x') {
		//got_key_x = true;
		Keys.insert('x');
	}
	if (map[y2][x2] == 'y') {
		//got_key_y = true;
		Keys.insert('y');
	}
	if (map[y2][x2] == 'z') {
		//got_key_z = true;
		Keys.insert('z');
	}
	if (map[y2][x2] == 'v') {
		//got_key_v = true;
		Keys.insert('v');
	}

	// ------------------------------Key reikalavimai----------------------------
	if (y2 == 2 && x2 == 8) {
		auto search = Keys.find('x');
		if (information == 1 && search == Keys.end()) dialog = "You need x key.";
	}
	if (y == 2 && x == 8) {
		auto search = Keys.find('x');
		if (search != Keys.end()) map[y2][x] = ' ';
	}
	if (y2 == 9 && x2 == 2) {
		auto searchy = Keys.find('y');
		if (information == 4 && searchy == Keys.end()) dialog = "You need y key.";
	}
	if (y == 9 && x == 2) {
		auto searchy = Keys.find('y');
		if (searchy != Keys.end()) map[y][x2] = ' ';
	}
	if (y2 == 9 && x2 == 6) {
		auto search = Keys.find('v');
		if (information == 6 && search == Keys.end()) dialog = "You need v key.";
	}
	if (y == 9 && x == 6) {
		auto search = Keys.find('v');
		if (search != Keys.end()) map[y2][x] = ' ';
	}
	if (y2 == 2 && x2 == 17) {
		auto search = Keys.find('t');
		if (information == 6 && search == Keys.end()) dialog = "You need t key.";
	}
	if (y == 2 && x == 17) {
		auto search = Keys.find('t');
		if (search != Keys.end()) map[y2][x] = ' ';
	}
	if (y2 == 7 && x2 == 17) {
		auto search = Keys.find('z');
		if (information == 2 && search == Keys.end()) dialog = "You need z key.";
	}
	if (y == 7 && x == 17) {
		auto search = Keys.find('z');
		if (search != Keys.end()) map[y2][x] = ' ';
	}

	// ------------------------------Shop reikalavimai ir pickaxe----------------
	if (y2 == 9 && x2 == 16) {
		if (information == 2) dialog = "You need 15 coins to buy a pickaxe.";
	}
	if (y2 == 9 && x2 == 18) {
		if (information == 2) dialog = "You need 25 coins to buy a t key.";
	}
	if (Pickaxe.size() == 0) {
		if (y2 == 5 && x2 == 9) {
			if (map[5][8] == '>') {
				if (information == 4) dialog = "You need a pickaxe to break it.";
			}
		}
		if (y2 == 3 && x2 == 13) {
			if (map[2][13] == '^') {
				if (information == 4) dialog = "You need a pickaxe to break it.";
			}
		}
		if (y2 == 3 && x2 == 12) {
			if (map[4][12] == '^') {
				if (information == 5) dialog = "You need a pickaxe to break it.";
			}
		}
		if (y2 == 1 && x2 == 6) {
			if (map[1][5] == '>') {
				if (information == 7) dialog = "You need a pickaxe to break it.";
			}
		}
	}
	else {
		if (y == 5 && x == 9) {
			if (information == 4) {
				if (y2 == 5 && x2 == 8) {
					if (map[y2][x2] == '>') Pickaxe.erase(Pickaxe.begin());
				}
				map[y2][x2] = ' ';
				if (Pickaxe.size() == 0) {
					dialog = "Your pickaxe broke. :(";
				}
			}
		}
		if (y == 3 && x == 13) {
			if (information == 4) {
				if (y2 == 2 && x2 == 13) {
					if (map[y2][x2] == '^') Pickaxe.erase(Pickaxe.begin());
				}
				map[y2][x2] = ' ';
				if (Pickaxe.size() == 0) {
					dialog = "Your pickaxe broke. :(";
				}
			}
		}
		if (y == 3 && x == 12) {
			if (information == 5) {
				if (y2 == 4 && x2 == 12) {
					if (map[y2][x2] == '^') Pickaxe.erase(Pickaxe.begin());
				}
				map[y2][x2] = ' ';
				if (Pickaxe.size() == 0) {
					Pickaxe.erase(Pickaxe.begin());
					dialog = "Your pickaxe broke. :(";
				}
			}
		}
		if (y == 1 && x == 6) {
			if (information == 7) {
				if (y2 == 1 && x2 == 5) {
					if (map[y2][x2] == '>') Pickaxe.erase(Pickaxe.begin());
				}
				map[y2][x2] = ' ';
				if (Pickaxe.size() == 0) {
					Pickaxe.erase(Pickaxe.begin());
					dialog = "Your pickaxe broke. :(";
				}
			}
		}
	}

	// ------------------------------Galimybes vaikscioti------------------------
	if (map[y][x2] == ' '
		|| map[y][x2] == '*'
		|| map[y][x2] == '+'
		|| map[y][x2] == 'x'
		|| map[y][x2] == 'y'
		|| map[y][x2] == 'z'
		|| map[y][x2] == 'v') {
		map[y][x] = ' ';
		x = x + H;
		map[y][x] = '@';
	}
	if (map[y2][x] == ' '
		|| map[y2][x] == '*'
		|| map[y2][x] == '+'
		|| map[y2][x] == '_'
		|| map[y2][x] == 'x'
		|| map[y2][x] == 'y'
		|| map[y2][x] == 'z'
		|| map[y2][x] == 'v') {
		map[y][x] = ' ';
		y = y + V;
		map[y][x] = '@';
	}

	// ------------------------------Perejimas is mapu--------------------------
	if (map[y2][x2] == map[7][10] && information == -1) jump = true;
	if (map[y2][x2] == map[1][19] && information == 0) jump = true;
	if (map[y2][x2] == map[11][3] && information == 0) jump = true;
	if (map[y2][x2] == map[3][0] && information == 0) jump = true;
	if (map[y2][x2] == map[11][18] && information == 1) jump = true;
	if (map[y2][x2] == map[1][0] && information == 1) jump = true;
	if (map[y2][x2] == map[0][8] && information == 1) jump = true;
	if (map[y2][x2] == map[3][0] && information == 2) jump = true;
	if (map[y2][x2] == map[0][18] && information == 2) jump = true;
	if (map[y2][x2] == map[0][3] && information == 3) jump = true;
	if (map[y2][x2] == map[3][19] && information == 3) jump = true;
	if (map[y2][x2] == map[11][8] && information == 4) jump = true;
	if (map[y2][x2] == map[9][0] && information == 4) jump = true;
	if (map[y2][x2] == map[9][19] && information == 5) jump = true;
	if (map[y2][x2] == map[3][19] && information == 6) jump = true;
	if (map[y2][x2] == map[11][6] && information == 6) jump = true;
	if (map[y2][x2] == map[0][17] && information == 6) jump = true;
	if (map[y2][x2] == map[11][17] && information == 7) jump = true;
	if (map[y2][x2] == map[0][6] && information == 8) jump = true;
}
/* for (char const& Pickaxe: MyVector) {
	cout << Pickaxe << endl;
}*/