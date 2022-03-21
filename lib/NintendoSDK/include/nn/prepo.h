#pragma once

#include <nn/types.h>

namespace nn::account {
class Uid;
}

namespace nn::prepo {

namespace detail {
class PlayReportGenerator {
public:
    PlayReportGenerator() = default;
    void Initialize();

private:
    void* m_Data = nullptr;
};
}  // namespace detail

enum class TransmissionStatus {};

class PlayReport {
public:
    PlayReport();
    explicit PlayReport(const char* event_id);

    Result SetEventId(const char* event_id);
    void SetBuffer(void* buffer, size_t size);
    void Clear();

    Result Add(const char* key, s64 value);
    Result Add(const char* key, f64 value);
    Result Add(const char* key, const char* value);

    Result Save();
    Result Save(const account::Uid& uid);

    s32 GetCount() const;

    static u32 CalcBufferSize(s32 num_entries) { return size_t(0x82) * num_entries + 3; }

private:
    char m_EventId[32];
    void* m_Buffer;
    size_t m_BufferSize;
    detail::PlayReportGenerator m_Generator;
};

void Initialize();

Result RequestImmediateTransmission();
Result GetTransmissionStatus(TransmissionStatus* status);

Result ClearStorage();
Result SetOperationMode(s64 mode);
Result IsUserAgreementCheckEnabled(bool* enabled);
Result SetUserAgreementCheckEnabled(bool enabled);
Result GetStorageUsage(s64*, s64*);

}  // namespace nn::prepo
