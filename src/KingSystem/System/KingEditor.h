#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class KingEditorComponent {
public:
    virtual const char* getName() const = 0;
    virtual void syncData(char* data) = 0;

    void log(const char* message, void* x = {}, int y = {}) const;

    static constexpr size_t getListNodeOffset() { return offsetof(KingEditorComponent, mListNode); }

private:
    sead::ListNode mListNode;
};

// FIXME
class KingEditor {
    SEAD_SINGLETON_DISPOSER(KingEditor)
    KingEditor() = default;

public:
    void init(sead::Heap* heap);
    void calc();
    void registerComponent(KingEditorComponent* component);
    void log(const char* system, const char* message, void* = {}, int = {});

    u32 get88() const { return _88; }

private:
    sead::OffsetList<KingEditorComponent> mComponents;
    sead::ListNode mListNode;
    sead::CriticalSection mCS;
    u32 _88 = 0;
    u32 _8c = 0;
    void* _90 = nullptr;
    u32 _98 = 0;
    void* _a0 = nullptr;
    void* _a8 = nullptr;
    void* mPlayerLink = nullptr;
    bool _b8 = false;
};
KSYS_CHECK_SIZE_NX150(KingEditor, 0xc0);

}  // namespace ksys
