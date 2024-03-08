#include <iostream>

#include <queue>

#include <random>

#include <functional>


//How to make the same code work for 2 servers with identical service time distribution?
// 
// 
// 
// Define the maximum simulation time

const int MAX_TIME = 100;
bool serverBusy[2] = { false, false};
//int serverBusyCount = 0; // 0 or 1 or 2

// Define the structure for events

enum EventType { ARRIVAL, DEPARTURE};



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



    std::cout << "Simulation completed." << std::endl;

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

    std::normal_distribution<double> serviceDistribution(3.2, 0.6);

    //This  model cannot estimate for what fraction of time each server is busy
    //but it can correctly estimate the waiting time for the customers
    //Why?

    if (!serverBusy[0] && !serverBusy[1]) {

        //The servers are identical, so we can choose either one


        serverBusy[0] = true;

        scheduleEvent(e.time + serviceDistribution(generator), DEPARTURE);

    }
    else if (serverBusy[0] && serverBusy[1]){

        queue.push(e);

    }
    else {//one busy one not

        serverBusy[1]= true;
        
        scheduleEvent(e.time + serviceDistribution(generator), DEPARTURE);


    }

}



void processDeparture(Event e, std::queue<Event>& queue, std::default_random_engine& generator) {

    if (!queue.empty() ) {

        Event customer = queue.front();

        queue.pop();

        std::normal_distribution<double> serviceDistribution(3.2, 0.6);

        scheduleEvent(e.time + serviceDistribution(generator), DEPARTURE);

    }
    else if (queue.empty() && serverBusy[1]){

        serverBusy[1] = false;

    }
    //else if (queue.empty() && !serverBusy[1])
    else {
        serverBusy[0] = false;
    }

}