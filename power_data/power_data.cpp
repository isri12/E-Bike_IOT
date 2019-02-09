#include "power_data.h"

int power_t::serialize(can_frame * frame)
{
	frame->can_id = 0xAB;
	frame->can_dlc = 8;
	uint8_t *ptr = frame->data;
	memcpy(ptr, &(this->voltage), sizeof(float));
	ptr += sizeof(float);
	memcpy(ptr, &(this->current), sizeof(float));
	return 0;
}

int power_t::deserialize(can_frame * frame)
{
	frame->can_id = 0xAB;
	frame->can_dlc = 8;
	uint8_t *ptr = frame->data;
	memcpy(&(this->voltage), ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&(this->current), ptr, sizeof(float));
	return 0;
}
