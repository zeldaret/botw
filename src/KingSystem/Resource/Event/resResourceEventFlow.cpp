#include "KingSystem/Resource/Event/resResourceEventFlow.h"
#include <evfl/ResEventFlowFile.h>
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

void EventFlowchart::registerFactory(sead::Heap* heap) {
    registerEntryFactory(new (heap) EntryFactory<EventFlowchart>(1.0, sizeof(EventFlowchart)),
                         "bfevfl");
}

void EventFlowchart::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {
    m_res = evfl::ResEventFlowFile::ResCast(buffer);
}

void EventFlowchart::onDestroy_() {
    if (m_res) {
        m_res->Unrelocate();
        m_res = nullptr;
    }
}

EventFlowchart::~EventFlowchart() = default;

void EventTimeline::registerFactory(sead::Heap* heap) {
    registerEntryFactory(new (heap) EntryFactory<EventTimeline>(1.0, sizeof(EventTimeline)),
                         "bfevtm");
}

void EventTimeline::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {
    m_res = evfl::ResEventFlowFile::ResCast(buffer);
}

void EventTimeline::onDestroy_() {
    if (m_res) {
        m_res->Unrelocate();
        m_res = nullptr;
    }
}

EventTimeline::~EventTimeline() = default;

}  // namespace ksys::res
