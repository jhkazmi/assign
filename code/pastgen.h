//CPP:/random/lib/stocc.cpp
//CPP:/random/lib/randomc.cpp
//CPP:discrete/pastgen.cpp
#if !defined pastgen_h
#define pastgen_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "time.h"
#include "random/lib/randomc.h"
#include "random/lib/stocc.h"
#include "paste.h"
#include "limits"


class pastgen: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;

StochasticLib1 *stor;
Paste* paste;

//Parameters
double maxOutputs;
double massMax, massMin;
double p1Max, p1Min;
double p2Max, p2Min;
double genMax, genMin;




















































public:
	pastgen(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
