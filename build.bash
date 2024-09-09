
#!/bin/bash

# create dir
mkdir -p build

# compile to build/
gcc src/*.c src/*.h -Wall -o build/dansketal