# libKitsumiAiSdk

![Github workfloat status](https://img.shields.io/github/workflow/status/kitsudaiki/libKitsumiAiSdk/build-and-test/develop?label=build%20and%20test&style=flat-square)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/kitsudaiki/libKitsumiAiSdk?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/kitsudaiki/libKitsumiAiSdk?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-17-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

SDK-library for Hanami-AI: https://github.com/kitsudaiki/Hanami-AI

## Build

#### Required build tools for C++-part

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | >= 8.0 | Compiler for the C++ code.
make | make | >= 4.0 | process the make-file, which is created by qmake to build the programm with g++
qmake | qt5-qmake | >= 5.0 | This package provides the tool qmake, which is similar to cmake and create the make-file for compilation.
FLEX | flex | >= 2.6 | Build the lexer-code for all used parser.
GNU Bison | bison | >= 3.0 | Build the parser-code together with the lexer-code.

#### Required generic libraries for C++-part

name | repository | version | task
--- | --- | --- | ---
ssl library | libssl-dev | 1.1.x | encryption for tls connections
crpyto++ | libcrypto++-dev | >= 5.6 | provides encryption-functions like AES
boost-library | libboost1.71-dev | >= 1.71 | provides boost beast library for HTTP and Websocket client

#### Required kitsunemimi libraries for C++-part

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsunemimiCommon | develop | https://github.com/kitsudaiki/libKitsunemimiCommon.git
libKitsunemimiJson | develop | https://github.com/kitsudaiki/libKitsunemimiJson.git
libKitsunemimiIni | develop | https://github.com/kitsudaiki/libKitsunemimiIni.git
ibKitsunemimiArgs | develop | https://github.com/kitsudaiki/ibKitsunemimiArgs.git
libKitsunemimiConfig | develop | https://github.com/kitsudaiki/libKitsunemimiConfig.git
libKitsunemimiCrypto | develop | https://github.com/kitsudaiki/libKitsunemimiCrypto.git
libKitsunemimiHanamiCommon | develop | https://github.com/kitsudaiki/libKitsunemimiHanamiCommon.git
libKitsunemimiHanamiMessages | develop | https://github.com/kitsudaiki/libKitsunemimiHanamiMessages.git

#### Required build tools for go-part

name | repository | version | task
--- | --- | --- | ---
go | golang | >= 1.13 | Compiler for the go code.

### build library (C++-part)

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/kitsudaiki/libKitsumiAiSdk.git
cd libKitsumiAiSdk/cpp
./build.sh
cd ../result
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Contributing

Please give me as many inputs as possible: Bugs, bad code style, bad documentation and so on.

## License

This project is licensed under the Apache License Version 2.0 - see the [LICENSE](LICENSE) file for details
