#pragma once

#include <string>
#include "rtc/rtc.hpp"
#include <unordered_map>

using namespace std;
using namespace rtc;

class p2p_api {
private:
    static Configuration ice_config;
    static string token;
    static string remote_id;

    static unordered_map<string, shared_ptr<PeerConnection>> peer_conn_map;
    static unordered_map<string, shared_ptr<DataChannel>> data_chann_map;
    static unordered_map<string, shared_ptr<Track>> media_track_map;
    
    static void webrtc_create(const string& token, const string& device_id, const string& remote_id, const string& offer_sdp);

public:
    p2p_api();
    ~p2p_api();
    static string get_version() { return "1.0.0"; }
    static void init();
    static bool login(string url, string usr, string pass);
    
    bool start_stream(const string& device_id);
    unsigned int get_port_stream(const string& device_id);
    void stop_stream(const string& device_id);
};