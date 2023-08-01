#ifndef SYNTHPOINTER_H
#define SYNTHPOINTER_H

#include <windows.h>

/**
 * # Synthetic Pointer DLL
 *
 * This is a DLL for simulating pen input using the Synthetic Pointer API in Windows.
 */

/**
 * ## Types
 */

/** (PEN_STATES)
 * Enum for representing the different states of a pen.
 *
 * - `PEN_STATE_MASK` - Mask for pen states.
 * - `PEN_HOVER` - Pen is hovering over the screen.
 * - `PEN_DOWN` - Pen is in contact with the screen and is being pressed down.
 * - `PEN_CONTACT` - Pen is in contact with the screen.
 * - `PEN_UP` - Pen has been lifted off the screen.
 * - `PEN_ENDHOVER` - Pen has stopped hovering over the screen.
 */
typedef enum {
  PEN_STATE_MASK = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN | POINTER_FLAG_UP | POINTER_FLAG_UPDATE),
  PEN_HOVER = (POINTER_FLAG_INRANGE | POINTER_FLAG_UPDATE),
  PEN_DOWN = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_DOWN),
  PEN_CONTACT = (POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT | POINTER_FLAG_UPDATE),
  PEN_UP = (POINTER_FLAG_INRANGE | POINTER_FLAG_UP),
  PEN_ENDHOVER = (POINTER_FLAG_UPDATE),
} PEN_STATES;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ## Public Functions
 */

/** (CreateSynthPointer)
 * Create a synthetic pointer device.
 *
 * # Return
 *
 * Return a handle to the synthetic pointer device.
 */
HSYNTHETICPOINTERDEVICE CreateSynthPointer();

/** (GetDefaultPointerTypeInfo)
 * Get an initial POINTER_TYPE_INFO with default values.
 *
 * # Return
 *
 * Return a POINTER_TYPE_INFO structure with default values.
 */
POINTER_TYPE_INFO GetDefaultPointerTypeInfo();

/** (HoverMove)
 * Move the hover position of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 * - `x` - Normalized x-coordinate of the hover position.
 * - `y` - Normalized y-coordinate of the hover position.
 * - `screenId` - ID of the screen.
 * - `buttonPressed` - Boolean indicating if the button is pressed.
 */
void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId, BOOL buttonPressed);

/** (ContactMove)
 * Move the contact position of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 * - `x` - Normalized x-coordinate of the contact position.
 * - `y` - Normalized y-coordinate of the contact position.
 * - `screenId` - ID of the screen.
 * - `buttonPressed` - Boolean indicating if the button is pressed.
 * - `pressure` - The pressure of the pen contact.
 */
void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId, BOOL buttonPressed, UINT32 pressure);

/** (HoverExit)
 * Exit the hover state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info);

/** (Down)
 * Enter the down state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info);

/** (Up)
 * Enter the up state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info);

/** (GetScreenIds)
 * Get the IDs of the available screens.
 *
 * # Parameters
 *
 * - `count` - Pointer to an integer that will be filled with the number of screens.
 *
 * # Return
 *
 * Return an array of screen IDs.
 */
int* GetScreenIds(int* count);

/**
 * ## Internal Functions
 *
 * The following functions are intended for internal use by the DLL and should not be used by applications.
 */

/** (calculateScreenOffset)
 * Calculate the offset of a screen from (0,0).
 *
 * # Parameters
 *
 * - `screenId` - ID of the screen.
 *
 * # Return
 *
 * Return the offset of the screen as a POINT structure.
 */
POINT calculateScreenOffset(int screenId);

/** (injectPointer)
 * Inject the pointer input.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info);

/** (handleError)
 * Handle an error that occurred during the DLL's operation.
 */
void handleError();

#ifdef __cplusplus
}
#endif

#endif // SYNTHPOINTER_H
