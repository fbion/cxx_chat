#include "./client.h"

using namespace std;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

void read_callback(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

void close_callback(uv_handle_t *handle);

uv_stream_t *client_connection(uv_loop_t *loop, uv_stream_t *server)
{
    uv_stream_t *client = new uv_stream_t();
    uv_tcp_init(loop, (uv_tcp_t *)client);
    int accept = uv_accept(server, client);
    if (accept == 0)
    {
        send_message(client, "Please input your name:\n");
        uv_read_start(client, alloc_buffer, read_callback);
        register_client(client);
        return client;
    }
    else
    {
        uv_close((uv_handle_t *)client, close_callback);
        return NULL;
    }
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = new char[suggested_size];
    buf->len = suggested_size;
}

void read_callback(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0)
    {
        handle(client, string(buf->base));
    }
    if (nread < 0)
    {
        uv_close((uv_handle_t *)client, close_callback);
    }

    delete buf->base;
}

void close_callback(uv_handle_t *handle)
{
    delete handle;
}