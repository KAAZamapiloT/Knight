//
// Created by Uday Singh on 22-02-2025.
//
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<math.h>
#include "datatypes.h"

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };
template <typename c>
class Camera {
public:
    c CameraId;       // camera id to diffrentiate between types of camera -> fixed , free movement , any movement
    // Constructor
    Camera(c ID) {
        Position = glm::vec3(0.0f, 0.0f, 3.0f);  // Default position
        Target = glm::vec3(0.0f, 0.0f, 0.0f);
        Up = glm::vec3(0.0f, 1.0f, 0.0f);        // Y-axis is up
        updateViewMatrix();
        FarPlane = 200.0f;
        NearPlane=0.1f;
        this->CameraId = ID;
    }
    Camera() {

    }
    // Destructor
    ~Camera() {}

    // Camera properties
    glm::vec3 Position;  // Where camera is situated
    glm::vec3 Target;    // Where camera is looking
    glm::vec3 Up;
    glm::mat4 view;
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 200.0f);
    float FarPlane;
    float NearPlane;
    // Update View Matrix
    void updateViewMatrix() {
        view = glm::lookAt(Position, Target, Up);
    }
   
    // Move Camera
    void MoveCamera(glm::vec3 direction, float magnitude) {
        Position += glm::normalize(direction) * magnitude;
        Target += glm::normalize(direction) * magnitude;
        updateViewMatrix();
    }
    // Rotate Camera (Implementation needed)
    void rotateCamera(float yaw, float pitch) {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        Target = glm::normalize(front);
        updateViewMatrix();
    }
    // would be atick type function and will be called every frame
    void UpdateCamera() {

    }
};

#endif // CAMERA_H
