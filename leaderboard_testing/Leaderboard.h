#pragma once

#include <algorithm> // Sorting
#include <fstream> // Reading & writing
#include <iostream> // Writing to console

class Leaderboard
{
public:
	Leaderboard();

	void Read();
	int Update(int new_score);
	void Display();
	void Write();

	int scores[10];
};

