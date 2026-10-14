#pragma once

class Battery{
private:
    int capacityWh;
    int chargePercent;
    int cycles;

public:
    Battery();
    Battery(int capacityWh);

    void charge(int percent);
    void discharge(int percent);
    bool isDegraded();
};