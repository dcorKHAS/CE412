#include <iostream>

#include <queue>
//https://en.cppreference.com/w/cpp/container/priority_queue

#include <random>
//https://en.cppreference.com/w/cpp/numeric/random
#include <functional>



// Define the maximum simulation time

const int MAX_TIME = 100;
bool serverBusy = false;
float numOfCustomer = 0;
float totalWaitingTime = 0;

// Define the structure for events

enum EventType { ARRIVAL, DEPARTURE };



struct Event {

    int time;

    EventType type;

};



// Function to compare events

struct CompareEvent {

    bool operator()(Event const& e1, Event const& e2) {

        return e1.time > e2.time;

    }

};



// Priority queue to manage events

std::priority_queue<Event, std::vector<Event>, CompareEvent> eventQueue;



// Function prototypes

void scheduleEvent(int time, EventType type);

void processArrival(Event e, std::queue<Event>& queue, std::default_random_engine& generator);

void processDeparture(Event e, std::queue<Event>& queue, std::default_random_engine& generator);



int main() {

    std::queue<Event> customerQueue; // Queue to hold waiting customers

    // Server status



    std::default_random_engine generator;
    generator.seed();
    std::exponential_distribution<double> arrivalDistribution(1.0 / 4.5);

    std::normal_distribution<double> serviceDistribution(3.2, 0.6);



    // Schedule the first arrival

    scheduleEvent(arrivalDistribution(generator), ARRIVAL);



    while (!eventQueue.empty() && eventQueue.top().time <= MAX_TIME) {

        Event currentEvent = eventQueue.top();

        eventQueue.pop();



        if (currentEvent.type == ARRIVAL) {

            processArrival(currentEvent, customerQueue, generator);

        }
        else {

            processDeparture(currentEvent, customerQueue, generator);

        }

    }

    float average = static_cast<float>(totalWaitingTime) / static_cast<float>(numOfCustomer);

    std::cout << "Simulation completed.\n Average Waiting time:" << average << std::endl;
    std::cout << totalWaitingTime <<std::endl;
    std::cout << numOfCustomer << std::endl;
    return 0;

}



void scheduleEvent(int time, EventType type) {

    Event newEvent;

    newEvent.time = time;

    newEvent.type = type;

    eventQueue.push(newEvent);

}



void processArrival(Event e, std::queue<Event>& queue, std::default_random_engine& generator) {

    std::exponential_distribution<double> arrivalDistribution(1.0 / 4.5);

    // Schedule next arrival

    scheduleEvent(e.time + arrivalDistribution(generator), ARRIVAL);



    if (!serverBusy) {

        serverBusy = true;

        std::normal_distribution<double> serviceDistribution(3.2, 0.6);

        scheduleEvent(e.time + serviceDistribution(generator), DEPARTURE);

    }
    else {

        queue.push(e);

    }

}



void processDeparture(Event e, std::queue<Event>& queue, std::default_random_engine& generator) {

    if (!queue.empty()) {

        Event customer = queue.front();

        queue.pop();

        std::normal_distribution<double> serviceDistribution(3.2, 0.6);

        scheduleEvent(e.time + serviceDistribution(generator), DEPARTURE);
        totalWaitingTime += e.time - customer.time;
    }
    else {

        serverBusy = false;

    }
    numOfCustomer++;

}