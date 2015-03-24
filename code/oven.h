//CPP:discrete/oven.cpp
#if !defined oven_h
#define oven_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "paste.h"
#include "list"
#include "iostream"
#include "limits"


class oven: public Simulator { 
// Declare the state,
// output variables
// and parameters


// Clock
double clock;

//List of paste waiting
std::list <Paste*> pasteQueue;

Paste* bread;

//Time oven is utalized (P<>0)
double tUtilized;

//Current oven state (0, 1, 2)
int processState;
int processed;

double p1Cost, p2Cost, totalCost;
double waitingTime;
int sendOutput;



































































public:
	oven(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
