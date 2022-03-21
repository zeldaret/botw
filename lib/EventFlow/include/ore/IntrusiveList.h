#pragma once

#include <utility>

namespace ore {

class IntrusiveListNode {
public:
    constexpr explicit IntrusiveListNode() { m_prev = m_next = this; }

    IntrusiveListNode(const IntrusiveListNode&) = delete;
    auto operator=(const IntrusiveListNode&) = delete;

    IntrusiveListNode(IntrusiveListNode&& other) noexcept { *this = std::move(other); }
    IntrusiveListNode& operator=(IntrusiveListNode&& other) noexcept {
        auto* prev = other.m_prev;
        other.m_prev = this;
        prev->m_next = this;
        m_prev = prev;
        m_next = &other;
        other.Erase();
        return *this;
    }

    IntrusiveListNode* Prev() const { return m_prev; }
    IntrusiveListNode* Next() const { return m_next; }
    bool IsLinked() const { return Prev() || Next(); }

    void Erase() {
        auto* next = m_next;
        auto* next_prev = next->m_prev;
        m_prev->m_next = next;
        next->m_prev = m_prev;
        // This is a circular list.
        next_prev->m_next = this;
        m_prev = next_prev;
    }

    void InsertFront(IntrusiveListNode* node) {
        auto* prev = node->m_prev;
        node->m_prev = m_prev;
        prev->m_next = this;
        m_prev->m_next = node;
        m_prev = prev;
    }

private:
    template <typename T>
    friend class IntrusiveList;

    IntrusiveListNode* m_prev{};
    IntrusiveListNode* m_next{};
};

template <typename T>
class IntrusiveList {
public:
    void SetOffset(int offset) { m_offset = offset; }

    bool Empty() const { return m_node.m_next == &m_node; }
    T* Front() { return NodeToItemWithNullCheck(m_node.m_next); }
    T* Back() { return NodeToItemWithNullCheck(m_node.m_prev); }
    const T* Front() const { return NodeToItemWithNullCheck(m_node.m_next); }
    const T* Back() const { return NodeToItemWithNullCheck(m_node.m_prev); }

    void Erase(T* item) { ItemToNode(item)->Erase(); }

    void InsertFront(T* item) { m_node.InsertFront(ItemToNode(item)); }

private:
    IntrusiveListNode* ItemToNode(T* item) const {
        return reinterpret_cast<IntrusiveListNode*>(reinterpret_cast<char*>(item) + m_offset);
    }

    const IntrusiveListNode* ItemToNode(const T* item) const {
        return reinterpret_cast<const IntrusiveListNode*>(reinterpret_cast<const char*>(item) +
                                                          m_offset);
    }

    T* NodeToItem(IntrusiveListNode* node) const {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(node) - m_offset);
    }

    const T* NodeToItem(const IntrusiveListNode* node) const {
        return reinterpret_cast<const T*>(reinterpret_cast<const char*>(node) - m_offset);
    }

    T* NodeToItemWithNullCheck(IntrusiveListNode* node) const {
        return node == &m_node ? nullptr : NodeToItem(node);
    }

    const T* NodeToItemWithNullCheck(const IntrusiveListNode* node) const {
        return node == &m_node ? nullptr : NodeToItem(node);
    }

    IntrusiveListNode m_node;
    int m_offset = -1;
};

}  // namespace ore
