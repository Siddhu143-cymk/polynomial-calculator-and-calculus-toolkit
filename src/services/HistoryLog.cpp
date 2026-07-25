#include "HistoryLog.h"
#include "../utils/JsonHelper.h"

HistoryLog::HistoryLog() : nextId(1) {}

void HistoryLog::logOperation(const std::string& operation, const nlohmann::json& inputs, const nlohmann::json& result) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::string timestamp = JsonHelper::getIsoTimestamp();
    HistoryEntry entry(nextId++, timestamp, operation, inputs, result);
    queue.enqueue(entry);
}

std::vector<HistoryEntry> HistoryLog::getHistory() const {
    std::lock_guard<std::mutex> lock(logMutex);
    return queue.getAll();
}

void HistoryLog::clear() {
    std::lock_guard<std::mutex> lock(logMutex);
    queue.clear();
    nextId = 1;
}

size_t HistoryLog::size() const {
    std::lock_guard<std::mutex> lock(logMutex);
    return queue.size();
}
