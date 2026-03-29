#include "runway_5.h"

#include <iostream>

using namespace std;

Runway_5::Runway_5(int limit)
{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    num_emergency_landings = 0;
    num_crashes = 0;
    land_wait = takeoff_wait = idle_time = 0;
}

Error_code Runway_5::can_land(const Plane &current)
{
    num_land_requests++;

    int estimated_wait = emergency_landing.size() + landing.size();
    bool needs_immediate_landing = (current.fuel() >= 0) && (current.fuel() < estimated_wait);

    if (needs_immediate_landing)
    {
        Error_code result = emergency_landing.append(current);
        if (result == success)
        {
            num_land_accepted++;
            num_emergency_landings++;
        }
        else
            num_land_refused++;
        return result;
    }

    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}

Error_code Runway_5::can_depart(const Plane &current)
{
    Error_code result;
    if (takeoff_queue.size() < queue_limit)
        result = takeoff_queue.append(current);
    else
        result = fail;

    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}

Runway_activity Runway_5::activity(int time, Plane &moving)
{
    if (!emergency_landing.empty())
    {
        emergency_landing.retrieve(moving);
        land_wait += time - moving.started();
        emergency_landing.serve();
        return land;
    }

    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        landing.serve();
        return land;
    }

    if (!takeoff_queue.empty())
    {
        takeoff_queue.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        takeoff_queue.serve();
        return takeoff;
    }

    idle_time++;
    return idle;
}

void Runway_5::register_landing_result(bool landed_safely)
{
    if (landed_safely)
        num_landings++;
    else
        num_crashes++;
}

void Runway_5::shut_down(int time) const
{
    cout << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Emergency landings granted "
         << num_emergency_landings << endl
         << "Total number of successful landings "
         << num_landings << endl
         << "Total number of crashes from fuel exhaustion "
         << num_crashes << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number of planes left in emergency landing queue "
         << emergency_landing.size() << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff_queue.size() << endl;

    cout << "Percentage of time runway idle "
         << (time > 0 ? 100.0 * static_cast<double>(idle_time) / static_cast<double>(time) : 0.0)
         << "%" << endl;

    cout << "Average wait in landing queue "
         << (num_landings + num_crashes > 0 ? static_cast<double>(land_wait) / static_cast<double>(num_landings + num_crashes) : 0.0)
         << " time units" << endl;
    cout << "Average wait in takeoff queue "
         << (num_takeoffs > 0 ? static_cast<double>(takeoff_wait) / static_cast<double>(num_takeoffs) : 0.0)
         << " time units" << endl;

    cout << "Average observed rate of planes wanting to land "
         << (time > 0 ? static_cast<double>(num_land_requests) / static_cast<double>(time) : 0.0)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << (time > 0 ? static_cast<double>(num_takeoff_requests) / static_cast<double>(time) : 0.0)
         << " per time unit" << endl;

    if (num_crashes == 0)
        cout << "No crashes occurred; airport load stayed below crash threshold." << endl;
    else
        cout << "Crashes occurred; airport load exceeded safe fuel-buffer capacity." << endl;
}
