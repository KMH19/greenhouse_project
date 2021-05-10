#pragma once

class CimateControl
{
private:
    double target_temperature;
public:
    CimateControl(/* args */);
    ~CimateControl();
    void controlclimate();
};


