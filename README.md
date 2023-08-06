# SynthPointer.dll

SynthPointer.dll is a dynamic link library (DLL) for simulating pen input using the Synthetic Pointer API in Windows. It provides a set of functions that allow you to create a synthetic pointer device, manipulate its state, and inject pointer input.

## Documentation

For detailed documentation of the functions and their usage, please refer to the [docs](./docs.md) file.

## Building

To build the project, follow these steps:

1. Ensure you have the required dependencies:
    
    - CMake (minimum version 3.10)
    - Clang compiler
    - Make

2. Clone the repository:
    
    ```bash
    git clone https://github.com/Sett17/SynthPointer.dll.git
    ```
    
3. Navigate to the project directory and create a build directory:
    
    ```bash
    cd SynthPointer.dll
    mkdir build
    ```
    
4. Configure the project using CMake:
    
    ```bash
    cd build
    cmake -G "Unix Makefiles" ..
    ```
    
5. Build the project:
    
    ```bash
    make
    ```

## Testing

After building, you can run the tests using:

```bash
./tests.exe
```

## Releases

The DLL is automatically built with GitHub Actions for each tag. You can download the latest version from the [releases](https://github.com/Sett17/SynthPointer.dll/releases) page on GitHub.

## License

The project is licensed under the [Unlicense](LICENSE).

## Contributing

Contributions are welcome. Please open an issue or submit a pull request on GitHub. We are particularly interested in contributions that would extend the functionality of the library to include touch input.
