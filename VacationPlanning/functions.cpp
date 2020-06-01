# include <iostream>
# include "functions.h"
# include <fstream>
# include "provided.h"
using namespace std;




	/*  Function readPrefs
 *  fileName: c-style String, i.e., array of chars ended by ‘\0’
 *  ngames:   number of games 
 *  prefs:    array of integers created with MAX_NB_GAMES=200
 *            positions
 *  Return value: described below
 
 reads in prefs from file name and stores in pref
 returns number of valid lines present
 game w/o rating is a 0 in array
 problem opening file return -1
 
 for the file
	valid line contains two integers game id from (0- ngames-1) and rating (0-5)
	
 
 
 */


int readPrefs(char fileName[], int ngames, int gamePrefs[]) {
	ifstream fin;
    fin.open(fileName);
	int gameid=0;
	int rating=0;
	int valid_inputs = 0;
	
    if (!fin) { // error in opening the file
		return -1;
    }
	else {
		for (int i = 0; i < ngames ; i++) {
			gamePrefs[i] = 0;
		}
		
		while(!fin.eof()) {
			fin >> gameid;
			fin >> rating;
			while(fin.fail()) {
				fin.clear();
				fin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (fin.good()){
				if (gameid < ngames && (rating >= 0 && rating <= 5)) {
					gamePrefs[gameid] = rating;
				}
			}
		}
	
	}
	
	fin.close();
	for(int i = 0 ; i < ngames ; ++i) {
		if (gamePrefs[i] != 0) {
			valid_inputs += 1;
		}
		
	}
	return valid_inputs;
	
}
	
/*
 Function readPlan
 *  fileName: c-style String, i.e., array of chars ended by ‘\0’
 *  plan:    array of integers created with 365 positions
 *  Return value: as described below
 */
int readPlan(char fileName[], int ngames, int plan[]) {
	ifstream fin;
    fin.open(fileName);
	int gameid=0;
	int day=0;
	
    if (!fin) { // error in opening the file
		return -1;
    }
	else {
		for (int i = 1; i < 366 ; i++) {
			plan[i] = 0;
		}
		
		while(!fin.eof()) {
			fin >> day;
			fin >> gameid;
			while(fin.fail()) {
				fin.clear();
				fin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (fin.good()){
				plan[day] = gameid;
			}
		}
		return 0;
	}
	
}




/*  Function computeFunLevel
 *  start:  first day of the vacation (1 <= start < 365)
 *  duration: number of vacation days (duration >= 1)
 *  gamePrefs: gamePrefs[k] indicates the rating specified for game k
 *  ngames: number of elements in the array gamePrefs
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  Return value: Explained below. 
 */
int computeFunLevel (int start, int duration, int gamePrefs[], int ngames, int plan[]) {
	int localfunarray[400];
	int sum_val = 0;
	int gameid = 0;
	int rating = 0;
	
	if(365 - start < duration) {
		return -1;
	}
	
	else {
		for(int day = 1 ; day < 366 ; ++day ) {
			gameid = plan[day];
			rating = gamePrefs[gameid];
			localfunarray[day] = rating;
		}
		
		//gamePrefs[gameid] = rating
		//plan[day]=gameid
		// i want the rating per day
		for(int i = start; i < start + duration; ++i) {
			sum_val += localfunarray[i]; 
		}
		
	
	}
	
	return sum_val;
}



/*  Function findBestVacation
 *  duration: number of vacation days
 *  gamePrefs: gamePrefs[k] indicates the rate specified for game k
 *  ngames: number of elements in the array gamePrefs
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  Return value: Explained below. 
 */
int findBestVacation (int duration,  int gamePrefs[], int ngames, int plan[]){
	int curr_max = 0;
	int start_date = 0;
	int local[400];
	int sum_val = 0;
	int gameid = 0;
	int rating = 0;
	
	

	for(int day = 1 ; day < 366 ; ++day ) {
		gameid = plan[day];
		rating = gamePrefs[gameid];
		local[day] = rating; 
	}
		
		//gamePrefs[gameid] = rating
		//plan[day]=gameid
		// i want the rating per day
	
	
	
	for(int i = duration; i < 366 ; ++i) {
		for(int j = 0 ; j < duration; ++j) {
			sum_val += local[i-j];
			//cout << sum_val << endl;
		}
		if (sum_val > curr_max) {
			curr_max = sum_val;
			start_date = i+1-duration;
		}
		sum_val = 0;
	}
	return start_date;
}
	

