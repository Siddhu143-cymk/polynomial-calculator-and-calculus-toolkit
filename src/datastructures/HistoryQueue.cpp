#include "HistoryQueue.h"
#include <stdexcept>

void HistoryQueue::enqueue(const HistoryEntry& entry) {
    entries.push(entry);
}

HistoryEntry HistoryQueue::dequeue() {
    if (entries.empty()) {
        throw std::out_of_range("HistoryQueue is empty");
    }
    HistoryEntry front = entries.front();
    entries.pop();
    return front;
}

bool HistoryQueue::empty() const {
    return entries.empty();
}

size_t HistoryQueue::size() const {
    return entries.size();
}

std::vector<HistoryEntry> HistoryQueue::getAll() const {
    std::vector<HistoryEntry> list;
    std::queue<HistoryEntry> temp = entries;
    while (!temp.empty()) {
        list.push_back(temp.front());
        temp.pop();
    }
    return list;
}

void HistoryQueue::clear() {
    std::queue<HistoryEntry> emptyQueue;
    std::swap(entries, emptyQueue);
}
