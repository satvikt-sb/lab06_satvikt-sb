// Student name: Satvik Talchuru
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <map>
#include <queue>
#include <sstream>
using namespace std;
#include "utilities.h"
#include "movies.h"


bool parseLine(string &line, string &movieName, double &movieRating);

class sortRating{
    public:
        bool operator()(const movie& other, const movie& otherTitle) const;
};

bool sortRating::operator()(const movie& other, const movie& otherTitle) const {
    if (other.get_rating() == otherTitle.get_rating()) {
        return other.get_name() < otherTitle.get_name();
    }

    return other.get_rating() > otherTitle.get_rating();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);
 
    if (movieFile.fail()) {
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    string line, movieName;
    double movieRating;
    set<movie> movies;

    // Read each file and store the name and rating
    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)) {
        movie movs(movieName,movieRating);
            movies.insert(movs);
    }

    movieFile.close();

    if (argc == 2) {
        for (auto mov : movies){
            cout << mov.get_name() << ", " << mov.get_rating() << endl;
        }
        return 0;
    }

    ifstream prefixFile(argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;

    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    map<string, set<movie, sortRating>> movieMap;
    for(int i = 0; i < prefixes.size(); i++){
        for(auto it = movies.begin(); it != movies.end(); it++){
            if(it->get_name().find(prefixes[i]) == 0 && it->get_name().size() >= prefixes[i].size()){
                movieMap[prefixes[i]].insert(*it);
            }
        }

        if(movieMap[prefixes[i]].empty()){
        cout << "No movies found with prefix " << prefixes[i];
        } else {
        for(auto& movie : movieMap[prefixes[i]]){
            cout << movie.get_name() << ", " << movie.get_rating() << endl;
        }
        }
        cout << endl;
    }

    for(int i = 0; i < prefixes.size(); i++){
        if(movieMap[prefixes[i]].size() != 0){   
            cout << "Best movie with prefix " << prefixes[i] << " is: " << movieMap[prefixes[i]].begin()->get_name() << " with rating " << std::fixed << std::setprecision(1) << movieMap[prefixes[i]].begin()->get_rating() << endl;
        }
    }
    return 0;

}


/* Add your run time analysis for part 3 of the assignment here as commented block*/

//Not sure how to find milliseconds for each input file for prefix_large.txt

//Time Complexity:  O(m *(log(n)+k)+ m+n)
//Explanation:
/*
First, I began by reading through each of the movies and organizing them in
alphabetical order and then printing it. Since I traversed through every movie, 
this has the worst case scenario of n. Then, I iterated through the files
of prefixes and pushed it into an array, having a worst case scenario of m 
because I am traversing through every prefix. Then, I print out the movie 
of each prefix. The outer loop goes through each prefix while the inner 
loop goes through the set of movies to find a matching one using binary
search having the logic of log(n). For this part of the algorithm, the runtime
would be m * (log(n) + k). Lastly, we have to print out the best movie in each prefix and this would
take m times because we have to traverse through each prefix again and this
has a runtime of m. Overall, my algorithm's runtime is O(m * (log(n)+k)+ m+n )

*/

//Space Complexity: O(m + n + m*k + l)
/*
Explanation: Since all the movies are stored in a set for efficient search
and retrieval, this requires O(n) space, where n is the total number of movies.
Next, we have to store all the prefixes in a vector for sequential processing,
so this requires O(m) space, where m is the number of prefixes. 
Then, we have map the prefixes to the movies and for each prefix, the algorithm
maps the prefix to a set of matching movies. This requires O(m * k) space, where
k is the total maximum number of movies matching one prefix. Lastly,
 there has to be storage for strings for movie names and prefixes are also stored, so 
 the total space complexity is O(m + n + m*k + l).
*/

/*

1. 
I designed my algorithm for a low runtime complexity and I think I didn't do that
bad of a job due to the usage of std::set and std::map for storage and 
prefix to movies mapping. These allowed for logarithmic operations for 
insertion and search, greatly increasing my runtime performance while 
eliminating any large runtime terms.

2. 
However, this came at the sacrifice of my spacetime complexity which wasn't 
that satisfactory, but that wasn't one of my goals to start with. I'm not
too sure how to solve this lab with a low runtime and low space complexity 
as well, but utilizing less data types and eliminating redudant iterations
made the space complexity as low as possible.




*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }

    return true;
}


