
set(SOURCES
    version.cpp
    include/j1939/version.hpp
)

add_library(j1939 STATIC ${SOURCES})
target_include_directories(j1939 PUBLIC include)