#ifndef WIFI_CLIENT_H
#define WIFI_CLIENT_H

#include <WiFi.h>

class WifiClient {
  public:
    WifiClient(const char* ssid, const char* password, const char* ip, uint16_t port);
    void connect();
    bool send(const char* data, size_t len);
    void receive();
    bool connected();
    void disconnect();
    IPAddress getIP() const;

  private:
    const char* _ssid;
    const char* _password;
    const char* _ip;
    uint16_t _port;
    WiFiClient _client;
    bool _connected;
};

#endif
