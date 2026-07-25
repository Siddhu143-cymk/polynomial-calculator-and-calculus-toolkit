#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <nlohmann/json.hpp>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace JsonHelper {

inline std::string getIsoTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&in_time_t), "%Y-%m-%dT%H:%M:%SZ");
    return ss.str();
}

inline nlohmann::json createSuccessResponse(const nlohmann::json& data) {
    return nlohmann::json{
        {"status", "success"},
        {"data", data}
    };
}

inline nlohmann::json createErrorResponse(const std::string& message, int code = 400) {
    return nlohmann::json{
        {"status", "error"},
        {"code", code},
        {"message", message}
    };
}

} // namespace JsonHelper

#endif // JSON_HELPER_H
