#pragma once

#include <AHRS.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/SwerveModule.h"

using namespace std;

class Swerve{
public:
    void set(complex<float> velocity, float turnRate){
        angle = gyro.GetYaw()*-(M_PI/180);
        targetVelocity = velocity;

        // robot orient the velocity
        velocity *= polar<float>(1, -angle);

        // find fastest module speed
        float fastest = 1;
        for (Module module : modules){
            float speed = abs(module.getVelocity(velocity, turnRate));
            if (speed > fastest){
                fastest = speed;
            }
        }

        // move current velocity toward target
        targetVelocity /= fastest;
        turnRate /= fastest;
        complex<float> velError = targetVelocity-currentVelocity;
        float turnRateError = turnRate - currentTurnRate;
        if (abs(velError) > slewRate) {
            velError *= slewRate/abs(velError);
        }
        if (abs(turnRateError) > slewRate) {
            turnRateError *= slewRate/abs(turnRateError);
        }
        currentVelocity += velError;
        currentTurnRate += turnRateError;
        targetVelocity = currentVelocity * polar<float>(1, -angle);

        // set modules
        for (Module module : modules){
            module.set(targetVelocity, currentTurnRate);
        }
    }
    void SetPosition(complex<float> position){
        posSetpoint = position;
    }
    void SetAngle(float angle) {
        angleSetpoint = angle;
    }
    bool GetPositionReached(float tolerance = 1) {
        return abs(posError) < tolerance;
    }
    bool GetAngleReached(float tolerance = 3) {
        return abs(angleError) < tolerance;
    }
    void RunPID() {
        // calculate PID Response
        angle = gyro.GetYaw()*-(M_PI/180);
        posError = posSetpoint-pos;
        angleError = angleSetpoint-angle;
        am::limit(angleError);
        complex<float> posPIDoutput = posError*polar<float>(0.025, 1);
        float anglePIDoutput = angleError*0.2;
        if (abs(posPIDoutput) > 0.3) {
            posPIDoutput *= 0.3 / abs(posPIDoutput);
        }
        if (abs(anglePIDoutput) > 0.5) {
            anglePIDoutput *= 0.5 * abs(anglePIDoutput);
        }
        // robot orient the velocity
        posPIDoutput *= polar<float>(1, -angle);
        // find fastest module speed
        float fastest = 1;
        for (Module module : modules){
            float speed = abs(module.getVelocity(posPIDoutput, anglePIDoutput));
            if (speed > fastest){
                fastest = speed;
            }
        }
        posPIDoutput /= fastest;
        anglePIDoutput /= fastest;
        // calculate odometry and set modules
        complex<float> posChange = complex<float>(0, 0);
        for (Module module : modules){
            module.set(targetVelocity, currentTurnRate, true);
            posChange += module.getPositionChange();
        }
        pos += posChange * polar<float>(0.25, angle);
    }

    void init(){
        for (Module module : modules){
            module.init();
        }
    }
private:
    AHRS gyro{frc::SPI::Port::kMXP};
    Module modules[4] = {
        Module{1, complex<float>(1, 1)},
        Module{2, complex<float>(-1, 1)},
        Module{3, complex<float>(1, -1)},
        Module{4, complex<float>(-1, -1)}
    };

    complex<float> pos = complex<float>(0, 0);
    float angle;

    complex<float> posSetpoint;
    complex<float> posError;
    float angleSetpoint;
    float angleError;

    complex<float> currentVelocity;
    float currentTurnRate = 0;
    complex<float> targetVelocity;

    const float slewRate = 0.04;
};
