#include <cerrno>
#include <cstdint>

#ifndef FRAME_H
#define FRAME_H

struct CAN_Message_Raw {
    short can_id;
    uint8_t data[8];
};

// autonomous system state
enum AS_State {
    AS_STATE_OFF = 1,
    AS_STATE_READY = 2,
    AS_STATE_DRIVING = 3,
    AS_STATE_EMERGENCY_BRAKE = 4,
    AS_STATE_FINISHED = 5,
};

// autonomous mission indicator state
enum AMI_State {
    AMI_STATE_NOT_SELECTED = 0,
    AMI_STATE_ACCELERATION = 1,
    AMI_STATE_SKIDPAD = 2,
    AMI_STATE_AUTOCROSS = 3,
    AMI_STATE_TRACK_DRIVE = 4,
    AMI_STATE_STATIC_INSPECTION_A = 5,
    AMI_STATE_STATIC_INSPECTION_B = 6,
    AMI_STATE_AUTONOMOUS_DEMO = 7,
};

enum Shutdown_Cause {
    SHUTDOWN_CAUSE_NO_SHUTDOWN = 0,
    SHUTDOWN_CAUSE_AI_COMPUTER_REQUEST = 1,
    SHUTDOWN_CAUSE_FAULT_HVIL_OPEN_CIRCUIT = 2,
    SHUTDOWN_CAUSE_FAULT_HVIL_SHORT_CIRCUIT = 3,
    SHUTDOWN_CAUSE_FAULT_EMERGENCY_BRAKING_SYSTEM = 4,
    SHUTDOWN_CAUSE_FAULT_OFFBOARD_CHARGER = 5,
    SHUTDOWN_CAUSE_FAULT_AI_COMMS = 6,
    SHUTDOWN_CAUSE_FAULT_AUTONOMOUS_BRAKING = 7,
    SHUTDOWN_CAUSE_FAULT_MISSION_STATUS = 8,
    SHUTDOWN_CAUSE_FAULT_CHARGING_PROCEDURE = 9,
    SHUTDOWN_CAUSE_FAULT_BMS = 10,
    SHUTDOWN_CAUSE_FAULT_BRAKE_PLAUSIBILITY = 11,
};

enum Brake_Status {
    BRAKE_STATUS_INITIALISING = 0,
    BRAKE_STATUS_READY = 1,
    BRAKE_STATUS_SHUTTING_DOWN = 2,
    BRAKE_STATUS_SHUTDOWN_COMPLETE = 3,
    BRAKE_STATUS_FAULT = 4,
};

// Emergency braking system status
enum EBS_Status {
    EBS_UNAVAILABLE = 1,
    EBS_ARMED = 2,
    EBS_TRIGGERED = 3,
};

enum Mission_Status {
    MISSION_STATUS_NOT_SELECTED = 0,
    MISSION_STATUS_SELECTED = 1,
    MISSION_STATUS_RUNNING = 2,
    MISSION_STATUS_FINISHED = 3,
};

enum Direction{
    DIRECTION_NEUTRAL = 0,
    DIRECTION_FORWARD = 1,
    DIRECTION_REVERSE = 2,
};

// VCU and powertrain status reporting to the AI computer
struct Frame_VCU2AI_Status {
    bool handshake;
    bool shutdown_requested;
    bool as_switch_status;
    bool ts_switch_status;
    bool go_signal;
    bool steering_active;
    AS_State as_state;
    AMI_State ami_state;
    bool fault_present;
    bool warning_present;
    bool warning_battery_temperature_high;
    bool warning_battery_soc_low;
    bool e_stop_requested;
    bool fault_hvil_open_circuit;
    bool fault_hvil_short_circuit;
    bool fault_emergency_braking_system;
    bool fault_offboard_charger;
    bool fault_ai_comms_lost;
    bool fault_autonomous_braking;
    bool fault_mission_status;
    bool fault_charge_procedure;
    bool fault_bms;
    bool fault_brake_plausibility;
    Shutdown_Cause shutdown_cause;
};

// Feedback from the front drive motor
struct Frame_VCU2AI_Drive_F {
    float actual_torque;
    float requested_torque;
    float maximum_torque;
};

// Feedback from the rear drive motor
struct Frame_VCU2AI_Drive_R {
    float actual_torque;
    float requested_torque;
    float maximum_torque;
};

// Feedback from the steering controller
struct Frame_VCU2AI_Steer {
    // angle in degrees, from -210 to 210 inclusive
    float angle;
    float maximum_angle;
    float requested_angle;
};

// Feedback from the hydraulic braking system
// Brake pressures are percentages, from 0% to 100%
struct Frame_VCU2AI_Brake {
    float actual_front_brake_pressure;
    float requested_front_brake_pressure;
    float actual_rear_brake_pressure;
    float requested_rear_brake_pressure;
    Brake_Status brake_status;
    EBS_Status ebs_status;
};

// Wheel speed measurements (RPM)
struct Frame_VCU2AI_Speeds {
    int front_left_wheel_speed;
    int front_right_wheel_speed;
    int rear_left_wheel_speed;
    int rear_right_wheel_speed;
};

// Raw pulse count measurements from the wheel speed sensors
struct Frame_VCU2AI_Wheel_Counts {
    int front_left_pulse_count;
    int front_right_pulse_count;
    int rear_left_pulse_count;
    int rear_right_pulse_count;
};

struct Frame_AI2VCU_Status {
    bool handshake;
    bool estop_request;
    Mission_Status mission_status;
    Direction direction_request;
    int lap_counter;
    int cones_count_actual;
    int cones_count_all;
    int vehicle_speed_actual;
    int vehicle_speed_demand;
};

struct Frame_AI2VCU_Drive_F {
    float requested_torque;
    // in RPM
    int motor_speed_max;
};

struct Frame_AI2VCU_Drive_R {
    float requested_torque;
    // in RPM
    int motor_speed_max;
};

struct Frame_AI2VCU_Steer {
    float requested_angle;
};

struct Frame_AI2VCU_Brake {
    float requested_front_brake_pressure;
    float requested_rear_brake_pressure;
};

void frame_encode_vcu2ai_status(CAN_Message_Raw* raw, Frame_VCU2AI_Status* msg);
void frame_encode_vcu2ai_drive_f(CAN_Message_Raw* raw, Frame_VCU2AI_Drive_F* msg);
void frame_encode_vcu2ai_drive_r(CAN_Message_Raw* raw, Frame_VCU2AI_Drive_R* msg);
void frame_encode_vcu2ai_steer(CAN_Message_Raw* raw, Frame_VCU2AI_Steer* msg);
void frame_encode_vcu2ai_brake(CAN_Message_Raw* raw, Frame_VCU2AI_Brake* msg);
void frame_encode_vcu2ai_speeds(CAN_Message_Raw* raw, Frame_VCU2AI_Speeds* msg);
void frame_encode_vcu2ai_wheel_counts(CAN_Message_Raw* raw, Frame_VCU2AI_Wheel_Counts* msg);

void frame_decode_ai2vcu_status(Frame_AI2VCU_Status* msg, CAN_Message_Raw* raw);
void frame_decode_ai2vcu_drive_f(Frame_AI2VCU_Drive_F* msg, CAN_Message_Raw* raw);
void frame_decode_ai2vcu_drive_r(Frame_AI2VCU_Drive_R* msg, CAN_Message_Raw* raw);
void frame_decode_ai2vcu_steer(Frame_AI2VCU_Steer* msg, CAN_Message_Raw* raw);
void frame_decode_ai2vcu_brake(Frame_AI2VCU_Brake* msg, CAN_Message_Raw* raw);

#endif
