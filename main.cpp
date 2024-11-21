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
    vector<string> no_results;
    vector<multimap<double,movie,greater<double>>> prefix_vector; 

    
    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    multimap<double,movie,greater<double>> pref;
    for (string prefix : prefixes){
        string upper_bound_prefix = prefix;
        upper_bound_prefix.back()++;

        auto lower = movies.lower_bound(movie(prefix, 0));
        auto upper = movies.lower_bound(movie(upper_bound_prefix, 0));

        for (auto it = lower; it != upper; ++it) {
            if (prefix_checker(it->get_name(), prefix)) {
                pref.insert({it->get_rating(), *it});
            }
        }
        prefix_vector.push_back(pref); 

        if (pref.empty()) {
            no_results.push_back(prefix); 
        } 

        pref.clear();
    }
    
    print_results(prefixes, no_results, prefix_vector);
    return 0;
}


void print_results(vector<string> prefixes, vector<string> no_results, vector<multimap<double,movie,greater<double>>> prefix_vector){
    int j = 0;
    for (int i = 0; i < prefix_vector.size(); i++){
        multimap<double,movie,greater<double>> pref = prefix_vector.at(i);
        
        if (pref.empty()){
            cout << "No movies found with prefix "<< no_results.at(j) << endl;
            j++;
            continue;
        }

        for (auto it = pref.begin(); it != pref.end(); it++){
            movie mov = it->second;

            cout << mov.get_name() << ", " << mov.get_rating() << endl;
        }

        cout << endl;
    }

    for (int i = 0; i < prefix_vector.size(); i++){
        multimap<double,movie,greater<double>> pref = prefix_vector.at(i);
        
        if (pref.empty()){
            continue;
        }

        for (auto it = pref.begin(); it != pref.end(); it++){
            movie mov = it->second;
            cout << "Best movie with prefix " << prefixes.at(i) << " is: " << mov.get_name() << " with rating " << std::fixed << std::setprecision(1) << mov.get_rating() << endl;
            break;
        }
    }
}

bool prefix_checker(const string& movString, const string& prefix) {
    if (movString.length() < prefix.length()) {
        return false;
    }

    for (int i = 0; i < prefix.length(); ++i) {
        if (movString[i] != prefix[i]) {
            return false;
        }
    }

    return true;
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

