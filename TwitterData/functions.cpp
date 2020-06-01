#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"



/* readTweet
 * Parameters:
 *      line: string containing the tweet information received by the function
 *      isRetweet: reference to bool; function will update it with true if retweet
 *      nb_htags: reference to int; function will update with number of hashtags
 *                in the tweet.
 *      array_of_htags: reference to an array of strings; function will allocate
 *                      the array and store the hashtag in it
 * Return value:
 *      none
 * Functionality:
 *     Processes the string in order to find out hashtags and identify if it is Retweet
 * to process the RTs:  ," or , or '  
 */
void readTweet(string line, bool& isRetweet, int& nb_htags, string*& array_of_htags) {		
	int testRTpos;
	testRTpos = line.find_first_of(',');
		if(line[testRTpos+1]== 'R' && line[testRTpos+2] == 'T' && line[testRTpos+3] == ' '){
			isRetweet = true;
		}
		else if(line[testRTpos+1] == '"' && line[testRTpos+2] == 'R' && line[testRTpos+3] == 'T' 
			&& line[testRTpos+4] == ' '){
			isRetweet = true;
		}
	testRTpos = line.find_first_of("'");
		if(line[testRTpos+1]== 'R' && line[testRTpos+2] == 'T'&& line[testRTpos+3] == ' '){
			isRetweet = true;
		}
	
	// for(int i = 0; i != line.size(); ++i){
		// if(line[i] == '#'){
			// nb_htags += 1;
		// }
	// }
	std::stringstream ss{line};
	std::string word;
	
	while(ss >> word){
		
		if(word.find("#") != -1){
			nb_htags += 1;
		}
	}
	array_of_htags = new string[nb_htags]; //allcotate memory
	ss.clear();
	ss.str(line);
	int start_tag = 0;
	int idx = 0;
	while(ss >> word){
		if(word.find("#") != -1){
			start_tag = word.find("#");
			array_of_htags[idx] = word.substr(start_tag);
			
			idx += 1;
		}
	}
	ss.clear();
	ss.str(line);
	
}













/* insertHashtag
 * Parameters:
 *      ht: string
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      true if insertion succeeds, false if memory allocation
 *      fails.
 * Functionality:
 *      See prompt for specification and examples.
 */

    bool insertHashtag(string ht, OrderedHashtagList& hashlist) {
	//first lower string to lower
	
	
	string new_ht;
	for (int i = 0; ht[i] != '\0'; ++i){
		if ((ht[i] >= 'A') && (ht[i] <= 'Z')){
			new_ht += (ht[i] - 'A') + 'a';
		}
		else{
			new_ht += ht[i];
		}
	}
	ht = new_ht;
	//need a case for numbers **working correctly
	
	
	
	Hashtag temp;
	temp.name = ht;
	temp.counter = 0;
	bool inList = false;
	int pos = -1;
	
	for(int i = 0; i < hashlist.capacity; ++i){
		if(temp.name == hashlist.list[i].name){ //if already in the list increase conter
			hashlist.list[i].counter += 1;
			inList = true;
			pos = i;
			//cout << "update this counter 1 new count is:" << hashlist.list[i].counter << endl;
		}
		
	}
		if(inList == false){
			if(hashlist.size == hashlist.capacity){		//if we need to increase the capacity 
				int newCapacity = hashlist.capacity * 2;
				Hashtag* temp_s = new Hashtag[hashlist.capacity * 2]; //doubles capacity 
				// if (temp_s == nullptr) { //to test is memory allocation
					// return false;
				// }
				
				
				for (int j = 0; j < hashlist.capacity; ++j){
					temp_s[j].name = hashlist.list[j].name;
					temp_s[j].counter = hashlist.list[j].counter;
				}
				delete [] hashlist.list;
				hashlist.capacity = newCapacity;
				hashlist.list = temp_s;
			}
			
			hashlist.list[hashlist.size].name = temp.name;
			hashlist.list[hashlist.size].counter += 1;
			pos = hashlist.size;
			hashlist.size += 1;
		}										//need to allocated memory and resize	
		//cout << "counter:" << hashlist.list[i].counter << endl;
		
		
		
	return true;
	
	
	//all hashtags should be added to the list and counters updated at this

}

void orderThaList(OrderedHashtagList& hashlist){
	Hashtag temp;
	int n;
	n = hashlist.size;
	//sorting - Descending ORDER
	for(int i=0;i<n;i++)
	{		
		for(int j = i+1 ;j < n; j++)
		{
			if(hashlist.list[i].counter < hashlist.list[j].counter)
			{
				temp=hashlist.list[i];
				hashlist.list[i]=hashlist.list[j];
				hashlist.list[j]=temp;
			}
		}
	}
		
}
	
	//hashlist.list = new Hashtag[hashlist.capacity];
	

//swap until pos -1 = 0
/* showMostPopularHashtags
 * Parameters:
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      none
 * Functionality:
 *      Prints the k most popular hashtags.
 *      See prompt for formatting details.
 */
void showMostPopularHashtags(OrderedHashtagList hashlist, int k) {
	orderThaList(hashlist);
	if(hashlist.size < k){
		for(int i = 0; i < hashlist.size; ++i){
		cout << "Tag " << hashlist.list[i].name <<" - " << hashlist.list[i].counter << " occurrence(s)" << endl;
		}
	}
	else{
		for(int i = 0; i < k; ++i){
			cout << "Tag " << hashlist.list[i].name <<" - " << hashlist.list[i].counter << " occurrence(s)" << endl;
		}
	}


}