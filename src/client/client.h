#ifndef C_CHAT_CLIENT_H
#define C_CHAT_CLIENT_H

#include <uv.h>
#include <stdlib.h>
#include <iostream>

#include "../handler/handler.h"

using namespace std;

uv_stream_t *client_connection(uv_loop_t *loop, uv_stream_t *server);

#endif