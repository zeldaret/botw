#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

bool stubbedLogFunction() {
    return true;
}

bool returnFalse() {
    return false;
}

bool returnFalse2(const sead::SafeString&) {
    return false;
}

s32 getDefaultAlignment() {
    return 8;
}

}  // namespace ksys::res
