#include "random.h"
#include "runway.h"
#include "runway_2.h"
#include "runway_3.h"
#include "runway_4.h"
#include "runway_5.h"
#include "plane.h"
#include <iostream>

using namespace std;

void initialize_p1(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies the number of time units in the simulation, the maximal queue
sizes permitted, and the expected arrival and departure rates for the airport.
Post: The program prints instructions and initializes the parameters end time,
queue limit, arrival rate, and departure rate to the specified values.
Uses: utility function user says yes */
{
    cout << "This program simulates an airport with only one runway."
         << endl
         << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;
    bool acceptable;
    do
    {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        acceptable = true;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be nonnegative." << endl;
            acceptable = false;
        }
        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. "
                 << endl;
    } while (!acceptable);
}

void initialize_p2(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies the number of time units in the simulation, the maximal queue
sizes permitted, and the expected arrival and departure rates for the airport.
Post: The program prints instructions and initializes the parameters end time,
queue limit, arrival rate, and departure rate to the specified values. */
{
    cout << "This program simulates an airport with two runways." << endl
         << "One runway is used only for landings, and one only for takeoffs."
         << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;
    bool acceptable;
    do
    {
        acceptable = true;
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be nonnegative." << endl;
            acceptable = false;
        }
        if (acceptable && (arrival_rate > 1.0 || departure_rate > 1.0))
            cerr << "Safety Warning: One of these runways will become saturated."
                 << endl;
    } while (!acceptable);
}

void initialize_p3(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies simulation parameters for the P3 two-runway rules.
Post: Parameters are initialized for the flexible two-runway simulation. */
{
    cout << "This program simulates an airport with two usually specialized runways."
         << endl
         << "If one queue is empty, both runways serve the other queue." << endl
         << "If landing queue overflows, takeoffs stop and both runways clear landings."
         << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        acceptable = true;
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;

        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be nonnegative." << endl;
            acceptable = false;
        }

        if (acceptable && (arrival_rate > 1.0 || departure_rate > 1.0))
            cerr << "Safety Warning: At least one queue may saturate frequently." << endl;
    } while (!acceptable);
}

void initialize_p4(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies simulation parameters for the P4 three-runway rules.
Post: Parameters are initialized for the three-runway simulation. */
{
    cout << "This program simulates an airport with three runways." << endl
         << "Runway A is always for landings, Runway B always for takeoffs," << endl
         << "and Runway C serves landings unless landing queue is empty." << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        acceptable = true;
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;

        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be nonnegative." << endl;
            acceptable = false;
        }

        if (acceptable && (arrival_rate > 2.0 || departure_rate > 2.0))
            cerr << "Safety Warning: One queue may still saturate." << endl;
    } while (!acceptable);
}

void initialize_p5(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies simulation parameters for P5 one-runway fuel rules.
Post: Parameters are initialized for the fuel-aware one-runway simulation. */
{
    cout << "This program simulates a one-runway airport with fuel-limited arrivals." << endl
         << "Arriving planes have random fuel and may receive emergency landing priority." << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        acceptable = true;
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;

        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be nonnegative." << endl;
            acceptable = false;
        }

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport may become saturated and cause crashes." << endl;
    } while (!acceptable);
}

void main_1()
/*Pre:  The user must supply the number of time intervals the simulation is to run, the
        expected number of planes arriving, the expected number of planes departing
        per time interval, and the maximum number of allowed size for runway queues.
  Post: The program performs a random simulation of the airport, showing the status of
        the runway at each time interval, and prints out a summary of ariport operation
        at the conclusion.
  Uses: Classes Runway, Plane, Random, and fucntions run_idle, initialize. */
{
    int end_time;    // Time to run the simulation
    int queue_limit; // size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize_p1(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
        }
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }
        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane))
        {
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            cout << current_time << ": Runway is idle." << endl;
            break;
        }
    }
    small_airport.shut_down(end_time);
}

