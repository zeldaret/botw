#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

class KingEditorComponent {
public:
    virtual const char* getName() const = 0;
    virtual void syncData() = 0;
};

// FIXME
class KingEditor {
    SEAD_SINGLETON_DISPOSER(KingEditor)

public:
    void registerComponent(KingEditorComponent* component);
};

}  // namespace ksys
