#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "functions.h"
//ifstream fin;

bool isRetweet = false;
OrderedHashtagList hashlist;



/* Starter code: used by function printMenu */
void printLine(string msg) {
    cout << msg << endl;
}

/* Starter code: function printMenu() is ready for you */
void printMenu() {
    cout << endl;
    printLine("Welcome to Aggieland Twitter Feeds Stats");
    printLine("The options are:");
    printLine("1. load tweet data file and update stats");
    printLine("2. show overall stats (number of tweets, retweets, and hashtags)");
    printLine("3. show most popular hashtags");
    printLine("9. quit");
    cout << "--------> Enter your option: ";
}

/* Starter code: function to read option from the user is ready for you */
int getOption() {
	int option;
    cin >> option;
    if (cin.fail()) {
	cin.clear();
	cin.ignore(256, '\n');
	return -1;
    } else {
	cin.ignore(256, '\n');
    }
    return option;
}

int main() {
	ifstream fin;
	int user_option;
	int tweets_count = 0;
	int retweets = 0;
	int hashtags = 0;
	string filename;
	string temp_str;
	//vars for option 2
	string line;
	bool isRetweet = false;
	string* array_of_htags;
	int retweet_count = 0;
	
	printMenu();
	user_option = getOption();
	
	while(user_option != 9){
		
		if(user_option == 1){
			cout << "Enter filename: "<< endl;
			cin >> filename;
			fin.open(filename);
			if (!fin) { // error in opening the file
				cout<< "File can't be open." << endl;
			}
			else{
				while(fin.good()){
					getline(fin, temp_str);
					if(temp_str == "\0"){
						break;
					}
					// if not valid tweet continue
					int nb_htags = 0;
					readTweet(temp_str, isRetweet, nb_htags, array_of_htags);
					// for(int i = 0; i <nb_htags; ++i)
						// cout<<array_of_htags[i]<<endl;
					
					tweets_count +=1;
					if(isRetweet == true){
						retweet_count+=1;
					}
					hashtags += nb_htags;
					
					
					for(int i = 0; i < nb_htags; ++i){
						insertHashtag(array_of_htags[i], hashlist);
					}
					
					
					isRetweet = false;
	
					
				}	
				
			fin.close();
			}
		}
		else if(user_option == 2){
			cout << "Tweets: "<< tweets_count << ", Retweets: " << retweet_count << ", Hashtags: " << hashlist.size << endl;
			tweets_count = 0;
		}
		else if(user_option == 3){
			int k = 10;
			if(hashtags == 0){
				cout << "No hashtags." << endl;
			}
			else{
				showMostPopularHashtags(hashlist, k);
			}
		}
		else if(user_option == 9){
			break;
		}
		else{
			cout << "Invalid option" << endl;
		}
		printMenu();
		user_option = getOption();
		
	}
	return 0;    
}