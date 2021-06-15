#pragma once

#include "KingSystem/Resource/resResource.h"

namespace evfl {
struct ResEventFlowFile;
}

namespace ksys::res {

class EventFlowchart : public Resource {
    SEAD_RTTI_OVERRIDE(EventFlowchart, Resource)

public:
    EventFlowchart() = default;
    ~EventFlowchart() override;

    static void registerFactory(sead::Heap* heap);

    evfl::ResEventFlowFile* getRes() const { return m_res; }

private:
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    void onDestroy_() override;

    evfl::ResEventFlowFile* m_res = nullptr;
};

class EventTimeline : public Resource {
    SEAD_RTTI_OVERRIDE(EventTimeline, Resource)

public:
    EventTimeline() = default;
    ~EventTimeline() override;

    static void registerFactory(sead::Heap* heap);

    evfl::ResEventFlowFile* getRes() const { return m_res; }

private:
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    void onDestroy_() override;

    evfl::ResEventFlowFile* m_res = nullptr;
};

}  // namespace ksys::res
