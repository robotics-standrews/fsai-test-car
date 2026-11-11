#include <cstring>
#include <cassert>
#include "frame.h"

float decode_torque(int torque) {
    assert(torque >= -1950 && torque <= 1950);
    return (float) torque / 10.0;
}

float decode_angle(int angle) {
    assert(angle >= -210 && angle <= 210);
    return (float) angle / 10.0;
}

float decode_brake_pressure(int pressure) {
    assert(pressure >= 0 && pressure <= 200);
    return (float) pressure / 2.0;
}

void frame_decode_ai2vcu_status(Frame_AI2VCU_Status* msg, CAN_Message_Raw* raw) {
    memset(msg, 0, sizeof(Frame_AI2VCU_Status));

    msg->handshake = raw->data[0] & 1;
    msg->estop_request = raw->data[1] & 1;
    msg->mission_status = (Mission_Status) ((raw->data[1] >> 4) & 3);
    msg->direction_request = (Direction) ((raw->data[1] >> 6) & 3);
    msg->lap_counter = raw->data[2] & 0x0f;
    msg->cones_count_actual = raw->data[3];
    msg->cones_count_all = raw->data[4] | ((int) raw->data[5] << 16);
    msg->vehicle_speed_actual = raw->data[6];
    msg->vehicle_speed_demand = raw->data[7];
}

void frame_decode_ai2vcu_drive_f(Frame_AI2VCU_Drive_F* msg, CAN_Message_Raw* raw) {
    memset(msg, 0, sizeof(Frame_AI2VCU_Drive_F));

    msg->requested_torque = decode_torque((int16_t) raw->data[0] | (int16_t) raw->data[1] << 8);
    msg->motor_speed_max = raw->data[2] | (int) raw->data[3] << 8;
}

void frame_decode_ai2vcu_drive_r(Frame_AI2VCU_Drive_R* msg, CAN_Message_Raw* raw) {
    memset(msg, 0, sizeof(Frame_AI2VCU_Drive_R));

    msg->requested_torque = decode_torque((int16_t) raw->data[0] | (int16_t) raw->data[1] << 8);
    msg->motor_speed_max = raw->data[2] | (int) raw->data[3] << 8;
}

void frame_decode_ai2vcu_steer(Frame_AI2VCU_Steer* msg, CAN_Message_Raw* raw) {
    memset(msg, 0, sizeof(Frame_AI2VCU_Steer));
    msg->requested_angle = decode_angle((int16_t) raw->data[0] | (int16_t) raw->data[1] << 8);
}

void frame_decode_ai2vcu_brake(Frame_AI2VCU_Brake* msg, CAN_Message_Raw* raw) {
    memset(msg, 0, sizeof(Frame_AI2VCU_Brake));

    msg->requested_front_brake_pressure = decode_brake_pressure(raw->data[0]);
    msg->requested_rear_brake_pressure = decode_brake_pressure(raw->data[1]);
}
