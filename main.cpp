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
            cout << "Best movie with prefix " << prefixes[i] << " is: " << movieMap[prefixes[i]].begin()->get_name() << " with rating " << std::fixed << std::setprecision(1) << movie_map[prefixes[i]].begin()->get_rating() << endl;
        }
    }
    return 0;
}


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }

    return true;
}


/* Add your run time analysis for part 3 of the assignment here as commented block*/

