#define _WIN32_WINNT_WIN10
#define NTDDI_VERSION NTDDI_WIN10_RS5
#include "SynthPointer.h"
#include <stdio.h>
#include <windows.h>

HSYNTHETICPOINTERDEVICE CreateSynthPointer() {
  HSYNTHETICPOINTERDEVICE device =  CreateSyntheticPointerDevice(PT_PEN, 1, POINTER_FEEDBACK_DEFAULT);
  if (device == NULL) {
    handleError();
  }
  return device;
}

POINTER_TYPE_INFO GetDefaultPointerTypeInfo() {
  POINTER_TYPE_INFO typeInfo = {0};
  POINTER_PEN_INFO penInfo = {0};
  POINTER_INFO info = {0};

  info.pointerType = PT_PEN;

  penInfo.pointerInfo = info;

  typeInfo.type = PT_PEN;
  typeInfo.penInfo = penInfo;

  return typeInfo;
}

void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId) {
    POINT offset = calculateScreenOffset(screenId);

    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
    int screenWidth = devMode.dmPelsWidth;
    int screenHeight = devMode.dmPelsHeight;

    int screenX = (int)(x * screenWidth) + offset.x;
    int screenY = (int)(y * screenHeight) + offset.y;

    info->penInfo.pointerInfo.ptPixelLocation.x = screenX;
    info->penInfo.pointerInfo.ptPixelLocation.y = screenY;
    info->penInfo.pointerInfo.pointerFlags = PEN_HOVER;

    injectPointer(device, info);
}

void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId) {
    POINT offset = calculateScreenOffset(screenId);

    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
    int screenWidth = devMode.dmPelsWidth;
    int screenHeight = devMode.dmPelsHeight;

    int screenX = (int)(x * screenWidth) + offset.x;
    int screenY = (int)(y * screenHeight) + offset.y;

    info->penInfo.pointerInfo.ptPixelLocation.x = screenX;
    info->penInfo.pointerInfo.ptPixelLocation.y = screenY;
    info->penInfo.pointerInfo.pointerFlags = PEN_CONTACT;

    injectPointer(device, info);
}

void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    info->penInfo.pointerInfo.pointerFlags = PEN_ENDHOVER;
    injectPointer(device, info);
}

void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    info->penInfo.pointerInfo.pointerFlags = PEN_DOWN;
    injectPointer(device, info);
}

void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info) {
    info->penInfo.pointerInfo.pointerFlags = PEN_UP;
    injectPointer(device, info);
}

typedef struct {
    int targetId;
    int currentId;
    POINT offset;
} MonitorOffsetData;

BOOL CALLBACK MonitorCountEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    int *count = (int*)dwData;
    (*count)++;
    return TRUE;
}

BOOL CALLBACK MonitorOffsetEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    MonitorOffsetData* data = (MonitorOffsetData*)dwData;
    if (data->currentId == data->targetId) {
        data->offset.x = lprcMonitor->left;
        data->offset.y = lprcMonitor->top;
        return FALSE;
    }
    data->currentId++;
    return TRUE;
}

int* GetScreenIds(int* count) {
    *count = 0;
    EnumDisplayMonitors(NULL, NULL, MonitorCountEnumProc, (LPARAM)count);
    int* screenIds = malloc(sizeof(int) * (*count));
    for (int i = 0; i < *count; i++) {
        screenIds[i] = i;
    }
    return screenIds;
}

POINT calculateScreenOffset(int screenId) {
    MonitorOffsetData data;
    data.targetId = screenId;
    data.currentId = 0;
    EnumDisplayMonitors(NULL, NULL, MonitorOffsetEnumProc, (LPARAM)&data);
    return data.offset;
}

void injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info) {
    if (!InjectSyntheticPointerInput(device, info, 1)) {
      handleError();
    }
}

void handleError() {
  LPVOID lpMsgBuf;
  DWORD dw = GetLastError(); 

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    dw,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &lpMsgBuf,
    0, NULL );

  printf("Error %lu: %s\n", dw, (char *)lpMsgBuf);

  // Free the buffer.
  LocalFree(lpMsgBuf);
}
