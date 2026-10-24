#pragma once

class Battery{
private:
    int capacityWh;
    int chargePercent;
    int cycles;

public:
    Battery();
    explicit Battery(int capacityWh);

    void charge(int percent);
    void discharge(int percent);
    bool isDegraded();
    int getChargePercent();
    int getCycles();
};
