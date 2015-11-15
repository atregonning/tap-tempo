#ifndef __TempoTracker_INCLUDE__
#define __TempoTracker_INCLUDE__

# include <chrono>
# include <stdexcept>
# include <iostream>

/**
 * This class tracks tempo values that are tapped in.
 *
 * The BPM is the average of all taps, unless a 5 second long break occurs,
 * in which case the count is reset.
 * The value is bounded by an upper and lower threshold set by parameters passed
 * to the constructor.
 *
 * @author      Adrian Tregonning
 * @version     1.0, 9/30/15
 */
class TempoTracker
{
public:
    
    /**
     * The constructor takes two parameters which should
     * constrain the BPM value.
     *
     * @param minimumAllowableBPM   Lowest allowable BPM. Anything lower
     defaults to this
     * @param maximumAllowableBPM   Highest allowable BPM. Anything higher
     *                              defaults to this
     */
    TempoTracker(double minimumAllowableBPM, double maximumAllowableBPM);
    
    /**
     * Called when the user taps on a button.
     *
     * @params currentTimeMs current System time in ms
     */
    void tap(double currentTimeMs);
    
    /**
     * Return whether a tempo value is available.
     *
     * @returns <tt>true</tt> if a tempo is available (i.e. more than two taps
     have occured); <tt>false</tt> if otherwise
     */
    bool isTempoAvailable();
    
    /**
     * Return the tempo in BPM.
     *
     * @returns Latest BPM value
     * @throws  std::out_of_range if no tempo is available
     */
    double getTempoAsBeatsPerMinute();
    
private:
    const double tapThreshold = 5;  // Tempo resets if no taps in this time
    double minBPM, maxBPM;          // Minimum and maximum allowed BPM values
    double t0, tLast;               // Time of first and previous taps (in ms)
    double currBPM = -1;            // BPM at most recent tap, -1 = no taps
    int tapCount = 0;               // Number of taps since instantiation
};

#endif
