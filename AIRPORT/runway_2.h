#pragma once

#include "queue.h"
#include "plane.h"
#include "runway.h"

class Runway_2
{
public:
    Runway_2(int limit);
    Error_code can_land(const Plane &current);
    Error_code can_depart(const Plane &current);
    Runway_activity land_activity(int time, Plane &moving);
    Runway_activity takeoff_activity(int time, Plane &moving);
    void shut_down(int time) const;

private:
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
    int landing_idle_time;
    int takeoff_idle_time;
};
