#include <evfl/ResEventFlowFile.h>
#include <evfl/ResFlowchart.h>
#include <evfl/ResTimeline.h>
#include <ore/Array.h>
#include <ore/RelocationTable.h>
#include <ore/ResDic.h>
#include <ore/ResEndian.h>
#include <ore/StringPool.h>
#include <string_view>

namespace evfl {

using ore::SwapEndian;

template <typename T>
constexpr T MakeMagic(std::string_view magic) {
    T result = 0;
    for (size_t i = 0; i < magic.length(); ++i)
        result |= T(magic[i]) << (8 * i);
    return result;
}

bool ResEventFlowFile::IsValid(void* data) {
    return static_cast<ore::BinaryFileHeader*>(data)->IsValid(MakeMagic<u64>("BFEVFL"), 0, 3, 0, 0);
}

ResEventFlowFile* ResEventFlowFile::ResCast(void* data) {
    auto* file = static_cast<ResEventFlowFile*>(data);
    file->Relocate();
    return file;
}

void ResEventFlowFile::Relocate() {
    if (header.IsRelocated())
        return;

    auto* table = header.GetRelocationTable();
    table->Relocate();
    header.SetRelocated(true);
}

void ResEventFlowFile::Unrelocate() {
    if (!header.IsRelocated())
        return;

    auto* table = header.GetRelocationTable();
    table->Unrelocate();
    header.SetRelocated(false);
}

static void SwapEndian(ore::ResEndian* endian, ore::StringPool* pool) {
    ore::BinString* str = pool->GetFirstString();
    const int num_strings = pool->GetLength();
    if (endian->is_serializing) {
        for (int i = 0; i < num_strings; ++i) {
            auto* next = str->NextString();
            SwapEndian(&str->length);
            str = next;
        }
    } else {
        for (int i = 0; i < num_strings; ++i) {
            SwapEndian(&str->length);
            str = str->NextString();
        }
    }
}

template <typename T>
static void SwapEndian(ore::ResEndian* endian, ore::BinTPtr<T>* ptr) {
    if (auto* value = ptr->ToPtr(endian->base))
        SwapEndian(endian, value);
}

static void SwapEndianForFileData(ore::ResEndian* endian, ResEventFlowFile* file) {
    ore::Array<ore::BinTPtr<ResFlowchart>> flowcharts{file->flowcharts.ToPtr(endian->base),
                                                      file->num_flowcharts};
    for (auto& flowchart : flowcharts)
        SwapEndian(endian, &flowchart);

    if (auto* flowchart_names = file->flowchart_names.ToPtr(endian->base))
        SwapEndian(endian, flowchart_names);

    ore::Array<ore::BinTPtr<ResTimeline>> timelines{file->timelines.ToPtr(endian->base),
                                                    file->num_timelines};
    for (auto& timeline : timelines)
        SwapEndian(endian, &timeline);

    if (auto* timeline_names = file->timeline_names.ToPtr(endian->base))
        SwapEndian(endian, timeline_names);

    auto* string_pool =
        static_cast<ore::StringPool*>(file->header.FindFirstBlock(MakeMagic<u32>("STR ")));
    SwapEndian(endian, string_pool);
}

void SwapEndian(ore::ResEndian* endian, ResEventFlowFile* file) {
    const auto swap_fields = [&] {
        SwapEndian(&file->header.bom);
        SwapEndian(&file->num_flowcharts);
        SwapEndian(&file->num_timelines);
    };

    if (endian->is_serializing) {
        SwapEndianForFileData(endian, file);
        swap_fields();
    } else {
        swap_fields();
        SwapEndianForFileData(endian, file);
    }
}

}  // namespace evfl
