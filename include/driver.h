#ifndef DRIVER_H
#define DRIVER_H

#include <Arduino.h>
#include <vector>

class driver{
    public:

    driver(int Pin_A, int Pin_B, int Pin_C, int Pin_D, long stepsPerRev);
    void set_speed(long stepsPerSecond);
    void step(int steps);

    private:
    long _stepsPerRev;
    long _stepsPerSecond;
    std::vector<int> _pins;
    bool _direction;
    int _stepsLeft;
    int _stepsMoved;
};

#endif
