#pragma once

#include <nn/types.h>

namespace nn::svc {
struct Handle {
    u32 handle;

    Handle(u32 h) { handle = h; }

    Handle() : Handle(0) {}

    operator u32() const { return handle; }
};

}  // namespace nn::svc
