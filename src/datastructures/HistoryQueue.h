#ifndef HISTORY_QUEUE_H
#define HISTORY_QUEUE_H

#include <queue>
#include <vector>
#include <cstddef>
#include "../models/HistoryEntry.h"

/**
 * @brief Custom thin queue wrapper for sequential chronological operation history storage.
 */
class HistoryQueue {
private:
    std::queue<HistoryEntry> entries;

public:
    HistoryQueue() = default;

    void enqueue(const HistoryEntry& entry);
    HistoryEntry dequeue();
    bool empty() const;
    size_t size() const;
    std::vector<HistoryEntry> getAll() const;
    void clear();
};

#endif // HISTORY_QUEUE_H
