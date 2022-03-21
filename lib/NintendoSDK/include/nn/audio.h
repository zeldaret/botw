/**
 * @file audio.h
 * @brief Audio implementation.
 */

#pragma once

#include <nn/os.h>
#include <nn/types.h>

namespace nn {
namespace audio {
// Common audio
struct AudioDeviceName {
    char raw_name[0x100];
};

static_assert(sizeof(AudioDeviceName) == 0x100);

void AcquireAudioDeviceSwitchNotification(nn::os::SystemEvent* event);
s32 ListAudioDeviceName(nn::audio::AudioDeviceName* buffer, s32 bufferCount);
Result SetAudioDeviceOutputVolume(nn::audio::AudioDeviceName const* device, float volume);
u32 GetActiveChannelCount();

struct AudioRendererConfig {
    u64* _0;
    u64* _8;
    u64* _10;
    u64* _18;
    u64* _20;
    u64* _28;
    u64* _30;
    u64* _38;
    u64* _40;
    u64* _48;
    u64* _50;
};

enum AudioRendererRenderingDevice : u32 {
    AudioRendererRenderingDevice_Cpu,
    AudioRendererRenderingDevice_Dsp
};

enum AudioRendererExecutionMode : u32 {
    AudioRendererExecutionMode_Manual,
    AudioRendererExecutionMode_Auto,
};

enum SampleFormat : u32 {
    SampleFormat_Invalid,
    SampleFormat_PcmInt8,
    SampleFormat_PcmInt16,
    SampleFormat_PcmInt24,
    SampleFormat_PcmInt32,
    SampleFormat_PcmFloat,
    SampleFormat_Adpcm,
};

enum MemoryPoolState : u32 {
    MemoryPoolState_Invalid,
    MemoryPoolState_New,
    MemoryPoolState_RequestDetach,
    MemoryPoolState_Detached,
    MemoryPoolState_RequestAttach,
    MemoryPoolState_Attached,
    MemoryPoolState_Released,
};

struct AudioRendererParameter {
    u32 sampleRate;
    u32 sampleCount;
    u32 mixBufferCount;
    u32 subMixCount;
    u32 voiceCount;
    u32 sinkCount;
    u32 effectCount;
    u32 performanceFrameCount;
    bool isVoiceDropEnabled;
    u32 splitterCount;
    u32 splitterSendChannelCount;
    AudioRendererRenderingDevice renderingDevice;
    AudioRendererExecutionMode executionMode;
    u32 _34;
    u32 revision;
};

static_assert(sizeof(AudioRendererParameter) == 0x3C);

struct BiquadFilterParameter {
    bool enabled;
    s16 numerator[3];
    s16 denominator[2];
};

static_assert(sizeof(BiquadFilterParameter) == 0xC);

struct WaveBuffer {
    void* buffer;
    size_t bufferSize;
    s32 startSampleOffset;
    s32 endSampleOffset;
    bool shouldLoop;
    bool isEndOfStream;
    void* context;
    size_t contextSize;
};

static_assert(sizeof(WaveBuffer) == 0x30);

struct AudioRendererHandle {
    u64* _0;
    u64* _8;
};

struct MemoryPoolType {
    u64* _0;
};

struct CircularBufferSinkType {
    u64* _0;
};

struct AuxType {
    u64* _0;
};

struct DelayType {
    u64* _0;
};

struct FinalMixType {
    u64* _0;
};

struct SubMixType {
    u64* _0;
};

struct VoiceType {
    u64* _0;

