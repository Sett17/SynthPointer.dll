<a name="line-6"></a>
# Synthetic Pointer DLL

This is a DLL for simulating pen input using the Synthetic Pointer API in Windows.

<a name="line-12"></a>
## Types

<a name="line-16"></a><a name="PEN_STATES"></a>
### 🔧 typedef enum {

```cpp
typedef enum {
```

Enum for representing the different states of a pen.

- `PEN_STATE_MASK` - Mask for pen states.
- `PEN_HOVER` - Pen is hovering over the screen.
- `PEN_DOWN` - Pen is in contact with the screen and is being pressed down.
- `PEN_CONTACT` - Pen is in contact with the screen.
- `PEN_UP` - Pen has been lifted off the screen.
- `PEN_ENDHOVER` - Pen has stopped hovering over the screen.

<a name="line-39"></a>
## Public Functions

<a name="line-43"></a><a name="CreateSynthPointer"></a>
### 🔹 HSYNTHETICPOINTERDEVICE CreateSynthPointer()

```cpp
HSYNTHETICPOINTERDEVICE CreateSynthPointer()
```

Create a synthetic pointer device.

#### Return

Return a handle to the synthetic pointer device.

<a name="line-52"></a><a name="GetDefaultPointerTypeInfo"></a>
### 🔹 POINTER_TYPE_INFO GetDefaultPointerTypeInfo()

```cpp
POINTER_TYPE_INFO GetDefaultPointerTypeInfo()
```

Get an initial POINTER_TYPE_INFO with default values.

#### Return

Return a POINTER_TYPE_INFO structure with default values.

<a name="line-61"></a><a name="HoverMove"></a>
### 🔹 void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId)

```cpp
void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId)
```

Move the hover position of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.
- `x` - Normalized x-coordinate of the hover position.
- `y` - Normalized y-coordinate of the hover position.
- `screenId` - ID of the screen.

<a name="line-74"></a><a name="ContactMove"></a>
### 🔹 void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId)

```cpp
void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info, float x, float y, int screenId)
```

Move the contact position of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.
- `x` - Normalized x-coordinate of the contact position.
- `y` - Normalized y-coordinate of the contact position.
- `screenId` - ID of the screen.

<a name="line-87"></a><a name="HoverExit"></a>
### 🔹 void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)

```cpp
void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)
```

Exit the hover state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-97"></a><a name="Down"></a>
### 🔹 void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)

```cpp
void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)
```

Enter the down state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-107"></a><a name="Up"></a>
### 🔹 void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)

```cpp
void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)
```

Enter the up state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-117"></a><a name="GetScreenIds"></a>
### 🔹 int* GetScreenIds(int* count)

```cpp
int* GetScreenIds(int* count)
```

Get the IDs of the available screens.

#### Parameters

- `count` - Pointer to an integer that will be filled with the number of screens.

#### Return

Return an array of screen IDs.

<a name="line-130"></a>
## Internal Functions

The following functions are intended for internal use by the DLL and should not be used by applications.

<a name="line-136"></a><a name="calculateScreenOffset"></a>
### 🔹 POINT calculateScreenOffset(int screenId)

```cpp
POINT calculateScreenOffset(int screenId)
```

Calculate the offset of a screen from (0,0).

#### Parameters

- `screenId` - ID of the screen.

#### Return

Return the offset of the screen as a POINT structure.

<a name="line-149"></a><a name="injectPointer"></a>
### 🔹 void injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)

```cpp
void injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO* info)
```

Inject the pointer input.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-159"></a><a name="handleError"></a>
### 🔹 void handleError()

```cpp
void handleError()
```

Handle an error that occurred during the DLL's operation.
