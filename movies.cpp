#include "movies.h"
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
#include <queue>
#include <sstream>

//constructor
movie::movie(string movieName, double movieRating){
    name = movieName;
    rating = movieRating;
}

//rating getter
double movie::get_rating() const{
    return rating;
}

//name getter
string movie::get_name() const{
    return name;
}

bool movie::operator<(const movie& other) const{
    return name < other.get_name();
}