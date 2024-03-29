
#include <iostream>
#include <queue>



struct Event {

	float day;
	int type; // 0 for demand 1 for shipment

};
struct CompareEvent {

	bool operator()(Event const& b1, Event const& b2) {

		return b1.day > b2.day;

	}

};
	//Input:
//Environmental parameters/Factors
//Decision variables

	//Reordering point--- number of items
	//Quantity    --- number of items
	// // 
	//Environmental Factors
	//
	//Demand --- Time
	// Interval between demand assuming every customer buys 1
	//       Alternative --- Number of items
	//Delay  --- Time
	//Inventory cost -- Dollars per unit per time
	//Shortage cost -- Dollars per unit

float simulate(	int reorderingPoint,
				int reorderingQuantity, 
				float demandInterval, 
				float delay,
				float inventoryCost, 
				float shortageCost);


int main() {

	// Function to compare events

	




	//Output: Total Cost

	//Measure of quality
	//--Cost/Profit
	//
	//Decision variables
	
	//Shelf-life ===We will not implement -- Time


	//System state variables
	//Inventory level - number of items
	//
	//  
	// 
	// Event Schedule
	// Next demand -- Date
	// Next shipment/order etc. --Date


	//Assume that there is no randomness in the system:








	std::cout << "test";
	





}



float simulate(
	//Decision variables
	int reorderingPoint,
	int reorderingQuantity,
	//Environmental Factors
	float demandInterval,
	float delay,
	float inventoryCost,
	float shortageCost, 
	int currentInventory,
	//Simulation parameters
	float simulationTime

) {

	float time = 0;
	float totalCost = 0;
	std::priority_queue<Event , std::vector<Event>, CompareEvent> eventSchedule = {};
	Event * nextDemand= new Event();
	nextDemand->day = time + demandInterval;
	nextDemand->type = 0;//
	eventSchedule.push(*nextDemand);

	while (!eventSchedule.empty()) {

		Event nextEvent = eventSchedule.top();
		eventSchedule.pop();
		if (nextEvent.type) {

			currentInventory += reorderingQuantity;
		}
		else {

			if (currentInventory) {
				currentInventory--;
				nextDemand = new Event();
				nextDemand->day = time + demandInterval;
				nextDemand->type = 0;//
				eventSchedule.push(*nextDemand);

			}
			else {
				Event* nextShipment= new Event();
				nextShipment->day = time + delay;
				nextShipment->type = 1;//
				eventSchedule.push(*nextShipment);


			}

		}

	}


	return totalCost;
}


