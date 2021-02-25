#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once

#include "Windows.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Console {
protected:
	char world[16][21];
public:
	Console();
	~Console();
	void Create(char map[13][21], const char CDfv[]);
	void Move(int V, int H);
};

class Minimap : public Console {

public:
	Minimap();
	~Minimap();
	void DrawMinimap(char world[16][21], const char CDfv[]);
};

extern char map[13][21];
extern int x;
extern int y;

extern int information;
extern bool jump;

extern set <char> Keys;
extern vector <char> Pickaxe;

extern int number_of_coins;
extern bool lever;
extern int durability;
extern string dialog;
#endif