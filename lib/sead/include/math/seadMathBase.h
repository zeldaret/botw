#pragma once

#include <array>

namespace sead
{
template <typename T>
struct BaseVec2
{
    union
    {
        struct
        {
            T x;
            T y;
        };
        std::array<T, 2> e;
    };
};

template <typename T>
struct BaseVec3
{
    union
    {
        struct
        {
            T x;
            T y;
            T z;
        };
        std::array<T, 3> e;
    };
};

template <typename T>
struct BaseVec4
{
    union
    {
        struct
        {
            T x;
            T y;
            T z;
            T w;
        };
        std::array<T, 4> e;
    };
};

template <typename T>
struct BaseQuat
{
    T x;
    T y;
    T z;
    T w;
};

template <typename T>
struct BaseMtx22
{
    union
    {
        T m[2][2];
        T a[4];
    };
};

template <typename T>
struct BaseMtx33
{
    union
    {
        T m[3][3];
        T a[9];
    };
};

template <typename T>
struct BaseMtx34
{
    union
    {
        T m[3][4];
        T a[12];
    };
};

template <typename T>
struct BaseMtx44
{
    union
    {
        T m[4][4];
        T a[16];
    };
};

}  // namespace sead
