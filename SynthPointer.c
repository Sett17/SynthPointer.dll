#define _WIN32_WINNT_WIN10
#define NTDDI_VERSION NTDDI_WIN10_RS5
#include "SynthPointer.h"
#include <stdio.h>
#include <windows.h>

typedef enum {
  PEN_STATE_MASK = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN | POINTER_FLAG_UP | POINTER_FLAG_UPDATE),
  PEN_HOVER = (POINTER_FLAG_INRANGE | POINTER_FLAG_UPDATE),
  PEN_DOWN = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN),
  PEN_CONTACT = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_UPDATE),
  PEN_UP = (POINTER_FLAG_INRANGE | POINTER_FLAG_UP),
  PEN_ENDHOVER = (POINTER_FLAG_UPDATE),
} PEN_STATES;

HSYNTHETICPOINTERDEVICE CreateSynthPointer() {
  HSYNTHETICPOINTERDEVICE device = CreateSyntheticPointerDevice(PT_PEN, 1, POINTER_FEEDBACK_DEFAULT);
  if (device == NULL) {
    _handleError();
  }
  return device;
}

POINTER_TYPE_INFO *GetDefaultPointerTypeInfo() {
  POINTER_TYPE_INFO *typeInfo = (POINTER_TYPE_INFO *)malloc(sizeof(POINTER_TYPE_INFO));
  POINTER_PEN_INFO penInfo = {0};
  POINTER_INFO info = {0};

  info.pointerType = PT_PEN;

  penInfo.pointerInfo = info;

  typeInfo->type = PT_PEN;
  typeInfo->penInfo = penInfo;

  return typeInfo;
}

void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed) {
  DEVMODE devMode;
  devMode.dmSize = sizeof(DEVMODE);
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
  int screenWidth = devMode.dmPelsWidth;
  int screenHeight = devMode.dmPelsHeight;

  int screenX = (int)(x * screenWidth);
  int screenY = (int)(y * screenHeight);

  POINT global = _ScreenToGlobal(screenX, screenY, screenId);

  info->penInfo.pointerInfo.ptPixelLocation.x = global.x;
  info->penInfo.pointerInfo.ptPixelLocation.y = global.y;
  info->penInfo.pointerInfo.pointerFlags = PEN_HOVER;
  info->penInfo.penFlags |= (buttonPressed) ? PEN_FLAG_BARREL : 0;

  _injectPointer(device, info);
}

void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed, UINT32 pressure) {
  DEVMODE devMode;
  devMode.dmSize = sizeof(DEVMODE);
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
  int screenWidth = devMode.dmPelsWidth;
  int screenHeight = devMode.dmPelsHeight;

  int screenX = (int)(x * screenWidth);
  int screenY = (int)(y * screenHeight);

  POINT global = _ScreenToGlobal(screenX, screenY, screenId);

  info->penInfo.pointerInfo.ptPixelLocation.x = global.x;
  info->penInfo.pointerInfo.ptPixelLocation.y = global.y;
  info->penInfo.pointerInfo.pointerFlags = PEN_CONTACT;
  info->penInfo.penFlags |= (buttonPressed) ? PEN_FLAG_BARREL : 0;
  info->penInfo.penMask = PEN_MASK_PRESSURE;
  info->penInfo.pressure = pressure;

  _injectPointer(device, info);
}

void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info) {
  info->penInfo.pointerInfo.pointerFlags = PEN_ENDHOVER;
  _injectPointer(device, info);
}

void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info) {
  info->penInfo.pointerInfo.pointerFlags = PEN_DOWN;
  _injectPointer(device, info);
}

void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info) {
  info->penInfo.pointerInfo.pointerFlags = PEN_UP;
  _injectPointer(device, info);
}

int ScreenCount() {
    return GetSystemMetrics(SM_CMONITORS);
}

typedef struct {
  int screenID;
  POINT offset;
} _ScreenData;

static int _CurrentEnumScreen = 0;
static POINT _globalOrigin = {0, 0};

BOOL CALLBACK _MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
  _ScreenData *data = (_ScreenData *)dwData;

  if (lprcMonitor->left < _globalOrigin.x) {
    _globalOrigin.x = lprcMonitor->left;
  }
  if (lprcMonitor->top < _globalOrigin.y) {
    _globalOrigin.y = lprcMonitor->top;
  }

  if (_CurrentEnumScreen == data->screenID) {
    data->offset.x = lprcMonitor->left;
    data->offset.y = lprcMonitor->top;
  };

  _CurrentEnumScreen++;
  return TRUE;
}

POINT _ScreenToGlobal(int screenX, int screenY, int screen) {
  if (screen < 0 || screen >= GetSystemMetrics(SM_CMONITORS)) {
    POINT p = {screenX, screenY};
    return p;
  }

  _globalOrigin.x = 0;
  _globalOrigin.y = 0;
  _CurrentEnumScreen = 0;

  _ScreenData data = {screen, {0, 0}};
  data.screenID = screen;
  EnumDisplayMonitors(NULL, NULL, _MonitorEnumProc, (LPARAM)&data);

  POINT ret = {screenX + data.offset.x - _globalOrigin.x, screenY + data.offset.y - _globalOrigin.y};
  return ret;
}

void _injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info) {
  if (!InjectSyntheticPointerInput(device, info, 1)) {
    _handleError();
  }
}

void _handleError() {
  LPVOID lpMsgBuf;
  DWORD dw = GetLastError();

  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
          FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      dw,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR)&lpMsgBuf,
      0, NULL);

  printf("Error %lu: %s\n", dw, (char *)lpMsgBuf);

  LocalFree(lpMsgBuf);
}
