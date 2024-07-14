
[![Actions Status](https://github.com/TheLartians/ModernCppStarter/workflows/Windows/badge.svg)](https://github.com/mmartincevic/CppSDLBoilerplate)
[![Actions Status](https://github.com/TheLartians/ModernCppStarter/workflows/Ubuntu/badge.svg)](https://github.com/mmartincevic/CppSDLBoilerplate)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>

# C++ SDL starter project


### Build everything at once

You can build everything

```bash
cmake -S . -B build
cmake --build build
```

### Cleanup

You have two files inside bin/ directory. You can cleanup everything just by running simple command line:

```bash
./bin/cleanup.bat
```

### TODO

1. Add maybe separate project generations
2. Add proper testing (also with examples)
3. Add testing to cmake so we can run tests
4. Add clang formatting
5. Add documentation creation