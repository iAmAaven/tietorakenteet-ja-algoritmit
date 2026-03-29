#include "runway_3.h"

#include <iostream>

using namespace std;

Runway_3::Runway_3(int limit)
{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = 0;
    idle_runway_slots = 0;
    emergency_mode_activations = 0;
    landing_priority_mode = false;
}

Error_code Runway_3::can_land(const Plane &current)
{
    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;

    num_land_requests++;
    if (result != success)
    {
        num_land_refused++;
        landing_priority_mode = true;
        emergency_mode_activations++;
    }
    else
        num_land_accepted++;

    return result;
}

Error_code Runway_3::can_depart(const Plane &current)
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

Runway_activity Runway_3::serve_landing(int time, Plane &moving)
{
    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        landing.serve();
        return land;
    }

    return idle;
}

Runway_activity Runway_3::serve_takeoff(int time, Plane &moving)
{
    if (!takeoff_queue.empty())
    {
        takeoff_queue.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        takeoff_queue.serve();
        return takeoff;
    }

    return idle;
}

void Runway_3::activity(int time,
                        Plane &moving_1, Runway_activity &act_1,
                        Plane &moving_2, Runway_activity &act_2)
{
    if (landing_priority_mode)
    {
        act_1 = serve_landing(time, moving_1);
        act_2 = serve_landing(time, moving_2);

        if (act_1 == idle)
            idle_runway_slots++;
        if (act_2 == idle)
            idle_runway_slots++;

        if (landing.empty())
            landing_priority_mode = false;

        return;
    }

    if (!landing.empty() && !takeoff_queue.empty())
    {
        // Usual operation: one runway usually lands, one usually takes off.
        act_1 = serve_landing(time, moving_1);
        act_2 = serve_takeoff(time, moving_2);
    }
    else if (!landing.empty())
    {
        // If takeoff queue is empty, both runways can serve landings.
        act_1 = serve_landing(time, moving_1);
        act_2 = serve_landing(time, moving_2);
    }
    else if (!takeoff_queue.empty())
    {
        // If landing queue is empty, both runways can serve takeoffs.
        act_1 = serve_takeoff(time, moving_1);
        act_2 = serve_takeoff(time, moving_2);
    }
    else
    {
        act_1 = idle;
        act_2 = idle;
    }

    if (act_1 == idle)
        idle_runway_slots++;
    if (act_2 == idle)
        idle_runway_slots++;
}

void Runway_3::shut_down(int time) const
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
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number of planes served "
         << (num_landings + num_takeoffs) << endl
         << "Landing-priority emergency activations "
         << emergency_mode_activations << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff_queue.size() << endl;

    cout << "Percentage of total runway time idle "
         << (time > 0 ? 100.0 * static_cast<double>(idle_runway_slots) / static_cast<double>(2 * time) : 0.0)
         << "%" << endl;

    cout << "Average wait in landing queue "
         << (num_landings > 0 ? static_cast<double>(land_wait) / static_cast<double>(num_landings) : 0.0)
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
}
