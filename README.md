# C boilerplate for raylib projects

## Dependencies

- [inotify-tools](https://github.com/inotify-tools/inotify-tools)
- [Make](https://www.gnu.org/software/make/)
- [gcc](https://gcc.gnu.org/)

## Platforms supported

- Linux
- Mac: **TODO**
- Windows: **TODO**

## Modes supported

- Debug
- Release: **TODO**
- Test: **TODO**

## Build for Development

### Start the watcher

Using ` inotify-wait` the watcher start listening changes in the game library source code directory and recompile
the game library. Open a terminal on the root of the project and execute:

```BASH
make watch
```

## Start the project

Open a terminal on the root of the project and execute:

```BASH
# build the project for debug
make
# execute the project
make run
```

## Key Concepts

1. **Dynamic Libraries**:

   - Shared libraries (`.so` files on Linux, `.dll` files on Windows) contain compiled code that can be loaded into a program at runtime. This allows the application to execute functions from an external library without including them at compile time.

2. **Dynamic Loading and Unloading**:

   - Functions like `dlopen`, `dlsym`, and `dlclose` (on Unix-like systems) or `LoadLibrary` and `GetProcAddress` (on Windows) allow a program to load and unload shared libraries while the program is running.

3. **Function Pointers**:
   - When a shared library is loaded, the program retrieves function addresses using `dlsym` (or `GetProcAddress` on Windows). These addresses are assigned to function pointers, which the program uses to call the functions in the library.

## Basic Workflow

### Step-by-Step Process

1. **Initial Load**:

   - The program loads the shared library dynamically using `dlopen` or `LoadLibrary`.
   - It retrieves function pointers using `dlsym` or `GetProcAddress`.

2. **Execute Functions**:

   - The program uses these function pointers to call functions from the shared library as needed.

3. **Monitor for Changes**:

   - A file-watching mechanism (e.g., `inotify` on Linux, `FindFirstChangeNotification` on Windows) detects when the shared library file has been modified.

4. **Reload the Library**:
   - The program unloads the existing library using `dlclose` (or `FreeLibrary` on Windows).
   - It reloads the updated library using `dlopen` or `LoadLibrary`.
   - Function pointers are updated to reference the new function addresses.

## Considerations

- State Preservation: When reloading a library, any state or static variables within the library are reset. Strategies must be developed to handle persistent state across reloads.

- Compatibility: Function signatures and data structures must remain consistent between reloads to avoid issues like crashes or undefined behavior.

- File Watching: Implementing a robust file-watching mechanism is crucial for automating the hot-reload process. Libraries like inotify (Linux) or ReadDirectoryChangesW (Windows) can help with this.

## Benefits

- Faster Iteration: Hot-reloading enables rapid testing and development without restarting the entire application.
- Seamless Updates: It provides a way to update specific components of an application at runtime, which can be useful for modular applications or plugins.
