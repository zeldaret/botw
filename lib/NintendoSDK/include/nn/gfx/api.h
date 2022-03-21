/**
 * @file api.h
 * @brief GFX API version and typing.
 */

#pragma once

namespace nn {
namespace gfx {
// passes both ApiType<4> and ApiVersion<8>
template <typename T, typename T2>
class ApiVariation {};

// usually passed as just a 4
template <int T>
class ApiType {};

// usually passed as just a 8
template <int T>
class ApiVersion {};
};  // namespace gfx
};  // namespace nn