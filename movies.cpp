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
    rating = 0.0;
    name = "";
}

//parameterized constructor
movie::movie(string name, double rating){
    this->name = name;
    this->rating = rating;
}
//rating getter
double movie::get_rating() const{
    return rating;
}

//name getter
string movie::get_name() const{
    return name;
}

//bool operator
bool movie::operator<(const movie& mov) const{
    string other = mov.get_name();

    if (name[0] != other[0]){
        return name[0] < other[0];
    }

    else {
        int ind = 0;
        while (name[ind] == other[ind]){
            ind+=1;
        }
        return name[ind] < other[ind];
    }

}




