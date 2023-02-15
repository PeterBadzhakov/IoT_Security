#include "wifi_client.h"

// Constructor to set up the necessary information for connecting to the WiFi network and a remote host
WifiClient::WifiClient(const char* ssid, const char* password, const char* ip, uint16_t port) {
  _ssid = ssid;
  _password = password;
  _ip = ip;
  _port = port;
  _connected = false;
}

// Attempts to connect to the WiFi network and remote host
void WifiClient::connect() {
  // Start the WiFi connection process
  WiFi.begin(_ssid, _password);
  // Wait for the connection to be established, up to 5 attempts
  for(int tries = 5; WiFi.status() != WL_CONNECTED && tries > 0; --tries) {
    delay(1000);
  }
  // Connect to the remote host
  _client.connect(_ip, _port);
  _connected = true;
}

// Sends the given data to the remote host if the client is connected
bool WifiClient::send(const char* data, size_t len) {
  if (_client.connected()) {
    return _client.write(data, len) == len;
  }
  return false;
}

// Receives data from the remote host and writes it to Serial if available
void WifiClient::receive() {
  if (_client.connected() && _client.available()) {
    char c = _client.read();
    Serial.write(c);
  }
}

// Returns whether the client is currently connected to the remote host
bool WifiClient::connected() {
  if (_client.connected()) {
    return true;
  }
  // If we were previously connected but are now disconnected, close the connection and set connected to false
  if (_connected) {
    _connected = false;
    _client.stop();
  }
  return false;
}

// Returns the IP address of the client
IPAddress WifiClient::getIP() const
{
  return _client.localIP();
}
