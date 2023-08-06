<a name="line-6"></a>
# Synthetic Pointer DLL

This is a DLL for simulating pen input using the Synthetic Pointer API in Windows.

<a name="line-16"></a>
## Public Functions

<a name="line-20"></a><a name="CreateSynthPointer"></a>
### 🔹 HSYNTHETICPOINTERDEVICE CreateSynthPointer()

```cpp
HSYNTHETICPOINTERDEVICE CreateSynthPointer()
```

Create a synthetic pointer device.

#### Return

Return a handle to the synthetic pointer device.

<a name="line-29"></a><a name="GetDefaultPointerTypeInfo"></a>
### 🔹 POINTER_TYPE_INFO *GetDefaultPointerTypeInfo()

```cpp
POINTER_TYPE_INFO *GetDefaultPointerTypeInfo()
```

Get an initial POINTER_TYPE_INFO with default values.

#### Return

Return a POINTER_TYPE_INFO structure with default values.

<a name="line-38"></a><a name="HoverMove"></a>
### 🔹 void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed)

```cpp
void HoverMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed)
```

Move the hover position of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.
- `x` - Normalized x-coordinate of the hover position.
- `y` - Normalized y-coordinate of the hover position.
- `screenId` - ID of the screen.
- `buttonPressed` - Boolean indicating if the button is pressed.

<a name="line-52"></a><a name="ContactMove"></a>
### 🔹 void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed, UINT32 pressure)

```cpp
void ContactMove(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info, float x, float y, int screenId, BOOL buttonPressed, UINT32 pressure)
```

Move the contact position of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.
- `x` - Normalized x-coordinate of the contact position.
- `y` - Normalized y-coordinate of the contact position.
- `screenId` - ID of the screen.
- `buttonPressed` - Boolean indicating if the button is pressed.
- `pressure` - The pressure of the pen contact.

<a name="line-67"></a><a name="HoverExit"></a>
### 🔹 void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)

```cpp
void HoverExit(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)
```

Exit the hover state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-77"></a><a name="Down"></a>
### 🔹 void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)

```cpp
void Down(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)
```

Enter the down state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-87"></a><a name="Up"></a>
### 🔹 void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)

```cpp
void Up(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)
```

Enter the up state of the pen.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-97"></a><a name="ScreenCount"></a>
### 🔹 void ScreenCount(int* count)

```cpp
void ScreenCount(int* count)
```

Get the number of screens.

#### Parameters

- `count` - Pointer to the number of screens.

<a name="line-106"></a>
## Internal Functions

The following functions are intended for internal use by the DLL and should not be used by applications.

<a name="line-112"></a><a name="_ScreenToGlobal"></a>
### 🔹 POINT _ScreenToGlobal(int screenX, int screenY, int screenId)

```cpp
POINT _ScreenToGlobal(int screenX, int screenY, int screenId)
```

Convert the screen coordinates to global coordinates.

#### Parameters

- `screenX` - The screen X coordinate.
- `screenY` - The screen Y coordinate.
- `screenId` - The screen ID.

#### Returns
The global coordinates.

<a name="line-126"></a><a name="injectPointer"></a>
### 🔹 void _injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)

```cpp
void _injectPointer(HSYNTHETICPOINTERDEVICE device, POINTER_TYPE_INFO *info)
```

Inject the pointer input.

#### Parameters

- `device` - Handle to the synthetic pointer device.
- `info` - Pointer to the POINTER_TYPE_INFO structure.

<a name="line-136"></a><a name="handleError"></a>
### 🔹 void _handleError()

```cpp
void _handleError()
```

Handle an error that occurred during the DLL's operation.
