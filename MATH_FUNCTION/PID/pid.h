#ifndef __PID_H__
#define __PID_H__

typedef struct 
{
	int  Ref;   			// Input: Reference input
	int  Fdb;   			// Input: Feedback input
	int  Err;				// Variable: Error
	
	int  Kp;				// Parameter: Proportional gain
	int  Ki;			    // Parameter: Integral gain
	int  Kd; 		        // Parameter: Derivative gain
	
	int  Up;				// Variable: Proportional output
	int  Ui;				// Variable: Integral output
	int  Ud;				// Variable: Derivative output
	int  OutPreSat; 		// Variable: Pre-saturated output
	int  OutMax;		    // Parameter: Maximum output
	int  OutMin;	    	// Parameter: Minimum output
	int  Out;   			// Output: PID output
	int  SatErr;			// Variable: Saturated difference
	int  Kc;		     	// Parameter: Integral correction gain
	int  Up1;		   	    // History: Previous proportional output
	void  (*calc)();	  	// Pointer to calculation function
	void  (*clear)();
} PID;
/*------------------------------------------------------------------------------
Prototypes for the functions in PID.C
------------------------------------------------------------------------------*/
void PidCalc(PID *);
void PidClear(PID *v);

#endif
