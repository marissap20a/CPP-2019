#include <iostream>
#include <fstream>
#include "functions.h"
#include "provided.h"
using namespace std;

int main() {
	int ngames;
	int duration;
	/*
	char correctPlan[MAX_TITLE_SIZE] = "plan.txt";
	char correctPrefs[MAX_TITLE_SIZE] = "prefs.txt";
	char correctTitles[MAX_TITLE_SIZE] = "game-titles.txt";
	*/
	int x;
	int y;
	int z;
	int start;
	
	char titlesFile[MAX_TITLE_SIZE];
	char prefsFile[MAX_TITLE_SIZE];
	char planFile[MAX_TITLE_SIZE];
	
	char gameTitles[MAX_NB_GAMES][MAX_TITLE_SIZE];
	int gamePrefs[MAX_TITLE_SIZE];
	int plan[MAX_TITLE_SIZE];
	
	//bool istitles = true;
	//bool isprefs = true;
	//bool isplan = true;
	
	cout << "Please enter ngames and duration: ";
	cin >> ngames >> duration;
	
	if (ngames > MAX_NB_GAMES || ngames < 0 || duration < 0 || duration > 365) {
		cout << "Invalid input." << endl;
	}
	else {
		cout << "Please enter name of file with titles: ";
		cin >> titlesFile;
		cout << "Please enter name of file with preferences: ";
		cin >> prefsFile;
		cout << "Please enter name of file with plan: ";
		cin >> planFile;
		
		
		
		x= readPrefs(prefsFile, ngames, gamePrefs);
		y= readGameTitles (titlesFile, ngames, gameTitles);
		z =readPlan(planFile, ngames, plan);
		start = findBestVacation (duration, gamePrefs, ngames, plan);
		computeFunLevel (start, duration, gamePrefs, ngames, plan);
		
		
		if (x == -1 || y == -1 || z == -1) {
			cout << "Invalid file." << endl;
			return 1;
		}
		else {
			readPrefs(prefsFile, ngames, gamePrefs);
			cout << "Best start day is " << start << endl;
			cout << "Games to be played:" << endl;
			readGameTitles (titlesFile, ngames, gameTitles);
			printGamesPlayedInVacation(start, duration, plan, gameTitles, ngames);
		}
		
		
	}
	return 0;

}




