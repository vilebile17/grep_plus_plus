![grep++](./pics/grep++.png)

A little _cli-tool,_ built in `c++`, that does a lot of the functions of
normal [`grep`](https://www.geeksforgeeks.org/linux-unix/grep-command-in-unixlinux/).

## 🛠️ Installation

Clone the repo and run [**CMake**](https://cmake.org/):

```sh
git clone https://github.com/vilebile17/grep_plus_plus
cd grep_plus_plus
cmake -B build
cmake --build build
```

And after that, your executable file will be ready at **./build/grep++**.
You can move to the _root directory_ and run it with:

```sh
mv ./build/grep++
./grep++ -v
./grep++ -h
```

---

## 🚩 List of Flags

|Flag|Function|
|-|-|
|-h|displays the help message|
|-v|displays the program version|
|-i|case insensitive|
|-c|displays the number of times that it found the substring after printing the other results|
|-C|displays **only** the number of times that it found the substring|
|-n|displays line numbers next to the lines themselves|
|-N|**only** finds _num_ instances of the substring (USAGE: `-N <num>`) |

---

## ❓ Why does this exist?

```
¯\_(ツ)_/¯
```

It is pretty cool though 🗿