void main_2()
/* Pre: User supplies simulation parameters for a two-runway airport.
Post: Runs simulation where one runway serves only landings and the other only takeoffs. */
{
    int end_time;
    int queue_limit;
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize_p2(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway_2 airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane landing_plane;
        if (airport.land_activity(current_time, landing_plane) == land)
            landing_plane.land(current_time);
        else
            cout << current_time << ": Landing runway is idle." << endl;

        Plane departing_plane;
        if (airport.takeoff_activity(current_time, departing_plane) == takeoff)
            departing_plane.fly(current_time);
        else
            cout << current_time << ": Takeoff runway is idle." << endl;
    }

    airport.shut_down(end_time);
}

void main_3()
/* Pre: User supplies simulation parameters for P3 rules.
Post: Runs simulation with two usually specialized runways plus dynamic overflow behavior. */
{
    int end_time;
    int queue_limit;
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize_p3(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway_3 airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_1, moving_2;
        Runway_activity act_1, act_2;
        airport.activity(current_time, moving_1, act_1, moving_2, act_2);

        if (act_1 == land)
            moving_1.land(current_time);
        else if (act_1 == takeoff)
            moving_1.fly(current_time);
        else
            cout << current_time << ": Runway A is idle." << endl;

        if (act_2 == land)
            moving_2.land(current_time);
        else if (act_2 == takeoff)
            moving_2.fly(current_time);
        else
            cout << current_time << ": Runway B is idle." << endl;
    }

    airport.shut_down(end_time);
}

void main_4()
/* Pre: User supplies simulation parameters for P4 rules.
Post: Runs simulation with three runways and fixed/dynamic assignment policy. */
{
    int end_time;
    int queue_limit;
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize_p4(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway_4 airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_1, moving_2, moving_3;
        Runway_activity act_1, act_2, act_3;
        airport.activity(current_time, moving_1, act_1, moving_2, act_2, moving_3, act_3);

        if (act_1 == land)
            moving_1.land(current_time);
        else if (act_1 == takeoff)
            moving_1.fly(current_time);
        else
            cout << current_time << ": Runway A is idle." << endl;

        if (act_2 == land)
            moving_2.land(current_time);
        else if (act_2 == takeoff)
            moving_2.fly(current_time);
        else
            cout << current_time << ": Runway B is idle." << endl;

        if (act_3 == land)
            moving_3.land(current_time);
        else if (act_3 == takeoff)
            moving_3.fly(current_time);
        else
            cout << current_time << ": Runway C is idle." << endl;
    }

    airport.shut_down(end_time);
}

void main_5()
/* Pre: User supplies simulation parameters for P5 rules.
Post: Runs one-runway simulation with random fuel, emergency landings, and crash tracking. */
{
    int end_time;
    int queue_limit;
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize_p5(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway_5 airport(queue_limit);

    int max_fuel = (queue_limit > 0) ? (queue_limit + 3) : 3;

    for (int current_time = 0; current_time < end_time; current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
        {
            int fuel_units = variable.random_integer(1, max_fuel);
            Plane current_plane(flight_number++, current_time, arriving, fuel_units);
            if (airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        Runway_activity action = airport.activity(current_time, moving_plane);
        if (action == land)
            airport.register_landing_result(moving_plane.land(current_time));
        else if (action == takeoff)
            moving_plane.fly(current_time);
        else
            cout << current_time << ": Runway is idle." << endl;
    }

    airport.shut_down(end_time);
}

int main()
{
    int choice = 0;
    do
    {
        cout << "1.\tRun P1 version of Airport simulator" << endl;
        cout << "2.\tRun P2 version of Airport simulator" << endl;
        cout << "3.\tRun P3 version of Airport simulator" << endl;
        cout << "4.\tRun P4 version of Airport simulator" << endl;
        cout << "5.\tRun P5 version of Airport simulator" << endl;
        cout << "6.\tQuit the program" << endl;
        cout << "Your choice: " << flush;
        cin >> choice;

        switch (choice)
        {
        case 1:
            main_1();
            break;
        case 2:
            main_2();
            break;
        case 3:
            main_3();
            break;
        case 4:
            main_4();
            break;
        case 5:
            main_5();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please choose 1-6." << endl;
            break;
        }
        cout << endl;
    } while (choice != 6);

    return 0;
}