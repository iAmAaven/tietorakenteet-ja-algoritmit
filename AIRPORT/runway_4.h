#pragma once

#include "queue.h"
#include "plane.h"
#include "runway.h"

class Runway_4
{
public:
    Runway_4(int limit);
    Error_code can_land(const Plane &current);
    Error_code can_depart(const Plane &current);
    void activity(int time,
                  Plane &moving_1, Runway_activity &act_1,
                  Plane &moving_2, Runway_activity &act_2,
                  Plane &moving_3, Runway_activity &act_3);
    void shut_down(int time) const;

private:
    Runway_activity serve_landing(int time, Plane &moving);
    Runway_activity serve_takeoff(int time, Plane &moving);

    Extended_queue landing;
    Extended_queue takeoff_queue;
    int queue_limit;

    int num_land_requests;
    int num_takeoff_requests;
    int num_landings;
    int num_takeoffs;
    int num_land_accepted;
    int num_takeoff_accepted;
    int num_land_refused;
    int num_takeoff_refused;
    int land_wait;
    int takeoff_wait;
    int idle_runway_slots;
};
