#pragma once

#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

// TODO
class RagdollController {
public:
    void update();

    u32 sub_7101221CC4();
    void sub_7101221728(ContactLayer layer);
    void sub_71012217A8();
};

}  // namespace ksys::phys
