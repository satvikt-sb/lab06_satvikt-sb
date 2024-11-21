#include <iostream>
using namespace std;
#include <string>


class movie {
    public:
        movie();
        movie(string name, double rating);
        double get_rating() const;
        string get_name() const;
        bool operator<(const movie& mov) const;
    private:
        string name;
        double rating;
};

