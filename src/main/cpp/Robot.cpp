// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "math.h"

using namespace std;

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {
  if (swerve.setPos(autoPos[x].pos, autoPos[x].angle) && x < size(autoPos)-1){
    if (i == x) {
      time.Restart();
      i++;
    }
    if (time.HasElapsed(autoPos[x].holdTime)) {
      x++;
    }
  }
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  complex<float> velocity = complex<float>(-controller.GetLeftY(), -controller.GetLeftX());
  float turnRate = -controller.GetRightX()*0.3;
  swerve.set(velocity, turnRate);
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
