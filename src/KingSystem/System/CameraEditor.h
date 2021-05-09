#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

// Completely stubbed in release builds
class CameraEditor {
    SEAD_SINGLETON_DISPOSER(CameraEditor)
    CameraEditor() = default;
};

}  // namespace ksys
