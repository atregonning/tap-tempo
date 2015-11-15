//
//  main.cpp
//  TapTempo
//
//  Created by Adrian Tregonning on 30/09/2015.
//  Copyright © 2015 Adrian Tregonning. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <thread>
#include "TempoTracker.hpp"

/**
 * Test client for TempoTracker
 */
int main(int argc, const char * argv[]) {
    
    // Rough tempo for testing tap
    double targetTempo = 120;
    int targetDelay = 1000 * 60.0 / targetTempo;
    
    // Test getTempoAsBeatsPerMinute when 0 or 1 taps have occured
    TempoTracker *t1 = new TempoTracker(80, 200);
    for (int i = 1; i <= 3; i++) {
        try {
            t1->getTempoAsBeatsPerMinute();
        } catch (std::out_of_range e) {
            std::cout << e.what();
        }
        t1->tap(std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::milliseconds(1));
    }
    
    // Test getTempoAsBeatsPerMinute before and after taps have occured
    TempoTracker *t2 = new TempoTracker(80, 200);
    
    if (t2->isTempoAvailable()) {
        std::cout << "Tempo available failed on unavailable BPM.\n";
    }
    t2->tap(std::chrono::system_clock::now().time_since_epoch() /
            std::chrono::milliseconds(1));
    if (t2->isTempoAvailable()) {
        std::cout << "Tempo available failed on unavailable BPM.\n";
    }
    t2->tap(std::chrono::system_clock::now().time_since_epoch() /
            std::chrono::milliseconds(1));
    if (!t2->isTempoAvailable()) {
        std::cout << "Tempo available failed on available BPM.\n";
    }
    
    // Test tap for taps at ~targetTempo BPM,
    // with random timing variations (+/-10 ms)
    TempoTracker *t3 = new TempoTracker(80, 200);
    double tapTime;
    
    for (int i = 1; i <= 3000; i++) {
        int sleepMS = targetDelay + (rand() % 20 - 10);
        
        // Test BPM reset for time lapse
        if (i == 20) {
            sleepMS = 6000;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS));
        tapTime = std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::milliseconds(1);
        t3->tap(tapTime);
        if (t3->isTempoAvailable()) {
            std::cout << "Tap " << i << ", tempo = " <<
            t3->getTempoAsBeatsPerMinute() << "\n";
        }
    }
    
}