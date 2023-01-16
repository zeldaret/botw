#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/ProductReporter.h"
#include "KingSystem/Utils/Types.h"

namespace nn::prepo {
class PlayReport;
}

namespace ksys {

namespace act {
class PlayerLink;
}

class ProductReporter;

class PlayReportMgr {
    SEAD_SINGLETON_DISPOSER(PlayReportMgr)
    PlayReportMgr() = default;
    virtual ~PlayReportMgr();

public:
    void init(sead::Heap* heap);

    void calc();

    void reportDebug(const sead::SafeString& message, const sead::SafeString& data);

    int auto0() const;
    PlayerTrackReporter* auto2() const;
    
    void auto1();
    void auto3();
    void x();

    ProductReporter* getReporter() const { return mReporter; }

    bool get30() const { return _30; }
    void set30(bool arg_30) { _30 = arg_30; }

private:
    ProductReporter* mReporter = nullptr;
    bool _30 = false;
    act::PlayerLink* mPlayerLink = nullptr;
};
KSYS_CHECK_SIZE_NX150(PlayReportMgr, 0x40);

class PlayReport {
public:
    inline PlayReport(const sead::FixedSafeString<32>& event_id, s32 num_entries, sead::Heap* heap) {
        init(num_entries, heap);
        sead::FixedSafeString<32> event_id_ = event_id;
        setEventId(event_id_);
    }

    ~PlayReport();

    bool setEventId(sead::BufferedSafeString& event_id);

    bool add(const sead::FixedSafeString<48>& key, u32 value);
    bool add(const sead::FixedSafeString<48>& key, s32 value);
    bool add(const sead::FixedSafeString<48>& key, f32 value);
    bool add(const sead::FixedSafeString<48>& key, const sead::SafeString& value);
    bool save();

private:
    void init(s32 num_entries, sead::Heap* heap);

    bool mHasNinPrepoReport = false;
    nn::prepo::PlayReport* mNinPlayReport = nullptr;
    sead::Buffer<u8> mBuffer;
};
KSYS_CHECK_SIZE_NX150(PlayReport, 0x20);

}  // namespace ksys
