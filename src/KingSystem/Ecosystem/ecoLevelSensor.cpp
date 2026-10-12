#include "KingSystem/Ecosystem/ecoLevelSensor.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::eco {

inline bool isScalingDisabled(const sead::Vector3f& position) {
    if (world::Manager::instance()->getStageType() == StageType::OpenWorld &&
        world::Manager::instance()->getFieldType() == world::FieldType::AocField &&
        world::Manager::instance()->getScalingMode() == world::ScalingMode::Disabled) {
        return true;
    }

    return Ecosystem::instance()->getFieldMapArea(position.x, position.z) == 28;
}

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

bool LevelSensor::scaleWeapon(const sead::SafeString& weapon, WeaponModifier min_modifier,
                              const char** scaled_weapon, WeaponModifier* scaled_modifier,
                              act::Actor* actor) const {
    if (actor) {
        if (const auto* map_obj = actor->getMapObject()) {
            const sead::Vector3f position = map_obj->getTranslate();
            if (isScalingDisabled(position))
                return false;
        } else {
            sead::Vector3f position;
            actor->getMtx().getTranslation(position);
            if (isScalingDisabled(position))
                return false;
        }
    }

    al::ByamlIter weapons_iter;
    if (!mRootIter->tryGetIterByKey(&weapons_iter, "weapon"))
        return false;

    bool scaled;
    bool finished = false;
    for (s32 i = 0; i < weapons_iter.getSize(); ++i) {
        al::ByamlIter weapon_iter;
        if (!weapons_iter.tryGetIterByIndex(&weapon_iter, i)) {
            scaled = false;
            finished = true;
            break;
        }

        al::ByamlIter actors_iter;
        if (!weapon_iter.tryGetIterByKey(&actors_iter, "actors")) {
            scaled = false;
            finished = true;
            break;
        }

        for (s32 j = 0; j < actors_iter.getSize() - 1; ++j) {
            do {
                al::ByamlIter actor_iter;
                const char* actor_name;
                if (!actors_iter.tryGetIterByIndex(&actor_iter, j) ||
                    !actor_iter.tryGetStringByKey(&actor_name, "name")) {
                    scaled = false;
                    finished = true;
                    break;
                }

                f32 actor_value;
                s32 actor_plus;
                if (!actor_iter.tryGetFloatByKey(&actor_value, "value") ||
                    !actor_iter.tryGetIntByKey(&actor_plus, "plus")) {
                    scaled = false;
                    finished = true;
                    break;
                }

                bool modifier_matches = false;
                if (min_modifier == WeaponModifier::None) {
                    if (actor_plus == -1)
                        modifier_matches = true;
                } else if (min_modifier == WeaponModifier::Blue) {
                    if (actor_plus == 0)
                        modifier_matches = true;
                } else if (min_modifier == WeaponModifier::Yellow && actor_plus == 1) {
                    modifier_matches = true;
                }
                if (!modifier_matches || !(actor_value < mWeaponPoints) || weapon != actor_name)
                    break;

                bool not_rank_up = false;
                if (!weapon_iter.tryGetBoolByKey(&not_rank_up, "not_rank_up")) {
                    scaled = false;
                    finished = true;
                    break;
                }

                al::ByamlIter next_iter;
                f32 next_value = 0.0f;
                if (j + 1 >= actors_iter.getSize()) {
                    scaled = false;
                    finished = true;
                    break;
                }

                s32 found_index = -1;
                s32 k = j + 1;
                do {
                    if (!actors_iter.tryGetIterByIndex(&next_iter, k) ||
                        !next_iter.tryGetFloatByKey(&next_value, "value")) {
                        scaled = false;
                        finished = true;
                        break;
                    }
                    if (not_rank_up) {
                        const char* next_name;
                        if (!next_iter.tryGetStringByKey(&next_name, "name")) {
                            scaled = false;
                            finished = true;
                            break;
                        }
                        if (weapon != next_name)
                            continue;
                    }
                    found_index = k;
                    if (mWeaponPoints <= next_value)
                        break;
                } while (++k < actors_iter.getSize());
                if (finished)
                    break;

                const char* found_name;
                const char* series;
                const char* actor_type;
                s32 found_plus;
                if (found_index < 0 || !actors_iter.tryGetIterByIndex(&next_iter, found_index) ||
                    !next_iter.tryGetStringByKey(&found_name, "name") ||
                    !weapon_iter.tryGetStringByKey(&series, "series") ||
                    !weapon_iter.tryGetStringByKey(&actor_type, "actorType") ||
                    !next_iter.tryGetIntByKey(&found_plus, "plus")) {
                    scaled = false;
                    finished = true;
                    break;
                }

                *scaled_weapon = found_name;
                switch (found_plus) {
                case 0:
                    *scaled_modifier = WeaponModifier::Blue;
                    break;
                case 1:
                    *scaled_modifier = WeaponModifier::Yellow;
                    break;
                default:
                    *scaled_modifier = WeaponModifier::None;
                    break;
                }
                scaled = true;
                finished = true;
            } while (false);

            if (finished)
                break;
        }
        if (finished)
            break;
    }
    return finished & scaled;
}

bool LevelSensor::scaleActor(const sead::SafeString& name, map::Object* obj,
                             const char** scaled_weapon, act::InstParamPack* pack,
                             const sead::Vector3f& position) const {
    if (isScalingDisabled(position))
        return false;

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
