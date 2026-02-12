#include "driver.h"


driver::driver(int pwm_1, int pwm_2, int dir_1, int dir_2, long stepsPerRev){
    _pins.push_back(pwm_1);
    _pins.push_back(pwm_2);
    _pins.push_back(dir_1);
    _pins.push_back(dir_2);
    _stepsPerRev = stepsPerRev;
    
    for(int i = 0; i < 4; i++){
        pinMode(_pins[i], OUTPUT);
    }
}

void driver::set_speed(long stepsPerSecond) {_stepDelay = 1000/(stepsPerSecond); }



//This function coordinates the required direction 1, 2
//and PWM 1 & 2 digital values to step the motor by 'steps'

int driver::step(int steps){
    //initialise vector of connected pins.
    _stepsMoved = 0;
    for(int i = 0; i < 4; i++){
        digitalWrite(_pins[i], 0);
    }

    if(steps > 0){
        _direction = true; //true for motion in positive direction (dependant on chosen motor & wire config)
    }
    else if(steps < 0){
        _direction = false; //false for motion in negative direction.
    }

    while(abs(_stepsLeft > 0)){

        if(_direction){

            //phase 0.5
            digitalWrite(_pins[0], 1);
            for(int i = 1; i < 4; i++){
                digitalWrite(_pins[i], 0);
            }
            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            //phase 1
            digitalWrite(_pins[1], 1);

            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            //phase 1.5
            digitalWrite(_pins[0], 0);
            digitalWrite(_pins[1], 0);
            digitalWrite(_pins[2], 1);
            digitalWrite(_pins[3], 1);

            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            //phase 2
            digitalWrite(_pins[2], 0);

            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);
        }

        if(!_direction){
            digitalWrite(_pins[0], 0);
            digitalWrite(_pins[1], 0);
            digitalWrite(_pins[2], 0);
            digitalWrite(_pins[3], 1);

            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            digitalWrite(_pins[0], 0);
            digitalWrite(_pins[1], 0);
            digitalWrite(_pins[2], 1);
            digitalWrite(_pins[3], 1);

            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            digitalWrite(_pins[0], 1);
            digitalWrite(_pins[1], 1);
            digitalWrite(_pins[2], 0);
            digitalWrite(_pins[3], 0);
        
            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

            digitalWrite(_pins[0], 1);
            digitalWrite(_pins[1], 0);
            digitalWrite(_pins[2], 0);
            digitalWrite(_pins[3], 0);
            
            _stepsMoved++;
            _stepsLeft = steps - _stepsMoved;

            delay(_stepDelay);

        }   
    }
    return _stepsLeft;
}

