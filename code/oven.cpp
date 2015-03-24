#include "oven.h"
void oven::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

p1Cost=va_arg(parameters,double);
p2Cost=va_arg(parameters,double);

clock=0;			// Reset the clock
tUtilized=0;		// Reset

processState=0;
totalCost=0;
sendOutput=0;
processed=0;
waitingTime=0.0;


printLog("Oven Initilized clock=%g, state=%d\n", clock, processState, t);
printLog("\tConfigured with p1Cost=%g, p2Cost=%g\n================================================\n\n", p1Cost, p2Cost);

}
double oven::ta(double t) {
//This function returns a double.
// The Time Advance is a non-negative real number saying how long the system remains in a given state in absence of input events
// If there is no paste to be baked, then wait
// for a long time
//if(pasteQueue.empty()){
//	if(processState==0)
//	printLog("[OVEN]->[TA] No paste to bake, waiting for the paste INF (state=%d)\n", processState);
//	return std::numeric_limits<double>::max();
//}

// If there is paste to be baked and/or being baked
// then check the processState and retrun the time
// accordingly.

double sigma;

switch(processState){
	case 0:		// We should never arrive here!
		if(pasteQueue.empty()){
			printLog("[OVEN]->[TA] No paste to bake, waiting for the paste INF (state=%d)\n", processState);		
			sigma=std::numeric_limits<double>::max();
		}
		else sigma=pasteQueue.front()->p1Time;
		break;
	case 1:		// processState1
		sigma=pasteQueue.front()->p1Time;
		break;
	case 2:		// processState2
		sigma=pasteQueue.front()->p2Time;
		break;
	default:	// an invalid state
		sigma=std::numeric_limits<double>::max();
}

//sigma+=clock;
if(!t==0) printLog("[OVEN]->[TA] clock=%g, state=%d, sigma=%g\n", clock, processState,sigma);

return sigma;

}
void oven::dint(double t) {
int dummy;

clock+=ta(0);		//Update clock

switch(processState){
	case 0:
		if(!pasteQueue.empty()) dummy=1;
		else dummy=0;
	case 1:
		dummy=2;
		break;
	case 2:
		sendOutput=1;	
		bread = pasteQueue.front();			
		//beingBakedPaste=pasteQueue.front();
		if(pasteQueue.empty()) { dummy=0; }
		else {
			dummy=1;			
		}
		pasteQueue.pop_front();
		break;	
}
processState=dummy;

printLog("[OVEN]->[INT] clock=%g, New state=%d\n", clock, processState);

}
void oven::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

// update the clock
clock += e;

if(processState==0){
	processState=1;	
}

pasteQueue.push_back((Paste*)x.value);
pasteQueue.back()-> tArrival = clock;

//beingBakedPaste = 
printLog("[OVEN]->[EXT] at clock=%g, New paste addedd.\n", clock);
printLog("\t[EXT] Queue length is %d.\n", pasteQueue.size());
}
Event oven::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

if(sendOutput==1){

	sendOutput=0;
	processed++;

	//Paste* bread = pasteQueue.front();

	bread->tDeparture=clock;
	bread->bakingCost = (bread->p1Time * p1Cost) + (bread->p2Time * p2Cost);
	totalCost += bread->bakingCost;
	waitingTime += bread->tDeparture-bread->tArrival;

	printLog("[OVEN]->[OUTPUT] clock=%g, Mass=%g, p1Time=%g, p2Time=%g, Cost=%g, Accumulated Cost=%g, tArrival=%g, tDepart=%g, tWait=%g\n", 
			clock, bread->mass, bread->p1Time, bread->p2Time, bread->bakingCost,totalCost, bread->tArrival, 
			bread->tDeparture, bread->tDeparture-bread->tArrival);

	printLog("\t[OUTPUT] Queue length is %d.\n", pasteQueue.size());	
	
	return Event(bread, 0);
}
else{
	return Event();
}

}
void oven::exit() {
//Code executed at the end of the simulation.
printLog("==================OVEN===========================\n");
printLog("\tClock=%g", clock);
printLog("\tAccumulate Cost = %g\n", totalCost);
printLog("\tAverage Waiting Time = %g\n", waitingTime/processed);
printLog("\tPastes Processed = %d\n", processed);
printLog("=============================================\n");
}
