#ifndef POWER_DATA_H
#define POWER_DATA_H

#include "can.h"
#include "mcp2515.h"

struct power_t {
	float voltage;
	float current;
	int serialize(can_frame * frame);
	int deserialize(can_frame * frame);
};
#endif