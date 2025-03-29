//
// Created by Uday Singh on 25-02-2025.
//

#ifndef RAYS_H
#define RAYS_H
#pragma once
#include<glm.hpp>

#include "datatypes.h"
#include"matrix.hpp"

class Rays {
public:
    FVector3<float> origin;
    FVector3<float> direction;
    FVector3<float> color;

    float length;
    inline FVector3<float> DirectedSum(FVector3<float> O,FVector3<float> D,float length) {
        return O+D.Multiply(D,length);
    }
    Rays(FVector3<float> _origin, FVector3<float> _direction, FVector3<float> _color);
    Rays();
    template<typename T>
    bool bCheckHit(T);//Would have to check collision axis aligned bounding box



};




#endif //RAYS_H
