
#include "scene.h"

#include "defs.h"
#include "graphics/graphics.h"
#include "models/models.h"
#include "materials/shadow_caster.h"
#include "materials/subject.h"
#include "materials/light.h"
#include "materials/point_light_rendered.h"
#include "util/time.h"
#include "sk64/skelatool_defs.h"
#include "controls/controller.h"
#include "shadow_map.h"

#include "../levels/test_chamber_00_0/header.h"

struct Vector3 gStartPosition = {5.0f * SCENE_SCALE, 0.0f, -5.0f * SCENE_SCALE};

struct Vector3 gCameraOffset = {0.0f, 1.2f * SCENE_SCALE, 0.0f};

void sceneInit(struct Scene* scene) {
    cameraInit(&scene->camera, 45.0f, SCENE_SCALE * 0.25f, SCENE_SCALE * 80.0f);
    playerInit(&scene->player);

    scene->player.transform.position = gStartPosition;

    portalInit(&scene->portals[0], 0);
    portalInit(&scene->portals[1], PortalFlagsOddParity);

    scene->portals[0].transform.position.x = 5.0f * SCENE_SCALE;
    scene->portals[0].transform.position.y = 1.0f * SCENE_SCALE;
    scene->portals[0].transform.position.z = -0.1f * SCENE_SCALE;

    scene->portals[1].transform.position.x = 0.1f * SCENE_SCALE;
    scene->portals[1].transform.position.y = 1.0f * SCENE_SCALE;
    scene->portals[1].transform.position.z = -6.0f * SCENE_SCALE;

    quatAxisAngle(&gUp, M_PI * 0.5f, &scene->portals[1].transform.rotation);
}

void sceneRender(struct Scene* scene, struct RenderState* renderState, struct GraphicsTask* task) {
    cameraSetupMatrices(&scene->camera, renderState, (float)SCREEN_WD / (float)SCREEN_HT);
    gDPSetRenderMode(renderState->dl++, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2);

    portalRender(&scene->portals[0], &scene->portals[1], &scene->camera, renderState);
    portalRender(&scene->portals[1], &scene->portals[2], &scene->camera, renderState);

    // gSPDisplayList(renderState->dl++, test_chamber_00_0_test_chamber_00_0_mesh);
}

unsigned ignoreInputFrames = 10;

void sceneUpdate(struct Scene* scene) {
    transformPoint(&scene->player.transform, &gCameraOffset, &scene->camera.transform.position);
    scene->camera.transform.rotation = scene->player.transform.rotation;

    playerUpdate(&scene->player, &scene->camera.transform);
}