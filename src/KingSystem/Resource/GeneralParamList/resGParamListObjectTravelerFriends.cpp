#include "KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.h"
#include "KingSystem/Utils/FixedString.h"

namespace ksys::res {

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const float& STR5(getRoutePoint, FROM, to, TO, WaitFrame(const GParamListObjectTraveler& t)) { \
        return *t.mRoutePoints[FROM].mForward.mWaitFrame;                                          \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const float& STR5(getRoutePoint, TO, to, FROM, WaitFrame(const GParamListObjectTraveler& t)) { \
        return *t.mRoutePoints[FROM].mBackward.mWaitFrame;                                         \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, FROM, to, TO,                                      \
                                 WaitAS(const GParamListObjectTraveler& t)) {                      \
        return *t.mRoutePoints[FROM].mForward.mWaitAS;                                             \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, TO, to, FROM,                                      \
                                 WaitAS(const GParamListObjectTraveler& t)) {                      \
        return *t.mRoutePoints[FROM].mBackward.mWaitAS;                                            \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, FROM, to, TO,                                      \
                                 MoveAS(const GParamListObjectTraveler& t)) {                      \
        return *t.mRoutePoints[FROM].mForward.mMoveAS;                                             \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, TO, to, FROM,                                      \
                                 MoveAS(const GParamListObjectTraveler& t)) {                      \
        return *t.mRoutePoints[FROM].mBackward.mMoveAS;                                            \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, FROM, to, TO,                                      \
                                 EntryPoint(const GParamListObjectTraveler& t)) {                  \
        return *t.mRoutePoints[FROM].mForward.mEntryPoint;                                         \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, TO, to, FROM,                                      \
                                 EntryPoint(const GParamListObjectTraveler& t)) {                  \
        return *t.mRoutePoints[FROM].mBackward.mEntryPoint;                                        \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, FROM, to, TO,                                      \
                                 Schedule(const GParamListObjectTraveler& t)) {                    \
        return *t.mRoutePoints[FROM].mForward.mSchedule;                                           \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION

#define ROUTE_POINT_FUNCTION(FROM, TO)                                                             \
    const sead::SafeString& STR5(getRoutePoint, TO, to, FROM,                                      \
                                 Schedule(const GParamListObjectTraveler& t)) {                    \
        return *t.mRoutePoints[FROM].mBackward.mSchedule;                                          \
    }
ROUTE_POINT(ROUTE_POINT_FUNCTION)
#undef ROUTE_POINT_FUNCTION
}  // namespace ksys::res
