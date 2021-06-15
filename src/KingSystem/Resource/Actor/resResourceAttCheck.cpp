#include "KingSystem/Resource/Actor/resResourceAttCheck.h"

namespace ksys::res {

void AttCheck::m4() {}

bool AttCheck::check() {
    return true;
}

float AttCheck::m6() {
    return -1.0;
}

bool AttCheckLine::parse(const CreateArg& arg) {
    mRadius.init(0.0, "Radius", "半径", "Min=0,Max=10", &mObj);
    mAsLineOfSight.init(false, "AsLineOfSight", "視線を透かすコリジョンを無視する", "", &mObj);
    return true;
}

bool AttCheckArea::parse(const CreateArg& arg) {
    mAttPos.init(&mObj);
    mFromPlayer.init(false, "FromPlayer", "目標側基準", "", &mObj);
    return true;
}

bool AttCheckAreaSphere::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaFan::parse(const CreateArg& arg) {
    mAngleCheckIgnoreLockOn.init(false, "AngleCheckIgnoreLockOn", "ロックオン時も角度チェック有効",
                                 "", &mObj);
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mAngle.init(0.0, "Angle", "(アテンション範囲)角度", "Min=0.f,Max=3.1415f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaCylinderFan::parse(const CreateArg& arg) {
    mAngleCheckIgnoreLockOn.init(false, "AngleCheckIgnoreLockOn", "ロックオン時も角度チェック有効",
                                 "", &mObj);
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mAngle.init(0.0, "Angle", "(アテンション範囲)角度", "Min=0.f,Max=3.1415f", &mObj);
    mFixedRadiusCylinder.init(-1.0, "FixedRadiusCylinder", "(アテンション範囲)円柱の半径",
                              "Min=-1.f,Max=100.f", &mObj);
    mFixedRadiusFan.init(-1.0, "FixedRadiusFan", "(アテンション範囲)扇形の半径",
                         "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadiusCylinder.init(1.0, "MarginRadiusCylinder", "(あそびの範囲)円柱の半径",
                               "Min=0.f,Max=100.f", &mObj);
    mMarginRadiusFan.init(1.0, "MarginRadiusFan", "(あそびの範囲)扇形の半径", "Min=0.f,Max=100.f",
                          &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaBox::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mMin.init(sead::Vector3f::zero, "Min", "(モデル範囲)最小", "Min=-100.f,Max=100.f", &mObj);
    mMax.init(sead::Vector3f::zero, "Max", "(モデル範囲)最大", "Min=-100.f,Max=100.f", &mObj);
    mFixedMin.init(-1 * sead::Vector3f::ones, "FixedMin", "(アテンション範囲)最小",
                   "Min=-1.f,Max=100.f", &mObj);
    mFixedMax.init(-1 * sead::Vector3f::ones, "FixedMax", "(アテンション範囲)最大",
                   "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginMin.init(sead::Vector3f::ones, "MarginMin", "(あそびの範囲)最小", "Min=-100.f,Max=100.f",
                    &mObj);
    mMarginMax.init(sead::Vector3f::ones, "MarginMax", "(あそびの範囲)最大", "Min=-100.f,Max=100.f",
                    &mObj);
    return AttCheckArea::parse(arg);
}

AttCheckEachOtherArea::AttCheckEachOtherArea(AttCheckType type) : AttCheck(type) {}

bool AttCheckEachOtherArea::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    mOffsetTop.init(0.0, "OffsetTop", "(アテンションを出される側の範囲オフセット)上辺",
                    "Min=-100,Max=100", &mObj);
    mOffsetBottom.init(0.0, "OffsetBottom", "(アテンションを出される側の範囲オフセット)下辺",
                       "Min=-100,Max=100", &mObj);
    return AttCheck::parse(arg);
}

bool AttCheckAngle::parse(const CreateArg& arg) {
    mAttPos.init(&mObj);
    mAngle.init(0.0, "Angle", "角度", "Min=0.f,Max=3.1415f", &mObj);
    return AttCheck::parse(arg);
}

bool AttCheck::parse(const CreateArg& arg) {
    return true;
}

namespace {
struct AttCheckFactory {
    const char* name;
    AttCheck* (*make)(AttCheckType type, sead::Heap* heap);
};

template <typename T>
constexpr AttCheckFactory makeFactory(const char* name) {
    AttCheckFactory factory{};
    factory.name = name;
    factory.make = [](AttCheckType type, sead::Heap* heap) -> AttCheck* {
        return new (heap) T(type);
    };
    return factory;
}

sead::SafeArray<AttCheckFactory, 19> sFactories{{
    makeFactory<AttCheckLine>("Line"),
    makeFactory<AttCheckScreen>("Screen"),
    makeFactory<AttCheckAreaSphere>("AreaSphere"),
    makeFactory<AttCheckAreaFan>("AreaFan"),
    makeFactory<AttCheckAreaCylinderFan>("AreaCylinderFan"),
    makeFactory<AttCheckAreaBox>("AreaBox"),
    makeFactory<AttCheckEachOtherArea>("EachOtherArea"),
    makeFactory<AttCheckAngle>("Angle"),
    makeFactory<AttCheckWeight>("Weight"),
    makeFactory<AttCheckRideHorse>("RideHorse"),
    makeFactory<AttCheckRideSpace>("RideSpace"),
    makeFactory<AttCheckSwim>("Swim"),
    makeFactory<AttCheckCarry>("Carry"),
    makeFactory<AttCheckNoCarry>("NoCarry"),
    makeFactory<AttCheckGrab>("Grab"),
    makeFactory<AttCheckBootFirstTower>("BootFirstTower"),
    makeFactory<AttCheckFireContact>("FireContact"),
    makeFactory<AttCheckCharacterOn>("CharacterOn"),
    makeFactory<AttCheckUnderWater>("UnderWater"),
}};
}  // namespace

AttCheck* AttCheck::make(const CreateArg& arg) {
    const auto Parameters = agl::utl::getResParameterObj(arg.res_list, "Parameters");
    if (!Parameters)
        return nullptr;

    int type = sFactories.size();
    const auto CheckType = agl::utl::getResParameter(Parameters, "CheckType");
    const sead::SafeString check_type_str = CheckType.getData<char>();
    for (int i = 0; i < sFactories.size(); ++i) {
        if (check_type_str == sFactories[i].name) {
            type = i;
            break;
        }
    }

    if (type == sFactories.size())
        return nullptr;

    auto* check = sFactories[type].make(AttCheckType(type), arg.heap);
    if (!check)
        return nullptr;

    if (!check->init(arg)) {
        delete check;
        return nullptr;
    }

    return check;
}

bool AttCheck::init(const AttCheck::CreateArg& arg) {
    mList.addObj(&mObj, "Parameters");
    mClient = arg.client;
    return parse(arg);
}

}  // namespace ksys::res
