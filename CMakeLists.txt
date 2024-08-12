cmake_minimum_required (VERSION 3.20)
project(PersonalDB)
add_executable (PersonalDB main.cpp "personal.cpp" "personal.h")

set(PostgreSQL_ADDITIONAL_VERSIONS "16")

add_subdirectory ("C:\\Program Files\\libpq++\\libpqxx-7.9.1\\libpqxx-7.9.1" libpqxx-build)

target_link_libraries (PersonalDB PRIVATE pqxx)

target_compile_features(PersonalDB PRIVATE cxx_std_17)

set(CMAKE_CXX_STANDARD 23)