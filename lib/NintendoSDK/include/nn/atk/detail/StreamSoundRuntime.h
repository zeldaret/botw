/**
 * @file StreamSoundRuntime.h
 * @brief Stream sound runtime information.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
namespace detail {
class StreamSoundRuntime {
public:
    StreamSoundRuntime();
    ~StreamSoundRuntime();

    u8 _0[0xB0];
};
};  // namespace detail
};  // namespace atk
};  // namespace nn