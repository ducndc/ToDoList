```sh
sudo apt install libgtkmm-3.0-dev


g++ todo.cc -o todo `pkg-config gtkmm-3.0 --cflags --libs`
```