    enum PlayState : u32 {
        PlayState_Start,
        PlayState_Stop,
        PlayState_Pause,
    };
};

struct DeviceSinkType {
    u64* _0;
};

// Audio Renderer base APIs
void InitializeAudioRendererParameter(nn::audio::AudioRendererParameter* inParameter);
bool IsValidAudioRendererParameter(nn::audio::AudioRendererParameter const& inParameter);
size_t GetAudioRendererWorkBufferSize(nn::audio::AudioRendererParameter const& inParameter);
size_t GetAudioRendererConfigWorkBufferSize(nn::audio::AudioRendererParameter const& inParameter);
Result InitializeAudioRendererConfig(nn::audio::AudioRendererConfig* outConfig,
                                     nn::audio::AudioRendererParameter const& inParameter,
                                     void* buffer, size_t bufferSize);
Result OpenAudioRenderer(nn::audio::AudioRendererHandle* outHandle,
                         nn::audio::AudioRendererParameter const& inParameter, void* workBuffer,
                         size_t workBufferSize);
void CloseAudioRenderer(nn::audio::AudioRendererHandle handle);
Result StartAudioRenderer(nn::audio::AudioRendererHandle handle);
Result StopAudioRenderer(nn::audio::AudioRendererHandle handle);
Result RequestUpdateAudioRenderer(nn::audio::AudioRendererHandle handle,
                                  nn::audio::AudioRendererConfig const* config);

// Audio Renderer MemoryPool APIs
bool IsMemoryPoolAttached(nn::audio::MemoryPoolType const* pool);
bool RequestAttachMemoryPool(nn::audio::MemoryPoolType* pool);
bool RequestDetachMemoryPool(nn::audio::MemoryPoolType* pool);
bool AcquireMemoryPool(nn::audio::AudioRendererConfig* config, nn::audio::MemoryPoolType* outPool,
                       void* address, size_t size);
void ReleaseMemoryPool(nn::audio::AudioRendererConfig* config, nn::audio::MemoryPoolType* pool);
void* GetMemoryPoolAddress(nn::audio::MemoryPoolType const* pool);
size_t GetMemoryPoolSize(nn::audio::MemoryPoolType const* pool);
MemoryPoolState GetMemoryPoolState(nn::audio::MemoryPoolType const* pool);

// Audio Renderer Effect APIs
void SetDelayInputOutput(nn::audio::DelayType* delay, s8 const* input, s8 const* output, s32 count);
void* RemoveDelay(nn::audio::AudioRendererConfig* config, nn::audio::DelayType* delay,
                  nn::audio::FinalMixType* mix);
void* RemoveDelay(nn::audio::AudioRendererConfig* config, nn::audio::DelayType* delay,
                  nn::audio::SubMixType* mix);
bool IsDelayRemovable(nn::audio::DelayType* delay);

size_t GetRequiredBufferSizeForAuxSendReturnBuffer(nn::audio::AudioRendererParameter const* config,
                                                   s32 mixBufferFrameCount, s32 channelCount);
Result AddAux(nn::audio::AudioRendererConfig* config, nn::audio::AuxType* aux,
              nn::audio::FinalMixType* mix, void* sendBuffer, void* returnBuffer,
              size_t bufferSize);
Result AddAux(nn::audio::AudioRendererConfig* config, nn::audio::AuxType* aux,
              nn::audio::SubMixType* mix, void* sendBuffer, void* returnBuffer, size_t bufferSize);
void RemoveAux(nn::audio::AudioRendererConfig* config, nn::audio::AuxType* aux,
               nn::audio::FinalMixType* mix);
void RemoveAux(nn::audio::AudioRendererConfig* config, nn::audio::AuxType* aux,
               nn::audio::SubMixType* mix);
void SetAuxEnabled(nn::audio::AuxType* aux, bool enable);
void SetAuxInputOutput(nn::audio::AuxType* aux, s8 const* input, s8 const* output, s32 count);
bool IsAuxRemovable(nn::audio::AuxType* aux);
s32 GetAuxSampleCount(nn::audio::AuxType const* aux);
s32 GetAuxSampleRate(nn::audio::AuxType const* aux);
s32 ReadAuxSendBuffer(nn::audio::AuxType* aux, s32* buffer, s32 count);
s32 WriteAuxReturnBuffer(nn::audio::AuxType* aux, s32 const* buffer, s32 count);

// Audio Renderer Performance APIs
size_t
GetRequiredBufferSizeForPerformanceFrames(nn::audio::AudioRendererParameter const& inParameter);
void* SetPerformanceFrameBuffer(nn::audio::AudioRendererConfig* config, void* buffer,
                                size_t bufferSize);

enum PerformanceEntryType : u8 {
    PerformanceEntryType_Invalid,
    PerformanceEntryType_Voice,
    PerformanceEntryType_SubMix,
    PerformanceEntryType_FinalMix,
    PerformanceEntryType_Sink
};

struct PerformanceEntry {
    s32 nodeId;
    s32 startTime;
    s32 processingTime;
    PerformanceEntryType entryType;
};

static_assert(sizeof(PerformanceEntry) == 0x10);

enum PerformanceDetailType : u8 {
    PerformanceDetailType_Unknown,
    PerformanceDetailType_PcmInt16,
    PerformanceDetailType_Adpcm,
    PerformanceDetailType_VolumeRamp,
    PerformanceDetailType_BiquadFilter,
    PerformanceDetailType_Mix,
    PerformanceDetailType_Delay,
    PerformanceDetailType_Aux,
    PerformanceDetailType_Reverb,
    PerformanceDetailType_Reverb3d,
    PerformanceDetailType_PcmFloat
};

struct PerformanceDetail {
    s32 nodeId;
    s32 startTime;
    s32 processingTime;
    PerformanceDetailType detailType;
    PerformanceEntryType entryType;
};

static_assert(sizeof(PerformanceDetail) == 0x10);

class PerformanceInfo {
public:
    PerformanceInfo();
    ~PerformanceInfo();

