#pragma once
enum TeleopState {
    DEFAULT,
    DEFENDING,
    ARMDEFAULT,
    INTAKING,
    NOTEALIGN1,
    NOTEALIGN2,
    NOTEALIGN3,
    AIMING,
    RAMPING,
    SHOOTING,
    AMPTRANSFER,
    TRAPTRANSFER,
    INTAKECLEAR,
    TRAPCLIMBUP,
    TRAPCLIMBDOWN,
    TRAPSCOREREADY,
    WAITINGTOSCORE,
    TRAPSCORE,
    CLIMBUP,
    CLIMBDOWN,
    AMPSCORE,
    AMPOS,
    WAITFORCLIMB,

    NUM_OF_STATES // the number of states: do not remove
};

enum TeleopState teleopState = TeleopState::DEFAULT;
enum TeleopState lastTeleopState = TeleopState::DEFAULT;

// Array of function pointers for state initialization code
void (*init[TeleopState::NUM_OF_STATES])();
// Array of function pointers for the state periodic code
void (*periodic[TeleopState::NUM_OF_STATES])();

void defineTeleopStateFunctions();


enum AutoState {
    ADRIVING,
    AINTAKING,
    AAIMING,
    ARAMPING,
    ASHOOTING,

    ANUM_OF_STATES // the number of states: do not remove
};

enum AutoState autoState = AutoState::ADRIVING;
enum AutoState lastAutoState = AutoState::ADRIVING;

// Array of function pointers for state initialization code
// // void (*init[AutoState::NUM_OF_STATES])();
// Array of function pointers for the state periodic code
// // void (*periodic[AutoState::NUM_OF_STATES])();

void defineAutoStateFunctions();
