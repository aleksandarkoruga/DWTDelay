# DWTDelay

Author: Aleksandar Koruga

Discrete wavelet transform delay

If you're looking for a compiled external please check out https://github.com/aleksandarkoruga/public-extensions

### Usage

The ugen is made in such a way thet you need to give it an array as input, the first entry being the sinal you want to process and the subsequent entries the delay control pf each wavelet decomposition level. The number of decomposition levels is given by the number of entries in your array. DWTDelay.ar([signal,ctr1,ctr2,ctr3,...]) please note that all of the sognals must be audio rate.

### Requirements

- CMake >= 3.5
- SuperCollider source code

### Building

Clone the project:

    git clone https://github.com/aleksandarkoruga/dwtdelay
    cd dwtdelay
    mkdir build
    cd build

Then, use CMake to configure and build it:

    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cmake --build . --config Release --target install

You may want to manually specify the install location in the first step to point it at your
SuperCollider extensions directory: add the option `-DCMAKE_INSTALL_PREFIX=/path/to/extensions`.

It's expected that the SuperCollider repo is cloned at `../supercollider` relative to this repo. If
it's not: add the option `-DSC_PATH=/path/to/sc/source`.

### Issues

You may encounter linking issues for the WaveLib library, if you are on a dev system different than Windows please run a build of WaveLib and link it. Otherwise (you are on a Windows system) you might want to check your additional library directories paths and include directories.  

### Developing

Use the command in `regenerate` to update CMakeLists.txt when you add or remove files from the
project. You don't need to run it if you only change the contents of existing files. You may need to
edit the command if you add, remove, or rename plugins, to match the new plugin paths. Run the
script with `--help` to see all available options.