    bool SetBuffer(void const* buffer, size_t bufferSize);
    bool MoveToNextFrame();
    s32 GetTotalProcessingTime();
    PerformanceEntry GetEntries(s32* count);
    PerformanceDetail GetDetails(s32* count);

private:
    void* buffer;
    size_t bufferSize;
    void* header;
    PerformanceEntry* entries;
    PerformanceDetail* details;
};

static_assert(sizeof(PerformanceInfo) == 0x28);

// Audio Renderer Sink APIs
Result AddDeviceSink(nn::audio::AudioRendererConfig* config, nn::audio::DeviceSinkType* sink,
                     nn::audio::FinalMixType* mix, s8 const* input, s32 inputCount,
                     char const* deviceName);
void RemoveDeviceSink(nn::audio::AudioRendererConfig* config, nn::audio::DeviceSinkType* sink,
                      nn::audio::FinalMixType* mix);
u32 GetSinkNodeId(nn::audio::DeviceSinkType const* sink);

Result AddCircularBufferSink(nn::audio::AudioRendererConfig* config,
                             nn::audio::CircularBufferSinkType* sink, nn::audio::FinalMixType* mix,
                             s8 const* input, s32 inputCount, void* buffer, size_t bufferSize,
                             nn::audio::SampleFormat sampleFormat);
void RemoveCircularBufferSink(nn::audio::AudioRendererConfig* config,
                              nn::audio::CircularBufferSinkType* sink,
                              nn::audio::FinalMixType* mix);
size_t ReadCircularBufferSink(nn::audio::CircularBufferSinkType* sink, void* buffer,
                              size_t buffer_size);
u32 GetSinkNodeId(nn::audio::CircularBufferSinkType const* sink);
size_t
GetRequiredBufferSizeForCircularBufferSink(nn::audio::AudioRendererParameter const* inParameter,
                                           s32 inputCount, s32 frameCount,
                                           nn::audio::SampleFormat sampleFormat);

// Audio Renderer Mix APIs
bool AcquireFinalMix(nn::audio::AudioRendererConfig* config, nn::audio::FinalMixType* mix,
                     s32 bufferCount);
bool AcquireSubMix(nn::audio::AudioRendererConfig* config, nn::audio::SubMixType* mix,
                   s32 sampleRate, s32 bufferCount);
void ReleaseSubMix(nn::audio::AudioRendererConfig* config, nn::audio::SubMixType* mix);
void SetSubMixDestination(nn::audio::AudioRendererConfig* config, nn::audio::SubMixType* source,
                          nn::audio::FinalMixType* destination);
void SetSubMixDestination(nn::audio::AudioRendererConfig* config, nn::audio::SubMixType* source,
                          nn::audio::SubMixType* destination);
void SetSubMixMixVolume(nn::audio::SubMixType* source, nn::audio::FinalMixType* destination,
                        float volume, s32 sourceIndex, s32 destinationIndex);
void SetSubMixMixVolume(nn::audio::SubMixType* source, nn::audio::SubMixType* destination,
                        float volume, s32 sourceIndex, s32 destinationIndex);
u32 GetSubMixNodeId(nn::audio::SubMixType const* mix);

// Audio Renderer Voice APIs
Result AcquireVoiceSlot(nn::audio::AudioRendererConfig* config, nn::audio::VoiceType* voice,
                        s32 sampleRate, s32 channelCount, nn::audio::SampleFormat sampleFormat,
                        s32 priority, void const* buffer, size_t bufferSize);
void ReleaseVoiceSlot(nn::audio::AudioRendererConfig* config, nn::audio::VoiceType* voice);
bool IsVoiceValid(nn::audio::VoiceType const* voice);
bool IsVoiceDroppedFlagOn(nn::audio::VoiceType const* voice);
void ResetVoiceDroppedFlag(nn::audio::VoiceType* voice);
void SetVoiceDestination(nn::audio::AudioRendererConfig* config, nn::audio::VoiceType* voice,
                         nn::audio::FinalMixType* mix);
void SetVoiceDestination(nn::audio::AudioRendererConfig* config, nn::audio::VoiceType* voice,
                         nn::audio::SubMixType* mix);
void SetVoiceVolume(nn::audio::VoiceType* config, float volume);
void SetVoicePitch(nn::audio::VoiceType* config, float pitch);
void SetVoicePlayState(nn::audio::VoiceType* voice, nn::audio::VoiceType::PlayState state);
void SetVoicePriority(nn::audio::VoiceType* voice, s32 priority);
void SetVoiceBiquadFilterParameter(nn::audio::VoiceType* voice, s32 index,
                                   nn::audio::BiquadFilterParameter const& biquadFilterParameter);
void SetVoiceMixVolume(nn::audio::VoiceType* voice, nn::audio::FinalMixType* mix, float volume,
                       int sourceIndex, int destinationIndex);
void SetVoiceMixVolume(nn::audio::VoiceType* voice, nn::audio::SubMixType* mix, float volume,
                       int sourceIndex, int destinationIndex);
nn::audio::VoiceType::PlayState GetVoicePlayState(nn::audio::VoiceType const* voice);
s32 GetVoicePriority(nn::audio::VoiceType const* voice);
u64 GetVoicePlayedSampleCount(nn::audio::VoiceType const* voice);
u32 GetVoiceNodeId(nn::audio::VoiceType const* voice);
bool AppendWaveBuffer(nn::audio::VoiceType* voice, nn::audio::WaveBuffer const* waveBuffer);
nn::audio::WaveBuffer* GetReleasedWaveBuffer(nn::audio::VoiceType* voice);
};  // namespace audio
};  // namespace nn