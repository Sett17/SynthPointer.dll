#include "../SynthPointer.h"
#include "unity.h"
#include <windows.h>

HSYNTHETICPOINTERDEVICE device;
POINTER_TYPE_INFO *info;
DEVMODE devMode;

typedef enum {
  PEN_STATE_MASK = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN | POINTER_FLAG_UP | POINTER_FLAG_UPDATE),
  PEN_HOVER = (POINTER_FLAG_INRANGE | POINTER_FLAG_UPDATE),
  PEN_DOWN = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN),
  PEN_CONTACT = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_UPDATE),
  PEN_UP = (POINTER_FLAG_INRANGE | POINTER_FLAG_UP),
  PEN_ENDHOVER = (POINTER_FLAG_UPDATE),
} PEN_STATES;

void setUp(void) {
  device = CreateSynthPointer();
  info = GetDefaultPointerTypeInfo();
  devMode.dmSize = sizeof(DEVMODE);
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
}

void tearDown(void) {
}

void test_DBG(void) {
  POINT global0 = _ScreenToGlobal(0, 0, 0);
  POINT global1 = _ScreenToGlobal(0, 0, 1);

  printf("global0: %d, %d\n", global0.x, global0.y);
  printf("global1: %d, %d\n", global1.x, global1.y);

  info->penInfo.pointerInfo.ptPixelLocation.x = global1.x;
  info->penInfo.pointerInfo.ptPixelLocation.y = global1.y;
  info->penInfo.pointerInfo.pointerFlags = PEN_CONTACT;

  _injectPointer(device, info);
}

void test_CreateSynthPointer(void) {
  TEST_ASSERT_NOT_NULL(device);
}

void test_HoverExit(void) {
  HoverExit(device, info);
  TEST_ASSERT_EQUAL_INT(PEN_ENDHOVER, info->penInfo.pointerInfo.pointerFlags);
}

void test_DownMove(void) {
  Down(device, info);
  TEST_ASSERT_EQUAL_INT(PEN_DOWN, info->penInfo.pointerInfo.pointerFlags);
}

void test_UpMove(void) {
  Up(device, info);
  TEST_ASSERT_EQUAL_INT(PEN_UP, info->penInfo.pointerInfo.pointerFlags);
}

void test_ScreenToGlobal(void) {
    // This test is specific to  my screen setup
    POINT global = _ScreenToGlobal(0, 0, 1);
    TEST_ASSERT_EQUAL_INT(1920, global.x);
    TEST_ASSERT_EQUAL_INT(0, global.y);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_CreateSynthPointer);
  RUN_TEST(test_HoverExit);
  RUN_TEST(test_DownMove);
  RUN_TEST(test_UpMove);
  /* RUN_TEST(test_ScreenToGlobal); */
  /* RUN_TEST(test_DBG); */
  return UNITY_END();
}
