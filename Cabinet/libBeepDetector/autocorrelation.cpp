#include "autocorrelation.h"
double AutocorrelationRMS(int offset, std::vector<double> *magnitudeVector)
{
    double squareSum = 0;
    for(int i = 0; i < (static_cast<int>(magnitudeVector->size()) - offset); i++)
    {
        double difference = ((*magnitudeVector)[i] - (*magnitudeVector)[i + offset]);
        squareSum += difference * difference;
    }
    double meanSquare = squareSum / (magnitudeVector->size() - offset);
    double rms = sqrt(meanSquare);
    return rms;
}
