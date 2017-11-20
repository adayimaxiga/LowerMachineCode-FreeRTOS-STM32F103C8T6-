#ifndef _KANMAN_FILTER_H
#define _KANMAN_FILTER_H

typedef struct
{
	float X_OptimalPredict;
	float X_LastOptimalEstimate;
	float X_ThisOptimalEstimate;
	
	float P_PrioriCovariance;
	float P_LastCorrectCovariance;
	
	float Q_ProcessedCovariance;
	float R_MeasurementCovariance;
	
	float K_KalmanGain;
	
	float Z_ObservationValue;
	
	float Output;
	
	void (*KalmanFilterCalc)();
}KalmanFilterStruct;

void KalmanFilterCalculate(KalmanFilterStruct *K);


#endif
