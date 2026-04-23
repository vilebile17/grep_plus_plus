# Grep++

A small little cli tool that does a bit of what normal `grep` does.
So it's probably not very useful...

## 🛠 Installation

Clone the repo and run CMake:

```sh
git clone https://github.com/vilebile17/grep_plus_plus
cd grep_plus_plus
cmake -B build
cmake --build build
```

And after that, your executable file will be ready at **/build/grep++**.
You can move to the root directory and run it with:

```sh
mv ./build/grep++ .
./grep++ --version
```

## 🚩 List of flags

|flag|function|
|-|-|
|-h|displays the help message|
|-v|displays the program version|
|-i|case insensitive|
|-c|displays the number of times that it found the substring after printing the other results|
|-C|displays **only** the number of times that it found the substring|
|-n|displays line numbers next to the lines themselves|
|-N `<num>` |**only** finds _num_ instances of the substring|

## Why does this exist?

¯\_(ツ)_/¯
