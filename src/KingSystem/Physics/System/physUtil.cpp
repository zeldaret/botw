#include "KingSystem/Physics/System/physUtil.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

MotionType motionTypeFromText(const sead::SafeString& text) {
    static constexpr const char* texts[] = {
        "Dynamic",
        "Fixed",
        "Keyframed",
    };
    static_assert(int(MotionType::Dynamic) == 0);
    static_assert(int(MotionType::Fixed) == 1);
    static_assert(int(MotionType::Keyframed) == 2);

    int type = 0;
    for (const char* type_text : texts) {
        if (text == type_text)
            return static_cast<MotionType>(type);
        ++type;
    }
    return MotionType::Unknown;
}

}  // namespace ksys::phys
