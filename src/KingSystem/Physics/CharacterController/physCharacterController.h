#pragma once
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class CharacterController {
public:
    void sub_7100F5EC30();
    void sub_7100F60604();
    void enableCollisionMaybe_0(ContactLayer);
};

}  // namespace ksys::phys
