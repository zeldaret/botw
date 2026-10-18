#include "KingSystem/ActorSystem/Awareness/actAwarenessMiscUtils.h"
#include <utility/aglParameter.h>

namespace ksys::act {

u32 calcAwarenessHash(const sead::SafeString& key) {
    return agl::utl::ParameterBase::calcHash(key);
}

}  // namespace ksys::act
