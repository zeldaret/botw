#pragma once

#include <Havok/Common/Base/hkBase.h>

enum hkpUpdateCollisionFilterOnWorldMode {
    HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK,
    HK_UPDATE_FILTER_ON_WORLD_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY,
};

enum hkpUpdateCollisionFilterOnEntityMode {
    HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK,
    HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY,
};

enum hkpEntityActivation {
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE,
    HK_ENTITY_ACTIVATION_DO_ACTIVATE,
};

class hkpWorld {
public:
    hkpWorld();

    hkTime getCurrentTime() const;
};
