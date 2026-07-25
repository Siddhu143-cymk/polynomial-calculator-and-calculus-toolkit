cmake_minimum_required(VERSION 3.14)
project(PolynomialCalculusToolkit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00 WIN32_LEAN_AND_MEAN NOMINMAX CPPHTTPLIB_NO_FILE_MAPPING)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# Core library sources
set(CORE_SOURCES
    src/datastructures/SparsePolyMap.cpp
    src/datastructures/CoeffVector.cpp
    src/datastructures/HistoryQueue.cpp
    src/models/Term.cpp
    src/models/Polynomial.cpp
    src/models/HistoryEntry.cpp
    src/utils/Tokenizer.cpp
    src/parser/PolynomialParser.cpp
    src/services/ArithmeticService.cpp
    src/services/CalculusEngine.cpp
    src/services/HistoryLog.cpp
    src/api/ApiController.cpp
)

# Windows socket library linking for cpp-httplib
if(WIN32)
    set(SOCKET_LIBS ws2_32 wsock32)
else()
    set(SOCKET_LIBS pthread)
endif()

# Main server executable
add_executable(poly_calc_server main.cpp ${CORE_SOURCES})
target_link_libraries(poly_calc_server PRIVATE ${SOCKET_LIBS})

# Unit test executables
add_executable(test_models tests/test_models.cpp ${CORE_SOURCES})
target_link_libraries(test_models PRIVATE ${SOCKET_LIBS})

add_executable(test_parser tests/test_parser.cpp ${CORE_SOURCES})
target_link_libraries(test_parser PRIVATE ${SOCKET_LIBS})

add_executable(test_arithmetic tests/test_arithmetic.cpp ${CORE_SOURCES})
target_link_libraries(test_arithmetic PRIVATE ${SOCKET_LIBS})

add_executable(test_calculus tests/test_calculus.cpp ${CORE_SOURCES})
target_link_libraries(test_calculus PRIVATE ${SOCKET_LIBS})

add_executable(test_history tests/test_history.cpp ${CORE_SOURCES})
target_link_libraries(test_history PRIVATE ${SOCKET_LIBS})
