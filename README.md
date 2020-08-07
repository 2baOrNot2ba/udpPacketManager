udpPacketManager
================

udpPacketManager is a C library developed to handle reading and processing packet streams from interational LOFAR stations. It is used at the Irish LOFAR station (I-LOFAR) in conjunction with Olaf Wucknitz's (MPIfRA) VLBI recording software, but in principle can be used with any packet capture that keep the last 16 bytes of the UDP header attached to CEP packets.

This library allows for the entire or partial extraction and processing of LOFAR CEP packet streams, re-aligning data to account for packet loss or misalignment on the first packet, to produce one of several data products, ranging from raw votlages (reordered or not) to stokes vector outputs.

A guide on how to integrate the software in your project is provided in the [**README_INTEGRATION.md**](README_INTEGRATION.md) file, and example implementations can be found in the provided [**lofar_cli_extractor.c**](lofar_cli_extractor.c) program and my fork of Cees Bassa's GPU coherent dedispersion software [CDMT](https://github.com/David-McKenna/cdmt) for use with raw data captures.

Caveats & TODOs
-------

While using the library, do be aware
- CEP packets that are recorded out of order may cause issues, the best way to handle them as not been determined so they are currently skipped
- The provided python dummy data script tends to generate errors in the output after around 5,000 packets are generated
- 4-bit data is not yet supported

Future work should not break the exiting load/process iteration loop, and may consist of
- Re-learning the intended way of installing C libraries (headers are copied to /usr/local/include, but the compiled objects need to be sorted)
- Implementing 4-bit
- Creating a wrapper python library to allow for easer interfacing within python scripts rather than requiring a C program (CFFI if I can strip out ifdefs?)
- Add some 'defaults' into the mockHeader input, such as a "-mode5" string converted to implement the default sampling time and frequencies used
- Investigating [blosc](https://github.com/Blosc/) [(examples link)](https://github.com/Blosc/c-blosc2/tree/master/examples) as an option to speed up some processing modes

Requirements
------------

### Building / Using the Library
- Modern C and C++ compilers with OpenMP and C++17 support (gcc/g++-9 used for development, icc/icpc-2021.01 also tested and optimal)
- Zstandard libary/development headers (ver > 1.3, libzstd-dev on Ubuntu 18.04+, libzstd1-dev on Ubuntu 16.04, may require the restricted toolchain PPA)

While we support both gcc and icc, they have different execution paths. Due to differences in the OpenMP libraries between GOMP and Intel's OpenMP, the icc code path is up to a factor of 2.5 faster in non-stokes processing methods and advised as the compiler as a result.

### Building / Using the Example CLI
As well as the requirements for building the library, the CLI (optionally) depends on
- An install of [mockHeader](https://github.com/David-McKenna/mockHeader) to attach sigproc headers to output files
-- This can be downloaded and compiled automatically with the `make mockHeader` target, install targets will attempt to copy it as well


Installing
----------
Once the pre-requists are met, a simple `make all` should suffice to build the library, while `make install` and `make install-local` will copy the CLI and headers to the /usr/local or \~/.local/ folders. 


Usage
-----
Please see the [*README_INTEGRATION.md*](README_INTEGRATION.md) file for a guide to implementing the library in your software, and the [*README_CLI.md*](README_CLI.md) file for the usage guide for the provided CLI.