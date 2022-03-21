#pragma once

#include <ore/BinaryFile.h>
#include <ore/Types.h>

namespace ore {
struct ResDic;
struct ResEndian;
}  // namespace ore

namespace evfl {

struct ResFlowchart;
struct ResTimeline;

struct ResEventFlowFile {
    /// data must be a pointer to a buffer of size >= 0x20.
    static bool IsValid(void* data);
    /// data must be a valid ResEventFlowFile.
    static ResEventFlowFile* ResCast(void* data);

    void Relocate();
    void Unrelocate();

    ore::BinaryFileHeader header;
    u16 num_flowcharts;
    u16 num_timelines;
    ore::BinTPtr<ore::BinTPtr<ResFlowchart>> flowcharts;
    ore::BinTPtr<ore::ResDic> flowchart_names;
    ore::BinTPtr<ore::BinTPtr<ResTimeline>> timelines;
    ore::BinTPtr<ore::ResDic> timeline_names;
};

void SwapEndian(ore::ResEndian* endian, ResEventFlowFile* file);

}  // namespace evfl
