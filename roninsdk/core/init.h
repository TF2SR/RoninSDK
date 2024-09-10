#pragma once

void SDK_Init();
void SDK_Shutdown();

void Systems_Init();
void Systems_Shutdown();

void Winsock_Init();
void Winsock_Shutdown();
void QuerySystemInfo();
void CheckCPU();

bool AllocateModule(string strModule);
void DetourScanModule(string strModule);
void DetourAttachModule(string strModule);
void DetourRegister();
void DetourAddress();