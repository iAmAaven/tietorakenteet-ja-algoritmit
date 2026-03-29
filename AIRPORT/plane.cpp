#include "plane.h"
#include <iostream>

using namespace std;

Plane::Plane(int flt, int time, Plane_status status, int fuel_units)
/* Post: The Plane data members flt num, clock start, and state are set to the
values of the parameters flt, time and status, respectively. */
{
    flt_num = flt;
    clock_start = time;
    state = status;
    fuel_level = (status == arriving) ? fuel_units : -1;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
    {
        if (fuel_level >= 0)
            cout << "land with fuel " << fuel_level << "." << endl;
        else
            cout << "land." << endl;
    }
    else
        cout << "take off." << endl;
}
Plane::Plane()
/* Post: The Plane data members flt num, clock start, state are set to illegal default
values. */
{
    flt_num = -1;
    clock_start = -1;
    state = null;
    fuel_level = -1;
}

void Plane::refuse() const
/* Post: Processes a Plane wanting to use Runway, when the Queue is full. */
{
    cout << "Plane number " << flt_num;
    if (state == arriving)
        cout << " directed to another airport" << endl;
    else
        cout << " told to try to takeoff again later" << endl;
}
bool Plane::land(int time) const
/* Post: Processes a Plane that is landing at the specified time. */
{
    int wait = time - clock_start;

    if (out_of_fuel(time))
    {
        cout << time << ": Plane number " << flt_num << " crashed after "
             << wait << " time unit" << ((wait == 1) ? "" : "s")
             << " in the landing queue." << endl;
        return false;
    }

    cout << time << ": Plane number " << flt_num << " landed after "
         << wait << " time unit" << ((wait == 1) ? "" : "s")
         << " in the landing queue." << endl;
    return true;
}
void Plane::fly(int time) const
/* Post: Process a Plane that is taking off at the specified time. */
{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " took off after "
         << wait << " time unit" << ((wait == 1) ? "" : "s")
         << " in the takeoff queue." << endl;
}

int Plane::started() const
/* Post: Return the time when the plane entered an airport queue. */
{
    return clock_start;
}

int Plane::fuel() const
{
    return fuel_level;
}

bool Plane::out_of_fuel(int time) const
{
    if (state != arriving || fuel_level < 0)
        return false;
    return (time - clock_start) > fuel_level;
}