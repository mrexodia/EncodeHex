# EncodeHex

An x64dbg plugin that provides expression functions for encoding strings as hexadecimal bytes.

## Features

This plugin registers an `encode()` expression function that can be used anywhere x64dbg accepts expressions (commands, breakpoints, conditions, etc.).

### Usage

```
encode("string", "encoding")
```

**Parameters:**
- `string` - The input string to encode (UTF-8)
- `encoding` - The target encoding: `"utf-8"` / `"utf8"` or `"utf-16"` / `"utf16"`

**Returns:** A hexadecimal string representation of the input.

### Examples

Encode "Hello" as UTF-8 hex bytes:
```
encode("Hello", "utf-8")
```
Result: `48656C6C6F`

Encode "Hello" as UTF-16 hex bytes:
```
encode("Hello", "utf-16")
```
Result: `480065006C006C006F00`

### Use Cases

- Converting strings to hex for memory search patterns
- Building byte sequences for patching
- Debugging string encoding issues
- Creating signatures that include string data

## Building

### Prerequisites

- Visual Studio with C++ development tools
- CMake 3.15 or higher

### Build Commands

From a Visual Studio Developer Command Prompt:

**64-bit:**
```
cmake -B build64 -A x64
cmake --build build64 --config Release
```

**32-bit:**
```
cmake -B build32 -A Win32
cmake --build build32 --config Release
```

The compiled plugin (`.dp32` or `.dp64`) will be in the build directory.

## Installation

Copy the appropriate plugin file to your x64dbg plugins directory:
- `EncodeHex.dp32` → `x32/plugins/`
- `EncodeHex.dp64` → `x64/plugins/`

Restart x64dbg to load the plugin.

## Development

This project uses [cmkr](https://cmkr.build) for CMake generation. The project configuration is in `cmake.toml`.

### Project Structure

```
EncodeHex/
├── src/
│   ├── plugin.cpp      # Main plugin logic
│   ├── pluginmain.cpp  # Plugin boilerplate
│   └── pluginmain.h    # Plugin headers
├── cmake.toml          # cmkr configuration
├── CMakeLists.txt      # Generated CMake (do not edit)
└── cmake/              # CMake utilities
```

## License

MIT License - see [LICENSE](LICENSE) for details.

## References

- [x64dbg Plugin Documentation](https://help.x64dbg.com/en/latest/developers/plugins/index.html)
- [x64dbg Plugin SDK](https://x64dbg.com/blog/2016/07/30/x64dbg-plugin-sdk.html)
- [Plugin Template](https://github.com/x64dbg/PluginTemplate)
