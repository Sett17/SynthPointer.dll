# SynthPointer.dll

SynthPointer.dll is a dynamic link library (DLL) for simulating pen input using the Synthetic Pointer API in Windows. It provides a set of functions that allow you to create a synthetic pointer device, manipulate its state, and inject pointer input.

For detailed documentation of the functions and their usage, please refer to the [docs](docs.md) file.

## Building

The project uses CMake for building and Clang as the compiler. The minimum required version of CMake is 3.10. The project is set up to export all symbols on Windows and to use the C99 standard.

## Download

The DLL is built with the GitHub Windows runner for each tag. You can download the latest version from the [releases](https://github.com/Sett17/SynthPointer.dll/releases) page on GitHub.

## License

The project is licensed under the [Unlicense](LICENSE).

## Contributing

Contributions are welcome. Please open an issue or submit a pull request on GitHub. I am particularly interested in contributions that would extend the functionality of the library to include touch input.
