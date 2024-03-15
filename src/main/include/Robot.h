#pragma once

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <complex.h>
#include <frc/Timer.h>
#include <string.h>

#include "states.h"
#include "subsystems/Swerve.h"
#include "subsystems/IntakeShooter.h"
#include "subsystems/NoteHandler.h"
#include "subsystems/Climb.h"
#include "subsystems/Limelight.h"
using namespace std;

unsigned int x = 0; // current autoPos setpoint index
float pitch;
float ty;
float tROffset = 0;

struct autoValue
{
	complex<float> pos;
	float angle = 0;
	enum AutoState startingState = AutoState::DRIVING;
};

frc::XboxController controller{0};
frc::Joystick key_pad{1};

frc::Timer timer;

autoValue autoPose[4] = {
	{complex<float>(0, 0), 0, AutoState::AIMING},
	{complex<float>(20,0), 0, AutoState::DRIVING}};



class Robot : public frc::TimedRobot{
public:
	
	void defineTeleopStateFunctions();

	void RobotInit() override;
	void RobotPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;

	void TestInit() override;
	void TestPeriodic() override;

	void SimulationInit() override;
	void SimulationPeriodic() override;

};
