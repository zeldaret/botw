#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

class KingEditorComponent {
public:
    virtual const char* getName() const = 0;
    virtual void syncData(const char* data) = 0;

    void* _8 = nullptr;
    void* _10 = nullptr;
};

// FIXME
class KingEditor {
    SEAD_SINGLETON_DISPOSER(KingEditor)
    KingEditor() = default;

public:
    void registerComponent(KingEditorComponent* component);
};

}  // namespace ksys
