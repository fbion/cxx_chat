#include "handler.h"

void send_message(uv_stream_t *client, string message);

void write_callback(uv_write_t *req, int status);

map<uv_stream_t *, string> client_map;

void register_client(uv_stream_t *client)
{
  client_map[client] = "";
}

void handle(uv_stream_t *client, string message)
{
  string result;
  message = message.substr(0, message.length() - 1);
  if (message.length() == 0)
  {
    return;
  }
  if (client_map[client].length() == 0)
  {
    client_map[client] = message;
    result = message + " login success\n";
    send_message(client, result);
  }
  else
  {
    cout << "server receive: " << message << endl;
    result = client_map[client] + ": " + message + "\n";
    for (std::map<uv_stream_t *, string>::iterator it = client_map.begin(); it != client_map.end(); ++it)
    {
      if ((*it).first != client)
      {
        send_message((*it).first, result);
      }
    }
  }
}

void send_message(uv_stream_t *client, string message)
{
  char *result_c_str = (char *)message.c_str();
  uv_buf_t req_buf = uv_buf_init(result_c_str, (unsigned int)message.length());
  uv_write(new uv_write_t(), client, &req_buf, 1, write_callback);
}

void write_callback(uv_write_t *req, int status)
{
  delete req->bufs;
  delete req;
}