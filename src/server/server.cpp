#include "server.h"

using namespace std;

void connect_callback(uv_stream_t *server, int status);

static uv_loop_t *loop = uv_default_loop();

sockaddr_in addr;

void start()
{
    int port = 6002;
    int back_log = 128;

    cout << "Start listen: " << port << endl;

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", port, &addr);

    uv_tcp_bind(&server, (const sockaddr *)&addr, 0);

    int r = uv_listen((uv_stream_t *)&server, back_log, connect_callback);
    if (r)
    {
        cout << "Listen error: " << uv_strerror(r) << ", " << uv_err_name(r) << endl;
        exit(1);
    }

    cout << "Listen in: " << to_string(port) << " success." << endl;
    uv_run(loop, UV_RUN_DEFAULT);
}

void connect_callback(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        return;
    }
    client_connection(loop, server);
}