#include "ApiController.h"
#include "../utils/JsonHelper.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <exception>

using json = nlohmann::json;

ApiController::ApiController() {
    setupRoutes();
}

void ApiController::setupRoutes() {
    // Enable CORS for all routes
    svr.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        if (req.method == "OPTIONS") {
            res.status = 200;
            return httplib::Server::HandlerResponse::Handled;
        }
        return httplib::Server::HandlerResponse::Unhandled;
    });

    // 1. POST /polynomial/parse
    svr.Post("/polynomial/parse", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("expression") || !body["expression"].is_string()) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Missing 'expression' field in request body", 400).dump(), "application/json");
                return;
            }

            std::string expr = body["expression"];
            Polynomial poly = parser.parse(expr);
            json resultData = poly.toJson();

            historyLog.logOperation("parse", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 2. POST /polynomial/add
    svr.Post("/polynomial/add", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("a") || !body.contains("b")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'a' and 'b' polynomials", 400).dump(), "application/json");
                return;
            }

            Polynomial polyA = parser.parse(body["a"]);
            Polynomial polyB = parser.parse(body["b"]);
            Polynomial resultPoly = arithmeticService.add(polyA, polyB);

            json resultData = resultPoly.toJson();
            historyLog.logOperation("add", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 3. POST /polynomial/subtract
    svr.Post("/polynomial/subtract", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("a") || !body.contains("b")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'a' and 'b' polynomials", 400).dump(), "application/json");
                return;
            }

            Polynomial polyA = parser.parse(body["a"]);
            Polynomial polyB = parser.parse(body["b"]);
            Polynomial resultPoly = arithmeticService.subtract(polyA, polyB);

            json resultData = resultPoly.toJson();
            historyLog.logOperation("subtract", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 4. POST /polynomial/multiply
    svr.Post("/polynomial/multiply", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("a") || !body.contains("b")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'a' and 'b' polynomials", 400).dump(), "application/json");
                return;
            }

            Polynomial polyA = parser.parse(body["a"]);
            Polynomial polyB = parser.parse(body["b"]);
            Polynomial resultPoly = arithmeticService.multiply(polyA, polyB);

            json resultData = resultPoly.toJson();
            historyLog.logOperation("multiply", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 5. POST /polynomial/divide
    svr.Post("/polynomial/divide", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("a") || !body.contains("b")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'a' (dividend) and 'b' (divisor)", 400).dump(), "application/json");
                return;
            }

            Polynomial dividend = parser.parse(body["a"]);
            Polynomial divisor = parser.parse(body["b"]);

            DivisionResult divRes = arithmeticService.divide(dividend, divisor);

            json resultData = {
                {"quotient", divRes.quotient.toJson()},
                {"remainder", divRes.remainder.toJson()}
            };

            historyLog.logOperation("divide", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 6. POST /polynomial/evaluate
    svr.Post("/polynomial/evaluate", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("expression") || !body.contains("x")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'expression' and numeric 'x' value", 400).dump(), "application/json");
                return;
            }

            Polynomial poly = parser.parse(body["expression"]);
            double xVal = body["x"].get<double>();
            double value = poly.evaluate(xVal);

            json resultData = {
                {"x", xVal},
                {"value", value}
            };

            historyLog.logOperation("evaluate", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 7. POST /calculus/derivative
    svr.Post("/calculus/derivative", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("expression")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'expression'", 400).dump(), "application/json");
                return;
            }

            Polynomial poly = parser.parse(body["expression"]);
            Polynomial dPoly = calculusEngine.differentiate(poly);

            json resultData = dPoly.toJson();
            historyLog.logOperation("derivative", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 8. POST /calculus/integral
    svr.Post("/calculus/integral", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("expression")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'expression'", 400).dump(), "application/json");
                return;
            }

            Polynomial poly = parser.parse(body["expression"]);

            bool hasA = body.contains("a") && !body["a"].is_null();
            bool hasB = body.contains("b") && !body["b"].is_null();

            json resultData;
            if (hasA && hasB) {
                double a = body["a"].get<double>();
                double b = body["b"].get<double>();
                double defValue = calculusEngine.integrateDefinite(poly, a, b);

                resultData = {
                    {"type", "definite"},
                    {"a", a},
                    {"b", b},
                    {"value", defValue}
                };
            } else {
                double C = 0.0;
                if (body.contains("C") && !body["C"].is_null()) {
                    C = body["C"].get<double>();
                }
                Polynomial indPoly = calculusEngine.integrateIndefinite(poly, C);

                resultData = {
                    {"type", "indefinite"},
                    {"C", C},
                    {"polynomial", indPoly.toJson()}
                };
            }

            historyLog.logOperation("integral", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 9. POST /calculus/roots
    svr.Post("/calculus/roots", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            json body = json::parse(req.body);
            if (!body.contains("expression")) {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Request body must contain 'expression'", 400).dump(), "application/json");
                return;
            }

            Polynomial poly = parser.parse(body["expression"]);
            double guess = 1.0;
            if (body.contains("guess") && !body["guess"].is_null()) {
                guess = body["guess"].get<double>();
            }

            std::vector<double> roots = calculusEngine.findRoots(poly, guess);
            json rootsArr = json::array();
            for (double r : roots) {
                rootsArr.push_back(r);
            }

            json resultData = {
                {"initial_guess", guess},
                {"roots", rootsArr}
            };

            historyLog.logOperation("roots", body, resultData);

            res.status = 200;
            res.set_content(JsonHelper::createSuccessResponse(resultData).dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 400).dump(), "application/json");
        }
    });

    // 10. GET /history
    svr.Get("/history", [this](const httplib::Request& req, httplib::Response& res) {

        try {
            std::vector<HistoryEntry> history = historyLog.getHistory();
            json historyArr = json::array();
            for (const auto& entry : history) {
                historyArr.push_back(entry.toJson());
            }

            json responseJson = {
                {"status", "success"},
                {"count", history.size()},
                {"history", historyArr}
            };

            res.status = 200;
            res.set_content(responseJson.dump(2), "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(JsonHelper::createErrorResponse(e.what(), 500).dump(), "application/json");
        }
    });
}

bool ApiController::listen(const std::string& host, int port) {
    std::cout << "========================================================\n";
    std::cout << " Polynomial Calculator + Calculus Toolkit REST API Server\n";
    std::cout << " Listening on http://" << host << ":" << port << "\n";
    std::cout << " Press Ctrl+C to terminate\n";
    std::cout << "========================================================\n" << std::flush;
    return svr.listen(host, port);
}

void ApiController::stop() {
    svr.stop();
}

HistoryLog& ApiController::getHistoryLog() {
    return historyLog;
}
