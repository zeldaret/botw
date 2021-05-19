#pragma once

#include <KingSystem/Map/mapObject.h>
#include <basis/seadTypes.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::act {
class Actor;
class InstParamPack;
}  // namespace ksys::act

namespace ksys::map {
class Object;
}

namespace ksys::eco {

enum class WeaponModifier {
    None = 0,
    /// This will be upgraded to Blue randomly.
    RandomBlue = 1,
    Blue = 2,
    Yellow = 3,
    /// Chests only: Weapon will never spawn with any modifiers. This overrides regular scaling.
    NoneForced = 4,
};

class LevelSensor {
public:
    LevelSensor();
    virtual ~LevelSensor();

    void init(sead::Heap* heap);

    bool scaleWeapon(const sead::SafeString& weapon, WeaponModifier min_modifier,
                     const char** scaled_weapon, WeaponModifier* scaled_modifier,
                     act::Actor* actor) const;

    bool scaleActor(const sead::SafeString& name, map::Object* obj, const char** scaled_weapon,
                    act::InstParamPack* pack, const sead::Vector3f& position) const;

    void calculatePoints();

private:
    f32 mPoints{};
    f32 mWeaponPoints{};
    f32 mEnemyPoints{};
    bool _14{};
    f32 mDefaultPoints = -1;
    al::ByamlIter* mRootIter = nullptr;
    res::Handle mResHandle;
};
KSYS_CHECK_SIZE_NX150(LevelSensor, 0x78);

}  // namespace ksys::eco
