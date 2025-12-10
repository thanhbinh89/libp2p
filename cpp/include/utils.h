#ifndef __UTILS__
#define __UTILS__

#include "json.hpp"

#define TS_20240601000000   (1717200000)

using json = nlohmann::json;
using namespace std;

bool http_post_request(const string link, const string& body, string &response, unsigned long timeout=10, const string rootCA="");
bool http_post_request_with_headers(const string link, const string& body, string &response, const vector<string>& headers, unsigned long timeout=10, const string rootCA="");
uint64_t timestamp_millisec();
string create_random_id(size_t length);
string get_remote_id();

#endif //__UTILS__