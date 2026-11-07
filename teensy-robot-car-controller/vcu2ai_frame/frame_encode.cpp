#include <cstring>
#include <cassert>
#include "frame.h"

int encode_torque(float torque) {
    int value = (int) (torque * 10.0);
    assert(value >= -1950 && value <= 1950);
    return value;
}

int encode_angle(float angle) {
    int value = (int) (angle * 10.0);
    assert(value >= -210 && value <= 210);
    return value;
}

int encode_brake_pressure(float pressure) {
    int value = (int) (pressure * 2.0);
    assert(value >= 0 && value <= 200);
    return value;
}

void frame_encode_vcu2ai_status(CAN_Message_Raw* raw, Frame_VCU2AI_Status* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x520;

    raw->data[0] = msg->handshake;
    raw->data[1] =
          msg->shutdown_requested << 0
        | msg->as_switch_status << 1
        | msg->ts_switch_status << 2
        | msg->go_signal << 3
        | msg->steering_active << 4;
    raw->data[2] =
          (msg->as_state & 0x0f) << 0
        | (msg->ami_state & 0xf0) << 4;
    raw->data[3] =
          msg->fault_present << 0
        | msg->warning_present << 1;
    raw->data[4] =
          msg->warning_battery_temperature_high << 0
        | msg->warning_battery_soc_low;
    raw->data[5] =
          msg->e_stop_requested << 0
        | msg->fault_hvil_open_circuit << 1
        | msg->fault_hvil_short_circuit << 2
        | msg->fault_emergency_braking_system << 3
        | msg->fault_offboard_charger << 4
        | msg->fault_ai_comms_lost << 5
        | msg->fault_autonomous_braking << 6
        | msg->fault_mission_status << 7;
    raw->data[6] =
          msg->fault_charge_procedure << 0
        | msg->fault_bms << 1
        | msg->fault_brake_plausibility << 2;
    raw->data[7] = msg->shutdown_cause;
}

void frame_encode_vcu2ai_drive_f(CAN_Message_Raw* raw, Frame_VCU2AI_Drive_F* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x521;

    raw->data[0] = (encode_torque(msg->actual_torque) & 0x00ff);
    raw->data[1] = (encode_torque(msg->actual_torque) & 0xff00) >> 8;
    raw->data[2] = (encode_torque(msg->requested_torque) & 0x00ff);
    raw->data[3] = (encode_torque(msg->requested_torque) & 0xff00) >> 8;
    raw->data[4] = (encode_torque(msg->maximum_torque) & 0x00ff);
    raw->data[5] = (encode_torque(msg->maximum_torque) & 0xff00) >> 8;
}

void frame_encode_vcu2ai_drive_r(CAN_Message_Raw* raw, Frame_VCU2AI_Drive_R* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x522;

    raw->data[0] = (encode_torque(msg->actual_torque) & 0x00ff);
    raw->data[1] = (encode_torque(msg->actual_torque) & 0xff00) >> 8;
    raw->data[2] = (encode_torque(msg->requested_torque) & 0x00ff);
    raw->data[3] = (encode_torque(msg->requested_torque) & 0xff00) >> 8;
    raw->data[4] = (encode_torque(msg->maximum_torque) & 0x00ff);
    raw->data[5] = (encode_torque(msg->maximum_torque) & 0xff00) >> 8;
}

void frame_encode_vcu2ai_steer(CAN_Message_Raw* raw, Frame_VCU2AI_Steer* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x523;

    raw->data[0] = (encode_angle(msg->angle) & 0x00ff);
    raw->data[1] = (encode_angle(msg->angle) & 0xff00) >> 8;
    raw->data[2] = (encode_angle(msg->maximum_angle) & 0x00ff);
    raw->data[3] = (encode_angle(msg->maximum_angle) & 0xff00) >> 8;
    raw->data[4] = (encode_angle(msg->requested_angle) & 0x00ff);
    raw->data[5] = (encode_angle(msg->requested_angle) & 0xff00) >> 8;
}

void frame_encode_vcu2ai_brake(CAN_Message_Raw* raw, Frame_VCU2AI_Brake* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x524;

    raw->data[0] = encode_brake_pressure(msg->actual_front_brake_pressure);
    raw->data[1] = encode_brake_pressure(msg->requested_front_brake_pressure);
    raw->data[2] = encode_brake_pressure(msg->actual_rear_brake_pressure);
    raw->data[3] = encode_brake_pressure(msg->requested_rear_brake_pressure);
    raw->data[4] = (msg->brake_status & 0x0f) | (msg->ebs_status & 0x0f) << 4;
}

void frame_encode_vcu2ai_speeds(CAN_Message_Raw* raw, Frame_VCU2AI_Speeds* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x525;

    raw->data[0] = (msg->front_left_wheel_speed & 0x00ff);
    raw->data[1] = (msg->front_left_wheel_speed & 0xff00) >> 8;
    raw->data[2] = (msg->front_right_wheel_speed & 0x00ff);
    raw->data[3] = (msg->front_right_wheel_speed & 0xff00) >> 8;
    raw->data[4] = (msg->rear_left_wheel_speed & 0x00ff);
    raw->data[5] = (msg->rear_left_wheel_speed & 0xff00) >> 8;
    raw->data[6] = (msg->rear_right_wheel_speed & 0x00ff);
    raw->data[7] = (msg->rear_right_wheel_speed & 0xff00) >> 8;
}

void frame_encode_vcu2ai_wheel_counts(CAN_Message_Raw* raw, Frame_VCU2AI_Wheel_Counts* msg) {
    memset(raw, 0, sizeof(CAN_Message_Raw));
    raw->can_id = 0x526;

    raw->data[0] = (msg->front_left_pulse_count & 0x00ff);
    raw->data[1] = (msg->front_left_pulse_count & 0xff00) >> 8;
    raw->data[2] = (msg->front_right_pulse_count & 0x00ff);
    raw->data[3] = (msg->front_right_pulse_count & 0xff00) >> 8;
    raw->data[4] = (msg->rear_left_pulse_count & 0x00ff);
    raw->data[5] = (msg->rear_left_pulse_count & 0xff00) >> 8;
    raw->data[6] = (msg->rear_right_pulse_count & 0x00ff);
    raw->data[7] = (msg->rear_right_pulse_count & 0xff00) >> 8;
}
