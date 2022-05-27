#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "graphics/renderstate.h"
#include "shadow_renderer.h"
#include "shadow_map.h"
#include "point_light.h"
#include "portal.h"
#include "../player/player.h"
#include "cube.h"
#include "button.h"
#include "../decor/decor_object.h"

#define MAX_CUBES   2

struct Scene {
    struct Camera camera;
    struct Player player;
    struct Portal portals[2];
    struct Cube cubes[MAX_CUBES];
    struct Button* buttons;
    struct DecorObject** decor;
    OSTime cpuTime;
    OSTime lastFrameStart;
    OSTime lastFrameTime;
    u8 buttonCount;
    u8 decorCount;
};

extern struct Scene gScene;

struct GraphicsTask;

void sceneInit(struct Scene* scene);
void sceneRender(struct Scene* scene, struct RenderState* renderState, struct GraphicsTask* task);
void sceneUpdate(struct Scene* scene);

int sceneFirePortal(struct Scene* scene, struct Ray* ray, struct Vector3* playerUp, int portalIndex, int roomIndex);
int sceneOpenPortal(struct Scene* scene, struct Transform* at, int portalIndex, int quadIndex, int roomIndex);

#endif