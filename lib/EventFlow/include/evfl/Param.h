#pragma once

#include <evfl/EvflAllocator.h>
#include <ore/Array.h>
#include <ore/BinaryFile.h>
#include <ore/Buffer.h>
#include <ore/EnumUtil.h>
#include <ore/IterRange.h>
#include <ore/ResMetaData.h>
#include <ore/StringView.h>
#include <ore/Types.h>

namespace ore {
struct ResDic;
struct ResMetaData;
}  // namespace ore

namespace evfl {

class FlowchartContext;
class FlowchartObj;
struct ResEntryPoint;

class MetaDataPack {
public:
    ORE_ENUM(DataType, kInt, kBool, kFloat, kString, kWString)

    struct Entry {
        union Value {
            bool b;
            int i;
            float f;
            const char* str;
            const wchar_t* wstr;
        };

        bool IsKey(const ore::StringView& other) const { return ore::StringView(key) == other; }

        const char* key;
        Value value;
        DataType::Type type;
    };

    class Builder {
    public:
        void CalcMemSize();
        bool Build(MetaDataPack* pack, ore::Buffer buffer);
        void SetNumEntries(int num) { m_num_entries = num; }
        int GetRequiredSize() const { return m_required_size; }

    private:
        int m_num_entries = 16;
        int m_required_size = 0;
        int m_alignment_real = 16;
        int m_entries_byte_size = 0;
        int m_alignment = 16;
        int _14 = 0;
        int m_buffer_offset = -1;
    };

    void AddInt(const char* key, int value);
    void AddBool(const char* key, bool value);
    void AddFloat(const char* key, float value);
    void AddStringPtr(const char* key, const char* value);
    void AddWStringPtr(const char* key, const wchar_t* value);

    bool FindInt(int* value, const ore::StringView& key) const;
    bool FindBool(bool* value, const ore::StringView& key) const;
    bool FindFloat(float* value, const ore::StringView& key) const;
    bool FindString(ore::StringView* value, const ore::StringView& key) const;
    bool FindWString(ore::WStringView* value, const ore::StringView& key) const;

    ore::ResMetaData::DataType::Type GetType(const ore::StringView& key) const;

private:
    Entry* Find(const ore::StringView& key) const;
    Entry& AddEntry() { return m_entries[m_entries_num++]; }

    ore::Array<Entry> GetEntries() const { return {m_entries, m_entries_num}; }

    ore::Buffer m_buffer{};
    Entry* m_entries{};
    int m_entries_num{};
    int m_entries_capacity{};
};

class VariablePack {
public:
    using VariableType = ore::ResMetaData::DataType::Type;

    struct Entry {
        union Value {
            void* dummy;
            int i;
            float f;
            ore::DynArrayList<int>* int_array;
            ore::DynArrayList<float>* float_array;
        };

        Value value;
        VariableType type;
    };

    VariablePack();
    ~VariablePack();
    VariablePack(const VariablePack&) = delete;
    auto operator=(const VariablePack&) = delete;

    void Init(AllocateArg arg, const ResEntryPoint* entry_point);

    Entry* GetVariableEntry(const ore::StringView& name);
    const Entry* GetVariableEntry(const ore::StringView& name) const;
    VariableType GetVariableType(const ore::StringView& name) const;
    ore::StringView GetVariableName(int idx) const;
    int GetVariableCount() const;

    bool Contains(const ore::StringView& name) const;

    bool FindInt(int* value, const ore::StringView& name) const;
    bool FindBool(bool* value, const ore::StringView& name) const;
    bool FindFloat(float* value, const ore::StringView& name) const;
    bool FindIntList(ore::DynArrayList<int>** value, const ore::StringView& name) const;
    bool FindFloatList(ore::DynArrayList<float>** value, const ore::StringView& name) const;

    int GetInt(const ore::StringView& name) const;
    bool GetBool(const ore::StringView& name) const;
    float GetFloat(const ore::StringView& name) const;
    ore::DynArrayList<int>* GetIntList(const ore::StringView& name) const;
    ore::DynArrayList<float>* GetFloatList(const ore::StringView& name) const;

    void SetInt(const ore::StringView& name, int value);
    void SetFloat(const ore::StringView& name, float value);
    void SetBool(const ore::StringView& name, bool value);

private:
    void Dispose();
    ore::Allocator* GetAllocator() { return &m_allocator; }

    const ore::ResDic* m_names = nullptr;
    ore::Array<Entry> m_variables;
    EvflAllocator m_allocator;
};

class ParamAccessor {
public:
    using Type = ore::ResMetaData::DataType::Type;
    using IntRange = ore::IterRange<const int*>;
    using FloatRange = ore::IterRange<const float*>;
    using StringRange = ore::IterRange<const ore::BinTPtr<ore::BinString>*>;
    using WStringRange = ore::IterRange<const ore::BinTPtr<ore::BinWString>*>;

    explicit ParamAccessor(const ore::ResMetaData* metadata);
    explicit ParamAccessor(const FlowchartContext* context, int node_idx);

    const ore::ResMetaData* GetFrontResMetaData() const;
    int GetParamCount() const;
    ore::StringView GetParamName(int idx) const;
    Type GetParamType(int idx) const;

    /// @param out_metadata  Must be nonnull.
    /// @param out_metadata_pack  Must be nonnull.
    /// @param out_variable_pack  Must be nonnull.
    /// @param out_obj  May be null.
    /// @param argument  Name of the argument to search for.
    ore::StringView TrackBackArgument(const ore::ResMetaData** out_metadata,
                                      const MetaDataPack** out_metadata_pack,
                                      const VariablePack** out_variable_pack,
                                      FlowchartObj** out_obj,
                                      const ore::StringView& argument) const;

    int GetInt(int idx) const;
    bool FindInt(int* value, const ore::StringView& name) const;

    bool GetBool(int idx) const;
    bool FindBool(bool* value, const ore::StringView& name) const;

    float GetFloat(int idx) const;
    bool FindFloat(float* value, const ore::StringView& name) const;

    ore::StringView GetString(int idx) const;
    bool FindString(ore::StringView* value, const ore::StringView& name) const;

    ore::WStringView GetWString(int idx) const;
    bool FindWString(ore::WStringView* value, const ore::StringView& name) const;

    IntRange GetIntArray(int idx) const;
    bool FindIntArray(IntRange* value, const ore::StringView& name) const;

    FloatRange GetFloatArray(int idx) const;
    bool FindFloatArray(FloatRange* value, const ore::StringView& name) const;

    StringRange GetStringArray(int idx) const;
    bool FindStringArray(StringRange* value, const ore::StringView& name) const;

    WStringRange GetWStringArray(int idx) const;
    bool FindWStringArray(WStringRange* value, const ore::StringView& name) const;

    bool FindActorIdentifier(ore::StringView* actor_name, ore::StringView* actor_sub_name,
                             const ore::StringView& name) const;

private:
    const ore::ResMetaData* m_metadata = nullptr;
    const FlowchartContext* m_context = nullptr;
    int m_node_idx = -1;
    u32 m_node_counter = -1;
};

}  // namespace evfl
