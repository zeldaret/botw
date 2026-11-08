#include "KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.h"
#include "KingSystem/Utils/FixedString.h"

namespace ksys::res {

template <std::size_t N, std::size_t I = 0>
KSYS_ALWAYS_INLINE static void
initGParamListTravelerRoutePoints(GParamListObjectTraveler::RoutePoint* point,
                                  agl::utl::ParameterObj* obj) {
    if constexpr (I < N) {
        point->initParameters_<I>(obj);
        initGParamListTravelerRoutePoints<N, I + 1>(point + 1, obj);
    }
}

GParamListObjectTraveler::GParamListObjectTraveler() {
    auto* const obj = &mObj;

    mAppearGameDataName.init("", "AppearGameDataName", "", obj);
    mDeleteGameDataName.init("", "DeleteGameDataName", "", obj);
    mRouteType.init("", "RouteType", "", obj);
    mRideHorseName.init("", "RideHorseName", "", obj);
    mIsLeadHorse.init(false, "IsLeadHorse", "", obj);
    mHorseGearLevel.init(-1, "HorseGearLevel", "", obj);

    initGParamListTravelerRoutePoints<NumRoutePoints>(mRoutePoints.data(), obj);
    mRoutePoint29Name.init("", "RoutePoint29Name", "", obj);
}

KSYS_ALWAYS_INLINE GParamListObjectTraveler::RoutePoints::RoutePoints() {
    // Nintendo seems to have duplicated the definitions for each of the 29 route points,
    // which is utterly disgusting and error prone. Manually writing out the loop and using
    // placement-new is necessary to prevent Clang from emitting a loop.
#pragma clang loop unroll(full)
    for (auto& storage : mStorage)
        new (&storage) RoutePoint;
}

KSYS_ALWAYS_INLINE GParamListObjectTraveler::RoutePoint::RoutePoint() = default;

template <s32 I>
KSYS_ALWAYS_INLINE void
GParamListObjectTraveler::RoutePoint::initParameters_(agl::utl::ParameterObj* obj) {
    mName.init("", KSYS_STR(Str("RoutePoint") + Str<I>() + Str("Name")), "", obj);
    mForward.initParameters_<I, I + 1>(obj);
    mBackward.initParameters_<I + 1, I>(obj);
}

template <s32 From, s32 To>
KSYS_ALWAYS_INLINE void
GParamListObjectTraveler::RoutePoint::DirectionInfo::initParameters_(agl::utl::ParameterObj* obj) {
    static constexpr auto prefix = [] {
        using ksys::util::Str;
        return Str("RoutePoint") + Str<From>() + Str("to") + Str<To>();
    }();

    mEntryPoint.init("", KSYS_STR(prefix + Str("EntryPoint")), "", obj);
    mWaitFrame.init(0.0, KSYS_STR(prefix + Str("WaitFrame")), "", obj);
    mSchedule.init("", KSYS_STR(prefix + Str("Schedule")), "", obj);
    mMoveAS.init("", KSYS_STR(prefix + Str("MoveAS")), "", obj);
    mWaitAS.init("", KSYS_STR(prefix + Str("WaitAS")), "", obj);
}

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const float& STR5(GParamListObjectTraveler::getRoutePoint, FROM, to, TO, WaitFrame()) const {  \
        return *mRoutePoints[FROM].mForward.mWaitFrame;                                            \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const float& STR5(GParamListObjectTraveler::getRoutePoint, TO, to, FROM, WaitFrame()) const {  \
        return *mRoutePoints[FROM].mBackward.mWaitFrame;                                           \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, FROM, to, TO, WaitAS())  \
        const {                                                                                    \
        return *mRoutePoints[FROM].mForward.mWaitAS;                                               \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, TO, to, FROM, WaitAS())  \
        const {                                                                                    \
        return *mRoutePoints[FROM].mBackward.mWaitAS;                                              \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, FROM, to, TO, MoveAS())  \
        const {                                                                                    \
        return *mRoutePoints[FROM].mForward.mMoveAS;                                               \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, TO, to, FROM, MoveAS())  \
        const {                                                                                    \
        return *mRoutePoints[FROM].mBackward.mMoveAS;                                              \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, FROM, to, TO,            \
                                 EntryPoint()) const {                                             \
        return *mRoutePoints[FROM].mForward.mEntryPoint;                                           \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, TO, to, FROM,            \
                                 EntryPoint()) const {                                             \
        return *mRoutePoints[FROM].mBackward.mEntryPoint;                                          \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, FROM, to, TO,            \
                                 Schedule()) const {                                               \
        return *mRoutePoints[FROM].mForward.mSchedule;                                             \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(GParamListObjectTraveler::getRoutePoint, TO, to, FROM,            \
                                 Schedule()) const {                                               \
        return *mRoutePoints[FROM].mBackward.mSchedule;                                            \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION
}  // namespace ksys::res
