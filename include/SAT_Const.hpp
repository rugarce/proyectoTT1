#ifndef SAT_CONST_HPP
#define SAT_CONST_HPP

namespace SAT_Const {

    // Mathematical constants
    const double pi = 3.14159265358979;                       
    const double eps = 2.22044604925031e-16;
    const double pi2       = 6.283185307179586;               // 2π
    const double Rad       = 3.141592653589793 / 180.0;       // Radians per degree
    const double Deg       = 180.0 / 3.141592653589793;       // Degrees per radian
    const double Arcs      = 3600.0 * 180.0 / 3.141592653589793; // Arcseconds per radian

    // General
    const double MJD_J2000 = 51544.5;                         // Modified Julian Date of J2000
    const double T_B1950   = -0.500002108;                    // Epoch B1950
    const double c_light   = 299792458.0;                     // Speed of light [m/s]
    const double AU        = 149597870700.0;                  // Astronomical Unit [m]

    // Physical parameters
    const double R_Earth   = 6378136.3;                       // Earth's radius [m]
    const double f_Earth   = 1.0 / 298.257223563;             // Earth's flattening
    const double R_Sun     = 696000000.0;                     // Sun's radius [m]
    const double R_Moon    = 1738000.0;                       // Moon's radius [m]

    // Earth rotation
    const double omega_Earth = 15.04106717866910 / 3600.0 * Rad; // Earth's rotation [rad/s]

    // Gravitational constants
    const double GM_Earth    = 398600.435436e9;
    const double GM_Sun      = 132712440041.9394e9;
    const double GM_Moon     = GM_Earth / 81.30056907419062;
    const double GM_Mercury  = 22031.780000e9;
    const double GM_Venus    = 324858.592000e9;
    const double GM_Mars     = 42828.375214e9;
    const double GM_Jupiter  = 126712764.800000e9;
    const double GM_Saturn   = 37940585.200000e9;
    const double GM_Uranus   = 5794548.600000e9;
    const double GM_Neptune  = 6836527.100580e9;
    const double GM_Pluto    = 977.0000000000009e9;

    // Solar radiation pressure at 1 AU
    const double P_Sol = 1367.0 / c_light;

}

#endif 
