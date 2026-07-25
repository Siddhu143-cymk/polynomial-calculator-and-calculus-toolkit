#ifndef API_CONTROLLER_H
#define API_CONTROLLER_H

#include "../third_party/httplib.h"
#include "../parser/PolynomialParser.h"
#include "../services/ArithmeticService.h"
#include "../services/CalculusEngine.h"
#include "../services/HistoryLog.h"
#include <memory>

/**
 * @brief REST API Controller registering HTTP handlers and mapping JSON requests to backend services.
 */
class ApiController {
private:
    httplib::Server svr;
    PolynomialParser parser;
    ArithmeticService arithmeticService;
    CalculusEngine calculusEngine;
    HistoryLog historyLog;

    void setupRoutes();

public:
    ApiController();

    /**
     * @brief Starts the HTTP server on specified host and port.
     */
    bool listen(const std::string& host, int port);

    /**
     * @brief Stops the HTTP server.
     */
    void stop();

    /**
     * @brief Access internal HistoryLog for testing or inspection.
     */
    HistoryLog& getHistoryLog();
};

#endif // API_CONTROLLER_H
