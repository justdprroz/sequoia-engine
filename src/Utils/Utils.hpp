#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>


template <typename T>
T LinearInterpolation(T x, T minInputRange, T maxInputRange, T minOutputRange, T maxOutputRange) {
    return (x - minInputRange) / (maxInputRange - minInputRange) * (maxOutputRange - minOutputRange) + minOutputRange;
}

template <typename T>
bool InRange(T x, T minRange, T maxRange) {
    return (minRange <= x && x < maxRange);
}

template <typename T>
T div(T a, T b){
    return T(floor(float(a) / b));
}

template <typename T>
T mod(T a, T b){
    return (a % b + b) % b;
}

template <typename T>
long long pair(T a, T b) {
    a %= 65535;
    b %= 65535;
    return (a + b) * (a + b + 1) / 2 + a;
}

#endif