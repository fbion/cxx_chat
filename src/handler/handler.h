#ifndef C_CHAT_HANDLER_H
#define C_CHAT_HANDLER_H

#include <map>
#include <uv.h>
#include <vector>
#include <iostream>

using namespace std;

void register_client(uv_stream_t *client);

void send_message(uv_stream_t *client, string message);

void handle(uv_stream_t *client, string data);

#endif