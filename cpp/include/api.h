// auth.h
#pragma once
#include <string>

bool api_login(std::string url, std::string usr, std::string pass, std::string &token);
bool api_request_offer(const std::string &token, const std::string &device_id, const std::string &remote_id, std::string &offer_sdp);
bool api_send_answer(const std::string &token, const std::string &device_id, const std::string &remote_id, const std::string &sdp);
