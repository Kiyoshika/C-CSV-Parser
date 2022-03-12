# C-CSV-Parser
Simple CSV parser written in C. Supports delimiters within quotes and casting data into int or float types.

See the examples/ folder for a few different examples on how to use the API.

# Installation
1. Git clone repo: `git clone https://github.com/Kiyoshika/C-CSV-Parser.git`
2. `cd C-CSV-Parser`
3. `mkdir build && cd build`
4. `cmake ..`
5. `(sudo) make install` - sudo may be required
6. `make` - if you do not want to use sudo; will have to manually add library and headers to your external projects

# Including Header and Linking
If you used `make install` you should be able to use it as follows
```c
#include <csvparser/csvparser.h>
```
and link the library as
```text
(command line)
gcc ... -lcsvparser ...

(CMake)
target_link_libraries(... csvparser)
```