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
movie::movie(){
    name = "";
    rating = 0.0;
}

//parameterized constructor
movie::movie(string name, double rating){
    this->name = name;
    this->rating = rating;
}

//name getter
string movie::get_name() const{
    return name;
}
//rating getter
double movie::get_rating() const{
    return rating;
}

//bool operator
bool movie::operator<(const movie& mov) const{
    string other_title = mov.get_name();

    if (name[0] != other_title[0]){
        return name[0] < other_title[0];
    }

    else {
        int ind = 0;
        while (name[ind] == other_title[ind]){
            ind += 1;
        }
        return name[ind] < other_title[ind];
    }

}




