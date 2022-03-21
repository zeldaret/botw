#pragma once

#include <ore/BinaryFile.h>
#include <ore/EnumUtil.h>
#include <ore/Types.h>

namespace ore {
struct ResEndian;
struct ResMetaData;
}  // namespace ore

namespace evfl {

struct ResActor;

struct ResTrigger {
    u16 clip_index;
    u8 trigger_type;
};

struct ResCut {
    float start_time;
    ore::BinTPtr<ore::BinString> name;
    ore::BinTPtr<ore::ResMetaData> params;
};

struct ResClip {
    float start_time;
    float duration;
    u16 actor_index;
    u16 actor_action_index;
    u8 _c;
    ore::BinTPtr<ore::ResMetaData> params;
};

struct ResOneshot {
    float time;
    u16 actor_index;
    u16 actor_action_index;
    u32 _8;
    u32 _c;
    ore::BinTPtr<ore::ResMetaData> params;
};

struct ResSubtimeline {
    ore::BinTPtr<ore::BinString> name;
};

struct ResTimeline {
    /// 'TLIN'
    u32 magic;
    /// String pool offset (relative to this structure)
    int string_pool_offset;
    u32 reserved_8;
    u32 reserved_c;
    float duration;
    u16 num_actors;
    u16 num_actions;
    u16 num_clips;
    u16 num_oneshots;
    u16 num_subtimelines;
    u16 num_cuts;
    ore::BinTPtr<ore::BinString> name;
    ore::BinTPtr<ResActor> actors;
    ore::BinTPtr<ResClip> clips;
    ore::BinTPtr<ResOneshot> oneshots;
    ore::BinTPtr<ResTrigger> triggers;
    ore::BinTPtr<ResSubtimeline> subtimelines;
    ore::BinTPtr<ResCut> cuts;
    ore::BinTPtr<ore::ResMetaData> params;
};

void SwapEndian(ore::ResEndian* endian, ResTrigger* trigger);
void SwapEndian(ore::ResEndian* endian, ResCut* cut);
void SwapEndian(ore::ResEndian* endian, ResClip* clip);
void SwapEndian(ore::ResEndian* endian, ResOneshot* oneshot);
void SwapEndian(ore::ResEndian* endian, ResSubtimeline* subtimeline);
void SwapEndian(ore::ResEndian* endian, ResTimeline* timeline);

}  // namespace evfl
