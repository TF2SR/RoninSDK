cmake_minimum_required (VERSION 3.11)

include(FetchContent)

project ("roninsdk")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VS_PLATFORM_TOOLSET v143)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game)

include_directories(. thirdparty)

add_subdirectory("roninlauncher")
add_subdirectory("roninsdk")

set(HTTP_ONLY ON)
set(CURL_STATICLIB ON)
set(BUILD_CURL_EXE OFF)
set(CURL_DISABLE_INSTALL ON)
set(USE_LIBIDN2 OFF)

add_subdirectory("thirdparty/detours")

FetchContent_Declare(
	curl
	GIT_REPOSITORY https://github.com/curl/curl.git
	GIT_TAG 83bedbd730d62b83744cc26fa0433d3f6e2e4cd6
)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)

FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG 27cb4c76708608465c413f6d0e6b8d99a4d84302 # 1.14.1
)

FetchContent_MakeAvailable(curl json spdlog)
