#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 10; i++)
	{
		scores[i] = 0;
	}
}

void Leaderboard::Read()
{
	// Open file with scores
	std::ifstream input_file("scores.txt");

	// Read the file and update the scores array
	for (int i = 0; i < 10; i++)
	{
		input_file >> scores[i];
	}

	if (!input_file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			scores[i] = 0;
		}
	}

	// Close the file
	input_file.close();
}

int Leaderboard::Update(int new_score)
{
	// Creates a new list to be sorted
	int list_of_scores_to_sort[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

	// Temporary variable that is set to the index of the new score
	int placing;

	// Checks if the score is higher or lower than the highest score
	if (!(new_score > scores[9]))
	{
		return 0;
	}

	for (int i = 0; i < 10; i++)
	{
		list_of_scores_to_sort[i] = scores[i];
	}

	list_of_scores_to_sort[10] = new_score;

	std::sort(std::begin(list_of_scores_to_sort), std::end(list_of_scores_to_sort));

	for (int i = 0; i < 10; i++)
	{
		// Updates the scores array and reverses its order so the highest score is indexed to 1
		scores[i] = list_of_scores_to_sort[10 - i];
		if (scores[i] == new_score)
		{
			placing = i + 1;
		}
	}

	// Returns the index of the score
	return placing;
}

void Leaderboard::Display()
{
	std::cout << "LEADERBOARD:" << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::cout << i + 1 << ". " << scores[i] << std::endl;
	}
}

void Leaderboard::Write()
{
	std::ofstream output_file("scores.txt");

	for (int i = 0; i < 10; i++)
	{
		output_file << scores[i] << " ";
	}

	output_file.close();
}
