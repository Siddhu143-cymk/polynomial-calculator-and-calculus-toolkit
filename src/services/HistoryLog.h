#ifndef HISTORY_LOG_H
#define HISTORY_LOG_H

#include "../datastructures/HistoryQueue.h"
#include "../models/HistoryEntry.h"
#include <mutex>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Thread-safe operation history logger.
 * Owned by ApiController/Server to track all incoming actions chronologically.
 */
class HistoryLog {
private:
    HistoryQueue queue;
    mutable std::mutex logMutex;
    int nextId;

public:
    HistoryLog();

    /**
     * @brief Log an operation entry in a thread-safe manner.
     */
    void logOperation(const std::string& operation, const nlohmann::json& inputs, const nlohmann::json& result);

    /**
     * @brief Get copy of all history entries.
     */
    std::vector<HistoryEntry> getHistory() const;

    /**
     * @brief Clear operation history.
     */
    void clear();

    /**
     * @brief Get total entries count.
     */
    size_t size() const;
};

#endif // HISTORY_LOG_H
