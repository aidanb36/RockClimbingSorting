//
// Aidan Brown
//

#ifndef CLIMBING_PROJECT_H
#define CLIMBING_PROJECT_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/**CLIMBING CLASS
 * This class represents a list of 1000 of the highest rated and most popular rock climbing routes in the United States
 * I retrieved this data from a site called "Mountain Project," feel free to take a look!
 *
 * Fields:
 *  route: the name of each climbing route, a string
 *  location: the string location of each route, broken up into sections using (>), for example--UVM>Burlington>Vermont
 *  stars: the star review given by the general public on Mountain Project, scale of 1-5, this is a double
 *  rating: the pure difficulty of the route, this is a string because it contains both numbers and letters occassionally
 *      an example-5.10 B, this ranges from 5.7 to 5.10, with letters being increments between
 *  pitches: the length of the route, an integer, broken up into segments called a pitch, a standard pitch is usually
 *      between the lengths of 60 and 70 meters, my calculation in Main() uses this
 */


//climbing class
class Climbing {
//private
private:
    std::string route, location, rating;
    int pitches{}, rowId{};
    double stars{};

    //public
public:
    //no variables, default
    Climbing(){

    }

    //constructor
    //order matters, from main
    Climbing(std::string route, std::string location, double stars, std::string rating, int pitches, int rowId){
        this->route = route;
        this->location = location;
        this->stars = stars;
        this->rating = rating;
        this->pitches = pitches;
        this->rowId = rowId;

    }
        //getters
        int getPitches() const {
            return pitches;
        }

        std::string getLocation() const {
            return location;
        }

        std::string getRoute() const {
            return route;
        }

        std::string getRating() const {
            return rating;
        }

        double getStars() const {
            return stars;
        }
        int getRowId() const {
            return rowId;
        }

        //setters
        void setPitches(int pitches) {
            this->pitches = pitches;
        }

        void setLocation(std::string location) {
            this->location = location;
        }

        void setRoute(std::string route) {
            this->route = route;
        }

        void setRating(std::string rating) {
            this->rating = rating;
        }

        void setPitches(double stars) {
            this->stars = stars;
        }

        void setRowId(int rowId) {
            this->rowId = rowId;
        }





    //format of the print operations
    //using friend, defined outside of scope, can still use variables
    friend std::ostream &operator<<(std::ostream &outs, const Climbing &cObj) {
        //outs-fixed
        //what will be printed
        outs << std::fixed
             << std::right
             << std::setprecision(4)
                //for clarity i want to print titles for each value from the csv
                //for example...route: the nose
             <<"route: "<<std::setw(2) << cObj.getRoute()
             <<"  |location: "
             << std::setw(5) << cObj.getLocation()
             << std::left
             << "  "
             <<"  |stars: "
             << std::setw(5) << cObj.getStars()
             <<"  |rating: "
             << std::setw(5) << cObj.getRating()
             <<"  |pitches: "
             << std::setw(5) << cObj.getPitches()
             << std::setw(5)<<cObj.getRowId();
        return outs;
    }
    /**
    * Overload < operator for object comparison
    */
    friend bool operator < (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() < rhs.getRowId();
    }

    /**
     * Overload > operator for object comparison
     */
    friend bool operator > (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() > rhs.getRowId();
    }

    /**
     * Overload <= operator for object comparison
     */
    friend bool operator <= (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() <= rhs.getRowId();
    }

    /**
     * Overload >= operator for object comparison
     */
    friend bool operator >= (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() >= rhs.getRowId();
    }

    /**
     * Overload == operator for object comparison
     */
    friend bool operator == (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() == rhs.getRowId();
    }


    /**
     * Overload != operator for object comparison
     */
    friend bool operator != (const Climbing& lhs, const Climbing& rhs) {
        return lhs.getRowId() != rhs.getRowId();
    }


};

//from the file, with the climbing csv file
//create vector with climbing objects
bool loadFromFile(std::string fn, std::vector<Climbing> & objs) {
        //open up the file, climbing.csv
        std::ifstream fin;
        fin.open(fn);

        //if the infile does not exist or cannot be openned, return false
        if (!fin) {
            // Bad file / could not open
            return false;
        }


        //if the file works, and is good, use peek before end of file
        while (fin && fin.peek() != EOF) {
            //set values for all five, invalid for strings, and negative 1 for numericals
            std::string route = "INVALID";
            std::string location = "INVALID";
            std::string rating = "INVALID";
            double stars = -1.0;
            int pitches = -1;
            int rowId = -1;

            //comma char, will make it easy to use repeatedly
            char comma = ',';

            //use getLine to get each value, separated by commas
            //if a string use parantheses method
            getline(fin, route, comma);
            getline(fin, location, comma);
            //numbers can be done just with carrots
            fin >> stars;
            fin >> comma;
            getline(fin, rating, comma);
            fin >> pitches;
            fin>>comma;
            //if next value in file is not cairrage return or new line, pitches is the value
            if (fin.peek() != '\r' && fin.peek() != '\n') {
                fin >> rowId;
            }

            //destination is the collection of variables, push back
            Climbing destination(route, location, stars, rating, pitches, rowId);
            objs.push_back(destination);
        }
        //close fin
        fin.close();
        return true;
    }





#endif
