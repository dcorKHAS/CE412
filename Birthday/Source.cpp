#define NUMOFEXP 1000

#include <iostream>

#include <queue>
//https://en.cppreference.com/w/cpp/container/priority_queue

#include <random>
//https://en.cppreference.com/w/cpp/numeric/random
#include <functional>


struct Birthday {

    int day;//1 to 365

   };

// Function to compare events

struct CompareBirthday {

    bool operator()(Birthday const& b1, Birthday const& b2) {

        return b1.day> b2.day;

    }

};
// Priority queue to manage events

int recordSum = 0;

int main() {

    std::default_random_engine generator;
    generator.seed();
    std::uniform_int_distribution<> dayOfTheYear(1, 365);
    
    for (int i = 0; i < NUMOFEXP; i++) {
        std::priority_queue<Birthday, std::vector<Birthday>, CompareBirthday> birthdaySchedule = {};


        
    
        int day = 0; 
        while (true) {
            day++;
            Birthday* newBirthday = new Birthday();
            newBirthday->day = dayOfTheYear(generator);
           // std::cout << newBirthday->day << std::endl;
        

            while (day > newBirthday->day) {

                newBirthday->day+=365;

            }


            birthdaySchedule.push(*newBirthday);
        
            Birthday bd;
            if (!birthdaySchedule.empty()) {
                bd = birthdaySchedule.top();
                if (bd.day == day) {
                    birthdaySchedule.pop();
                    if (birthdaySchedule.top().day == day) {

                        recordSum += ((day - 1) % 365) + 1;
                        break;
                    }

                }
            
            

            }

        }
    }
    std::cout << (double)recordSum / NUMOFEXP << std::endl;
    }




