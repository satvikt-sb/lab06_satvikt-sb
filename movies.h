#include <iostream>
using namespace std;
#include <string>


class movie {
    public:
        movie(string movieName, double movieRating);
        double get_rating() const;
        string get_name() const;
        bool operator<(const movie& mov) const;
    private:
        double rating;
        string name;
};
