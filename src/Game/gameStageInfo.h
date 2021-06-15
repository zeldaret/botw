#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace uking {

// TODO: Incomplete, but all getters should be there
class StageInfo {
public:
    static const sead::Vector3f& getPSavePosAngleForStageGen() {
        return sInfo.mPSavePosAngleForStageGen;
    }
    static const sead::Vector3f& getPSavePosForStageGen() { return sInfo.mPSavePosForStageGen; }
    static bool isDebugOrDevMap() { return sInfo.mIsDebugOrDevMap; }
    static bool isViewerMapType() { return sInfo.mIsViewerMapType; }
    static bool isDungeon() { return sInfo.mIsDungeon; }
    static bool isCDungeon() { return sInfo.mIsCDungeon; }
    static bool isTestDungeon() { return sInfo.mIsTestDungeon; }
    static bool isMainFieldDungeon() { return sInfo.mIsMainFieldDungeon; }
    static bool isActorViewer() { return sInfo.mIsActorViewer; }
    static bool isStageDebug() { return sInfo.mIsStageDebug; }
    static bool isRemainsElectric() { return sInfo.mIsRemainsElectric; }
    static bool isRemainsFire() { return sInfo.mIsRemainsFire; }
    static bool isRemainsWater() { return sInfo.mIsRemainsWater; }
    static bool isRemainsWind() { return sInfo.mIsRemainsWind; }
    static bool isFinalTrial() { return sInfo.mIsFinalTrial; }
    static bool isAocField() { return sInfo.mIsAocField; }
    static bool isMainField() { return sInfo.mIsMainField; }

    static sead::FixedSafeString<256> sStr;

private:
    static StageInfo sInfo;

    sead::Vector3f mPSavePosAngleForStageGen;
    sead::Vector3f mPSavePosForStageGen;
    bool mIsDebugOrDevMap;
    bool mIsViewerMapType;
    bool mIsDungeon;
    bool mIsCDungeon;
    bool mIsTestDungeon;
    bool mIsMainFieldDungeon;
    bool mIsActorViewer;
    bool mIsStageDebug;
    bool mIsRemainsElectric;
    bool mIsRemainsFire;
    bool mIsRemainsWater;
    bool mIsRemainsWind;
    bool mIsFinalTrial;
    bool mIsAocField;
    bool mIsMainField;
};

}  // namespace uking
