#ifndef SYNTHPOINTER_H
#define SYNTHPOINTER_H

#include <windows.h>

/**
 * # Synthetic Pointer DLL
 *
 * This is a DLL for simulating pen input using the Synthetic Pointer API in Windows.
 */

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
POINTER_TYPE_INFO *GetDefaultPointerTypeInfo();

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
void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed);

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
void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed, UINT32 pressure);

/** (HoverExit)
 * Exit the hover state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info);

/** (Down)
 * Enter the down state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info);

/** (Up)
 * Enter the up state of the pen.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info);

/** (ScreenCount)
 * Get the number of screens.
 *
 * # Parameters
 *
 * - `count` - Will be set to the number of screens.
 */
void ScreenCount(int *count);

/**
 * ## Internal Functions
 *
 * The following functions are intended for internal use by the DLL and should not be used by applications.
 */

/** (_ScreenToGlobal)
 * Convert the screen coordinates to global coordinates.
 *
 * # Parameters
 *
 * - `screenX` - The screen X coordinate.
 * - `screenY` - The screen Y coordinate.
 * - `screenId` - The screen ID.
 *
 * # Returns
 * The global coordinates.
 */
POINT _ScreenToGlobal(int screenX, int screenY, int screenId);

/** (injectPointer)
 * Inject the pointer input.
 *
 * # Parameters
 *
 * - `device` - Handle to the synthetic pointer device.
 * - `info` - Pointer to the POINTER_TYPE_INFO structure.
 */
void _injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info);

/** (handleError)
 * Handle an error that occurred during the DLL's operation.
 */
void _handleError();

#ifdef __cplusplus
}
#endif

#endif // SYNTHPOINTER_H
