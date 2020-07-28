# utf8proc

Originally forked from [JuliaStrings/utf8proc](https://github.com/JuliaStrings/utf8proc)

Aims:
* Integrate [libsodium](https://github.com/jedisct1/libsodium) [secure memory](https://doc.libsodium.org/memory_management)
* Add webassembly (wasm32) target

# How to build

## Environment for compiling

- cmake 3.16
- standard for the C++ - 20
- gcc-10, g++-10

On GNU/Linux Ubuntu 20.04
```sh
sudo add-apt-repository ppa:ubuntu-toolchain-r/test #for gcc-10 g++-10
sudo apt install cmake gcc-10 g++-10 build-essential libtool libboost-dev
```

## Dependences
[GpCore2](https://github.com/ITBear/GpCore2.git)
 
## Linux x86_64

- create folders **_uno-labs/src_**
- go into **_src_** and clone this repo
- go to the repo folder and run
```sh
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_SYSTEM_PROCESSOR=x86_64 -DBOOST_INCLUDE=/usr/include/boost/ -DBUILD_SHARED_LIBS=ON
```
- then make and install it
```sh
make & make install
```

In the folder **uno-labs** be created folders:
```
├── bin
├── doc
├── inc - for headers
├── lib - for *.so files
├── src - for sources
└── tmp
```

