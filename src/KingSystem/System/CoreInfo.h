#pragma once

namespace ksys {

// Must be a compile-time constant because this value is used as an array size in various places.
// This limitation is why we cannot just use sead::CoreInfo::getNumCores() everywhere.
constexpr int NumCores = 3;

}  // namespace ksys
