cmake_minimum_required(VERSION 3.0)
project(ed2_TabelaHash)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage") #codecov
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.travis/cmake) # modulo para codecov
include(CodeCoverage)

find_package(GTest REQUIRED)


file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

file(GLOB_RECURSE TEST_FILES "tests/*.cpp" "tests/*.h")





add_executable(runUnitTests  ${TEST_FILES} ${SOURCE_FILES} )

target_link_libraries(runUnitTests GTest::GTest GTest::Main)

setup_target_for_coverage(coverage  runUnitTests  coverage)