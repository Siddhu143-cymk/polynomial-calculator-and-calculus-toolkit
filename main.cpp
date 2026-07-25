#include "src/api/ApiController.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int port = 8080;
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    ApiController controller;
    if (!controller.listen("0.0.0.0", port)) {
        std::cerr << "Failed to start HTTP server on port " << port << std::endl;
        return 1;
    }

    return 0;
}
