#include "KingSystem/Ecosystem/ecoLevelSensor.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/GameData/gdtManager.h"

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

void LevelSensor::calculatePoints()
{
    if (mDefaultPoints >= 0) {
        mPoints = mDefaultPoints;
    }
    else {
        al::ByamlIter iter;
        if (!mRootIter->tryGetIterByKey(&iter, "flag")) {
            return;
        }
        float mPointsSum = 0;
        for (int index = 0; index < iter.getSize(); index++) {
            al::ByamlIter iterKill;
            if (!iter.tryGetIterByIndex(&iterKill, index)) {
                return;
            }
            const char *name;
            if (!iterKill.tryGetStringByKey(&name, "name")) {
                return;
            }
            f32 kill_count;
            s32 kill_mul = 0;
            if (!gdt::Manager::instance()->getParam().get().getS32(&kill_mul, name)) {
                bool non_skip = false;
                bool work = gdt::Manager::instance()->getParam().get().getBool(&non_skip, name);
                if (non_skip && work)
                {
                    kill_mul = 1;
                }
            }
            if (kill_mul > 0) {
                if (!iterKill.tryGetFloatByKey(&kill_count, "point")) {
                    return;
                }
                mPointsSum += kill_count * kill_mul;
            }
        }
        mPoints = mPointsSum;
    }
    al::ByamlIter iter;
    if (mRootIter->tryGetIterByKey(&iter, "setting")) {
        f32 Level2WeaponPower;
        f32 Level2EnemyPower;
        if (iter.tryGetFloatByKey(&Level2WeaponPower, "Level2WeaponPower") &&
            iter.tryGetFloatByKey(&Level2EnemyPower, "Level2EnemyPower")) {
            mWeaponPoints = mPoints * Level2WeaponPower;
            mEnemyPoints = mPoints * Level2EnemyPower;
        }
    }
}

}  // namespace ksys::eco
