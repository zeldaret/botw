#pragma once
#include <basis/seadTypes.h>
#include <nn/oe.h>

namespace ksys::frm {

// FIXME: incomplete
struct Framework {
    static Framework* instance();

    u8 _0[0x278];
    nn::oe::OperationMode mOperationMode;
};

}  // namespace ksys::frm