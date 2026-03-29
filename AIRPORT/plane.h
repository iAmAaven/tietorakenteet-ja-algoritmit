#pragma once

enum Plane_status
{
    null,
    arriving,
    departing
};
class Plane
{
public:
    Plane();
    Plane(int flt, int time, Plane_status status, int fuel_units = -1);
    void refuse() const;
    bool land(int time) const;
    void fly(int time) const;
    int started() const;
    int fuel() const;
    bool out_of_fuel(int time) const;

private:
    int flt_num;
    int clock_start;
    Plane_status state;
    int fuel_level;
};