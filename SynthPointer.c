#define _WIN32_WINNT_WIN10
#define NTDDI_VERSION NTDDI_WIN10_RS5
#include <stdio.h>
#include <windows.h>
#include "SynthPointer.h"

HSYNTHETICPOINTERDEVICE CreateSynthPointer() {
    // TODO: Implement this function
    return NULL;
}

POINTER_TYPE_INFO GetDefaultPointerTypeInfo() {
    // TODO: Implement this function
    POINTER_TYPE_INFO info;
    return info;
}

void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId) {
    // TODO: Implement this function
}

void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId) {
    // TODO: Implement this function
}

void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    // TODO: Implement this function
}

void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    // TODO: Implement this function
}

void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    // TODO: Implement this function
}

int* getScreenIds(int* count) {
    // TODO: Implement this function
    return NULL;
}

POINT calculateScreenOffset(int screenId) {
    // TODO: Implement this function
    POINT offset;
    return offset;
}

void injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    // TODO: Implement this function
}

void handleError(DWORD errorCode) {
    // TODO: Implement this function
}
