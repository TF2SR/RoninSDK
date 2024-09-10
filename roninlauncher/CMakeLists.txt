
set(CMAKE_WIN32_EXECUTABLE True)

add_executable(roninlauncher "main.cpp" "resources.rc")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:8000000")

target_link_libraries(roninlauncher PUBLIC Shlwapi)
