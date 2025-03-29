//
// Created by Uday Singh on 22-02-2025.
//
#pragma once
#ifndef DATATYPES_H
#define DATATYPES_H
#include <compare>
#include <fwd.hpp>
#include<glm.hpp>
// simply a point in 3d space
template<typename t>
class FVector3 {
public:
    t x, y, z;
    FVector3() : x(0), y(0), z(0) {}
    FVector3(t x, t y, t z) : x(x), y(y), z(z) {}
    // Operator Overloading (Fixed)
    FVector3 operator+(const FVector3& r) const {
        return FVector3(x + r.x, y + r.y, z + r.z);
    }

    FVector3 operator-(const FVector3& r) const {
        return FVector3(x - r.x, y - r.y, z - r.z);
    }

    FVector3 operator*(t scalar) const {
        return FVector3(x * scalar, y * scalar, z * scalar);
    }
   inline t length() const {return sqrt(x*x + y*y + z*z);}
    inline t Dot(FVector3 other,t l) const {return other.x*l.x + other.y*l.y + other.z*l.z;}
   inline t Multiply(FVector3 other,t l) const {return other.x*l + other.y*l + other.z*l;}
};
template<typename t>
class FRotator3 {
    public:
    FRotator3(){}
};
class datatypes {

};
class Transform {
    public:
    Transform() {}
    FVector3<float> Location;
    FRotator3<float> Rotation;
    FVector3<float> Scale;



};


#endif //DATATYPES_H
