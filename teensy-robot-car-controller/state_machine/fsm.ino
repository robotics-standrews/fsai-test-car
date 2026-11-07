


enum states {
    AS_OFF,
    AS_READY,
    EMERGENCY_BRAKE,
    AS_DRIVING,
    AS_FINISHED
};


// use these to access a bit array of
// true or false values to determine state switch
enum transition_criteria {
    AS_MASTER_SWITCH_ON,
    TS_MASTER_SWITCH_ON,
    MISSION_STATUS_SELECTED,
    MISSION_STATUS_FINISHED,
    ALL_WHEEL_LESS_THAN_10_RPM,
    FRONT_AXLE_TORQUE_REQ_0,
    REAR_AXLE_TORQUE_REQUEST_0,
    STEER_ANGLE_LESS_THAN_5,
    DIRECTION_REQUEST_NEUTRAL,
    GO_SIGNAL_ON,
    SDC_OPEN,
    AI_ESTOP_REQ,
    AI_COMMS_LOST_FAULT,
    MISSION_STATUS_FAULT,
    AUTONOMOUS_BRAKING_FAULT,
    BRAKE_PLAUSIBILITY_FAULT,
    BMS_FAULT,
    EBS_ARMED,
    EBS_UNAVAILABLE,
    EBS_TIMER_15_SEC,
    FIVE_SECOND_TIMER_PASSED,
};

// change enum based on last value in the transition_criteria enum, 
// to get bitarray with one index for each enum.
char* transition_bools[FIVE_SECOND_TIMER_PASSED + 1];

typedef struct FSM {
    int state;
} FSM;


int get_state(int state, char* arr) {
    if (state == AS_OFF) {
        if (
            arr[AS_MASTER_SWITCH_ON] &&
            arr[TS_MASTER_SWITCH_ON] &&
            arr[EBS_ARMED] &&
            arr[MISSION_STATUS_SELECTED]
        ) {
            return AS_READY;
        }
    }

    if (state == AS_READY) {
        if (!arr[AS_MASTER_SWITCH_ON]) {
            return AS_OFF;
        }

        if (arr[SDC_OPEN]) {
            return EMERGENCY_BRAKE;
        }

        if ( arr[FIVE_SECOND_TIMER_PASSED] &&
            arr[FRONT_AXLE_TORQUE_REQ_0] &&
            arr[REAR_AXLE_TORQUE_REQUEST_0] &&
            arr[STEER_ANGLE_LESS_THAN_5] &&
            arr[STEER_ANGLE_LESS_THAN_5] &&
            arr[DIRECTION_REQUEST_NEUTRAL] ||
            arr[GO_SIGNAL_ON] 
        ) {
            return AS_DRIVING;
        }
    }

    if (state == AS_DRIVING) {
        if (arr[MISSION_STATUS_FINISHED] &&
            arr[ALL_WHEEL_LESS_THAN_10_RPM]
        ) {
            return AS_FINISHED;
        }

        if (
            arr[SDC_OPEN] ||
            !arr[AS_MASTER_SWITCH_ON] ||
            !arr[GO_SIGNAL_ON] ||
            arr[MISSION_STATUS_FAULT] ||
            arr[AUTONOMOUS_BRAKING_FAULT] ||
            arr[BRAKE_PLAUSIBILITY_FAULT] ||
            arr[AI_ESTOP_REQ] ||
            arr[AI_COMMS_LOST_FAULT] ||
            arr[BMS_FAULT] ||
            arr[EBS_UNAVAILABLE]
        ) {
            return EMERGENCY_BRAKE;
        }
    }

    if (state == AS_FINISHED) {
        if (arr[SDC_OPEN]) {
            return EMERGENCY_BRAKE;
        }

        if (!arr[AS_MASTER_SWITCH_ON]) {
            return AS_OFF;
        }
    }

    if (state == EMERGENCY_BRAKE) {
        if (arr[EBS_TIMER_15_SEC] ||
            !arr[AS_MASTER_SWITCH_ON]
        ) {
            return AS_OFF;
        }
    }

    return state;
}