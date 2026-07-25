#ifndef HISTORY_ENTRY_H
#define HISTORY_ENTRY_H

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Represents a single logged API operation history record.
 */
class HistoryEntry {
private:
    int id;
    std::string timestamp;
    std::string operation;
    nlohmann::json inputs;
    nlohmann::json result;

public:
    HistoryEntry();
    HistoryEntry(int id, const std::string& timestamp, const std::string& operation,
                 const nlohmann::json& inputs, const nlohmann::json& result);

    int getId() const;
    std::string getTimestamp() const;
    std::string getOperation() const;
    nlohmann::json getInputs() const;
    nlohmann::json getResult() const;

    nlohmann::json toJson() const;
};

#endif // HISTORY_ENTRY_H
