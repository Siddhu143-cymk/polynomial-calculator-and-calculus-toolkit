#include "HistoryEntry.h"

HistoryEntry::HistoryEntry() : id(0) {}

HistoryEntry::HistoryEntry(int id, const std::string& timestamp, const std::string& operation,
                             const nlohmann::json& inputs, const nlohmann::json& result)
    : id(id), timestamp(timestamp), operation(operation), inputs(inputs), result(result) {}

int HistoryEntry::getId() const { return id; }
std::string HistoryEntry::getTimestamp() const { return timestamp; }
std::string HistoryEntry::getOperation() const { return operation; }
nlohmann::json HistoryEntry::getInputs() const { return inputs; }
nlohmann::json HistoryEntry::getResult() const { return result; }

nlohmann::json HistoryEntry::toJson() const {
    return nlohmann::json{
        {"id", id},
        {"timestamp", timestamp},
        {"operation", operation},
        {"inputs", inputs},
        {"result", result}
    };
}
