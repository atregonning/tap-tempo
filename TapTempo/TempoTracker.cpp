#include "TempoTracker.hpp"

TempoTracker::TempoTracker(double minimumAllowableBPM, double maximumAllowableBPM)
{
    // Set min/max BPM values from input arguments
    minBPM = minimumAllowableBPM;
    maxBPM = maximumAllowableBPM;
}

void TempoTracker::tap(double currentTimeMs)
{
    tapCount++;
    
    // Set t0 on first tap
    if (tapCount == 1) {
        t0 = currentTimeMs;
        tLast = currentTimeMs;
        return;
    }
    
    //    // Check time since last tap
    if ((currentTimeMs - tLast) > (tapThreshold * 1000)) {
        tapCount = 1;
        currBPM = -1;
        t0 = currentTimeMs;
        tLast = currentTimeMs;
        return;
    }
    
    // Calculate average BPM using elapsed system time since first tap
    currBPM = tapCount / ((currentTimeMs - t0) / 1000 / 60);
    
    // Check BPM is within min/max, set to min (max) if below (above)
    if (currBPM < minBPM) {
        currBPM = minBPM;
    } else if (currBPM > maxBPM) {
        currBPM = maxBPM;
    }
    
    tLast = currentTimeMs;
}

bool TempoTracker::isTempoAvailable()
{
    return (currBPM != -1);
}

double TempoTracker::getTempoAsBeatsPerMinute()
{
    if (currBPM == -1) {
        throw std::out_of_range("No BPM yet\n");
    }
    return currBPM;
}
