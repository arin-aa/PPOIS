#pragma once

class PowerConnector{
private:
    int pinCount;
    bool isConnected;

public:
    PowerConnector();
    PowerConnector(int pinCount);

    bool connect();
};