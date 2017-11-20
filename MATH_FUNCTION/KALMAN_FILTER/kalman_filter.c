#include "kalman_filter.h"

void KalmanFilterCalculate(KalmanFilterStruct *K)
{
	//Time Update Equations-----------Predict
	K->X_OptimalPredict = K->X_LastOptimalEstimate;
	K->P_PrioriCovariance = K->P_LastCorrectCovariance + K->Q_ProcessedCovariance;
	
	//Measurement Update Equations---------Correct
	
	K -> K_KalmanGain = K -> P_PrioriCovariance /(K -> P_PrioriCovariance + K -> R_MeasurementCovariance);
	K -> X_ThisOptimalEstimate = K -> X_OptimalPredict + K -> K_KalmanGain * ( K -> Z_ObservationValue - K -> X_OptimalPredict);
	K -> P_LastCorrectCovariance = (1 - K -> K_KalmanGain) * K -> P_PrioriCovariance;
	
	K -> X_LastOptimalEstimate = K -> X_ThisOptimalEstimate ;
	
	K -> Output = K -> X_ThisOptimalEstimate;
}


