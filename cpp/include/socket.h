#pragma once

#include <string>
#include <cstdint>

void socket_udp_create(const std::string& device_id);
uint16_t socket_udp_get_port(const std::string& device_id);
void socket_udp_send(const std::string& device_id, uint8_t *data, uint32_t len);
void socket_udp_close(const std::string& device_id);