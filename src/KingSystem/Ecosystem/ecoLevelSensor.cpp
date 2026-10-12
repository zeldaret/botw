#include "KingSystem/Ecosystem/ecoLevelSensor.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::eco {

LevelSensor::LevelSensor() = default;

LevelSensor::~LevelSensor() {
    mResHandle.requestUnload2();
    if (mRootIter)
        delete mRootIter;
}

void LevelSensor::init(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "LevelSensor";
    mResHandle.load("Ecosystem/LevelSensor.byml", &req);
    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());
    mRootIter = new (heap) al::ByamlIter(res->getRawData());
}

bool LevelSensor::scaleActor(const sead::SafeString& name, map::Object* obj,
                             const char** scaled_weapon, act::InstParamPack* pack,
                             const sead::Vector3f& position) const {
    if (world::Manager::instance()->getStageType() == StageType::OpenWorld &&
        world::Manager::instance()->getFieldType() == world::FieldType::AocField &&
        world::Manager::instance()->getScalingMode() == world::ScalingMode::Disabled) {
        return false;
    }

    if (Ecosystem::instance()->getFieldMapArea(position.x, position.z) == 28) {
        return false;
    }

    if (name.startsWith("Enemy")) {
        const auto& mubin_iter = obj->getMubinIter();
        s32 mode = 0;
        if (mubin_iter.tryGetParamIntByKey(&mode, "LevelSensorMode") && mode >= 1) {
            al::ByamlIter enemies_iter;
            if (!mRootIter->tryGetIterByKey(&enemies_iter, "enemy"))
                return false;
            for (s32 i = 0; i < enemies_iter.getSize(); ++i) {
                al::ByamlIter enemy_iter;
                if (!enemies_iter.tryGetIterByIndex(&enemy_iter, i))
                    return false;

                al::ByamlIter actors_iter;
                if (!enemy_iter.tryGetIterByKey(&actors_iter, "actors"))
                    return false;

                for (s32 j = 0; j < actors_iter.getSize() - 1; ++j) {
                    al::ByamlIter actor_iter;
                    if (!actors_iter.tryGetIterByIndex(&actor_iter, j)) {
                        return false;
                    }

                    const char* actor_name;
                    if (!actor_iter.tryGetStringByKey(&actor_name, "name")) {
                        return false;
                    }

                    f32 actor_value;
                    if (!actor_iter.tryGetFloatByKey(&actor_value, "value")) {
                        return false;
                    }

                    if (!(actor_value < mEnemyPoints))
                        continue;
                    if (name != actor_name)
                        continue;

                    al::ByamlIter next_actor_iter;
                    f32 next_actor_value;
                    for (int k = j + 1; k < actors_iter.getSize(); ++k) {
                        if (!actors_iter.tryGetIterByIndex(&next_actor_iter, k)) {
                            return false;
                        }

                        if (!next_actor_iter.tryGetFloatByKey(&next_actor_value, "value")) {
                            return false;
                        }

                        if (!(mEnemyPoints <= next_actor_value))
                            continue;
                        break;
                    }

                    const char* next_actor_name;
                    if (!next_actor_iter.tryGetStringByKey(&next_actor_name, "name")) {
                        return false;
                    }

                    const char* enemy_species;
                    if (!enemy_iter.tryGetStringByKey(&enemy_species, "species")) {
                        return false;
                    }

                    *scaled_weapon = next_actor_name;
                    return true;
                }
            }
        }
    }

    if (name.startsWith("Weapon")) {
        const auto& mubin_iter = obj->getMubinIter();
        WeaponModifier scaled_modifier;
        s32 mode = 0;
        s32 sharp_weapon_judge_type;
        if (mubin_iter.tryGetParamIntByKey(&mode, "LevelSensorMode") && mode >= 1) {
            sharp_weapon_judge_type = 0;
            if (!mubin_iter.tryGetParamIntByKey(&sharp_weapon_judge_type, "SharpWeaponJudgeType")) {
                return false;
            }

            const char* scaled_weapon_result;
            WeaponModifier weapon_modifier =
                getRandomWeaponModifier(sharp_weapon_judge_type, obj->getUnitConfigName());
            if (!scaleWeapon(obj->getUnitConfigName(), weapon_modifier, &scaled_weapon_result,
                             &scaled_modifier, nullptr)) {
                return false;
            }

            auto val = int(scaled_modifier);
            pack->getBuffer().add(val, "SharpWeaponJudgeType");

            *scaled_weapon = scaled_weapon_result;
            return true;
        }
    }

    return false;
}

void LevelSensor::calculatePoints() {
    if (mDefaultPoints >= 0) {
        mPoints = mDefaultPoints;
    } else {
        al::ByamlIter flag;
        if (!mRootIter->tryGetIterByKey(&flag, "flag")) {
            return;
        }
        float point_sum = 0;
        for (int index = 0; index < flag.getSize(); index++) {
            al::ByamlIter iter_enemy;
            if (!flag.tryGetIterByIndex(&iter_enemy, index)) {
                return;
            }
            const char* name;
            if (!iter_enemy.tryGetStringByKey(&name, "name")) {
                return;
            }
            s32 kill_count = 0;
            if (!gdt::Manager::instance()->getParam().get().getS32(&kill_count, name)) {
                bool unique_kill = false;
                if (gdt::Manager::instance()->getParam().get().getBool(&unique_kill, name)) {
                    if (unique_kill) {
                        kill_count = 1;
                    }
                }
            }
            if (kill_count > 0) {
                f32 point;
                if (!iter_enemy.tryGetFloatByKey(&point, "point")) {
                    return;
                }
                point_sum += point * kill_count;
            }
        }
        mPoints = point_sum;
    }
    al::ByamlIter setting_iter;
    if (mRootIter->tryGetIterByKey(&setting_iter, "setting")) {
        f32 Level2WeaponPower;
        f32 Level2EnemyPower;
        if (setting_iter.tryGetFloatByKey(&Level2WeaponPower, "Level2WeaponPower") &&
            setting_iter.tryGetFloatByKey(&Level2EnemyPower, "Level2EnemyPower")) {
            mWeaponPoints = mPoints * Level2WeaponPower;
            mEnemyPoints = mPoints * Level2EnemyPower;
        }
    }
}

}  // namespace ksys::eco
