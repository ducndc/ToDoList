## Install lib gtk 
```sh
sudo apt install libgtkmm-3.0-dev
use a library like OpenSSL

g++ main.cc todo_app.cc -o todo $(pkg-config gtkmm-3.0 --cflags --libs)

```
## Build with CMake

```sh
mkdir build
cd build
cmake ..
make
```
