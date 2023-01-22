#pragma once

#include <math/seadVectorFwd.h>
#include "KingSystem/System/PlayReportMgr.h"

namespace uking {

void reportKorok(const sead::Vector3f& position);
void reportDungeon(const sead::SafeString& name, const sead::SafeString& event);

// TODO: More functions

class PlayReport : public ksys::PlayReport {
public:
    PlayReport(const sead::FixedSafeString<32>& event_id, s32 num_entries, sead::Heap* heap);

    void addMapType();
};

}  // namespace uking
