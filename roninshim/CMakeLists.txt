
set(CMAKE_WIN32_EXECUTABLE True)

add_library(roninshim SHARED "main.cpp")

target_link_libraries(roninshim PUBLIC shlwapi)

set_target_properties(roninshim PROPERTIES
    OUTPUT_NAME Northstar
    PREFIX ""
)


set_target_properties(
    roninshim
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ronin
)
