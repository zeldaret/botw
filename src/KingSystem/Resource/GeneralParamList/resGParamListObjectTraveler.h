#pragma once

#include <utility/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

#define STR5_HELP(A, B, C, D, E) A##B##C##D##E
#define STR5(a, b, c, d, e) STR5_HELP(a, b, c, d, e)

#define ROUTE_POINT(PT)                                    \
    PT(0, 1)   PT(1, 2)   PT(2, 3)   PT(3, 4)   PT(4, 5)   \
    PT(5, 6)   PT(6, 7)   PT(7, 8)   PT(8, 9)   PT(9, 10)  \
    PT(10, 11) PT(11, 12) PT(12, 13) PT(13, 14) PT(14, 15) \
    PT(15, 16) PT(16, 17) PT(17, 18) PT(18, 19) PT(19, 20) \
    PT(20, 21) PT(21, 22) PT(22, 23) PT(23, 24) PT(24, 25) \
    PT(25, 26) PT(26, 27) PT(27, 28) PT(28, 29)

namespace ksys::res {

class GParamListObjectTraveler : public GParamListObject {
public:
    struct RoutePoint {
        RoutePoint();

        template <s32 I>
        KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

        struct DirectionInfo {
            template <s32 From, s32 To>
            KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

            agl::utl::Parameter<sead::SafeString> mEntryPoint;
            agl::utl::Parameter<f32> mWaitFrame;
            agl::utl::Parameter<sead::SafeString> mSchedule;
            agl::utl::Parameter<sead::SafeString> mMoveAS;
            agl::utl::Parameter<sead::SafeString> mWaitAS;
        };

        agl::utl::Parameter<sead::SafeString> mName;
        // i to i+1
        DirectionInfo mForward;
        // i+1 to i
        DirectionInfo mBackward;
    };
    static constexpr size_t NumRoutePoints = 29;

    GParamListObjectTraveler();
    const char* getName() const override { return "Traveler"; }

#define ROUTE_POINT_FUNCTION_DECL(FROM, TO)                                                        \
    const float& STR5(getRoutePoint, FROM, to, TO, WaitFrame()) const;                             \
    const float& STR5(getRoutePoint, TO, to, FROM, WaitFrame()) const;
    ROUTE_POINT(ROUTE_POINT_FUNCTION_DECL)
#undef ROUTE_POINT_FUNCTION_DECL

    agl::utl::Parameter<sead::SafeString> mAppearGameDataName;
    agl::utl::Parameter<sead::SafeString> mDeleteGameDataName;
    agl::utl::Parameter<sead::SafeString> mRouteType;
    agl::utl::Parameter<sead::SafeString> mRideHorseName;
    agl::utl::Parameter<bool> mIsLeadHorse;
    agl::utl::Parameter<s32> mHorseGearLevel;

    struct RoutePoints {
        RoutePoints();
        auto& operator[](s32 i) { return reinterpret_cast<RoutePoint&>(mStorage[i]); }
        auto& operator[](s32 i) const { return reinterpret_cast<const RoutePoint&>(mStorage[i]); }
        auto data() { return reinterpret_cast<RoutePoint*>(&mStorage[0]); }

    private:
        std::aligned_storage_t<sizeof(RoutePoint), alignof(RoutePoint)> mStorage[NumRoutePoints];
    };
    RoutePoints mRoutePoints;
    agl::utl::Parameter<sead::SafeString> mRoutePoint29Name;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectTraveler, 0x3148);

}  // namespace ksys::res
