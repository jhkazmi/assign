#include "pastgen.h"
void pastgen::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);

maxOutputs=va_arg(parameters,double);	//Max pastes

massMax=va_arg(parameters,double);		//Max mass
massMin=va_arg(parameters,double);		//Min mass
p1Max=va_arg(parameters,double);			//Max p1 time
p1Min=va_arg(parameters,double);			//Min p1 time
p2Max=va_arg(parameters,double);			//Max p2 time
p2Min=va_arg(parameters,double);			//Min p2 time
genMax=va_arg(parameters,double);		//Max ta for output
genMin=va_arg(parameters,double);		//Min ta for output

int seed = (int)time(0)+rand();			//seed for random num lib

sigma=0;											
stor=new StochasticLib1(seed);			//Initilized the lib

//Print summary of the configured parameters
printLog("Paste Generator configured with:\n");
printLog("\tMax Pastes=%g\n", maxOutputs);
printLog("\tMax Mass=%g, Min Mass=%g\n", massMax, massMin);
printLog("\tMax P1=%g,   Min P1=%g\n", p1Max, p1Min);
printLog("\tMax P2=%g,   Min P2=%g\n", p2Max, p2Min);
printLog("\tMax Gen TA=%g,   Min Gen TA=%g\n", genMax, genMin);
printLog("\t----------------------------\n\n\n");

//paste=new Paste();

}
double pastgen::ta(double t) {
//This function returns a double.
//return sigma;

if(maxOutputs>0) return sigma;
else return std::numeric_limits<double>::max();
}
void pastgen::dint(double t) {
//sigma=T;
//sigma=v;
sigma=stor->IRandom(genMin,genMax);


}
void pastgen::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
}
Event pastgen::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

if(maxOutputs-->0)
{
	paste=new Paste();
	paste->mass=stor->IRandom(massMin,massMax);
	paste->p1Time=stor->IRandom(p1Min,p1Max); //sigma;
	paste->p2Time=stor->IRandom(p2Min,p2Max);// /2;

	//return Event(&y,0);
	printLog("[PASTEGEN] Generated paste number %g with mass=%g, p1Time=%g, p2Time=%g\n",
		maxOutputs, paste->mass, paste->p1Time, paste->p2Time);

	return Event(paste, 0);
}
else return Event();

}
void pastgen::exit() {
//Code executed at the end of the simulation.
}
