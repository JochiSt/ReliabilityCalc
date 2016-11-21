#include "utils.h"
#include <cmath>

float utils::FIT2FailureRate(float FIT, float deviceHours){
	return 1. - exp( -1. * FIT / 1E9 * deviceHours);
}
float utils::FailureRate2FIT(float failureRate, float deviceHours){
	return -1. * log(1. - failureRate) / deviceHours * 1E9;
}
