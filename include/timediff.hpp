#ifndef TIMEDIFF_HPP
#define TIMEDIFF_HPP

struct TimeDifferences {
    double UT1_TAI;
    double UTC_GPS;
    double UT1_GPS;
    double TT_UTC;
    double GPS_UTC;
};

TimeDifferences timediff(double UT1_UTC, double TAI_UTC);

#endif
