// paste.h
// This will hold our paste structure
#if !defined paste_h
#define paste_h

struct Paste
{
	double mass;		// Mass of the paste
	double p1Time;		// Baking time required in P1
	double p2Time;		// Baking time required in P2
	double bakingCost;	// Baking cost
	
	double tArrival;	// Arrival time at oven
	double tDeparture;	// Departure time (when baked as bread)
};

#endif