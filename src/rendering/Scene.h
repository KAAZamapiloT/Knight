//
// Created by Uday Singh on 24-02-2025.
//
#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "datatypes.h"
template<typename T>
class SceneNode {
public:
    Transform transform;
    T data;
    SceneNode*next;
    SceneNode();
};
template<typename T>
class SceneActor {
private:
    SceneNode <T>Root;

public:
    SceneActor();
    ~SceneActor();

};
template<typename T>
class Scene {
public:

void UpdateScene() {

}

};
class FSceneInfo {

};


#endif //SCENE_H
