#pragma once

class PowerConnector{
private:
    int pinCount;
    bool isConnected;

public:
    PowerConnector();
    explicit PowerConnector(int pinCount);

    bool connect();
};
