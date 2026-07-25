#include "../src/services/HistoryLog.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>

void testHistory() {
    HistoryLog log;

    log.logOperation("parse", {{"expression", "3x^2+2x-5"}}, {{"pretty", "3x^2 + 2x - 5"}});
    log.logOperation("evaluate", {{"expression", "3x^2+2x-5"}, {"x", 2.0}}, {{"value", 11.0}});

    assert(log.size() == 2);
    auto history = log.getHistory();
    assert(history[0].getOperation() == "parse");
    assert(history[1].getOperation() == "evaluate");

    // Test concurrent logging safety
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&log, i]() {
            log.logOperation("concurrent_op", {{"index", i}}, {{"result", "ok"}});
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(log.size() == 12);

    std::cout << "[PASS] testHistory\n";
}

int main() {
    testHistory();
    std::cout << "All HistoryLog unit tests passed successfully!\n";
    return 0;
}
