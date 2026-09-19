#pragma once

#include <string>

void UpdateChecker_Start();
const char* UpdateChecker_Poll();
const std::string& UpdateChecker_LatestVersion();
void UpdateChecker_Shutdown();
