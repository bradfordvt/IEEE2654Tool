# IEEE2654Tool
This project is an example of creating an EDA tool based on the IEEE Std 2654 System Test and Access Management (STAM) standard.

## High Level Design
### UML Diagrams
![uncached image](http://www.plantuml.com/plantuml/proxy?fmt=svg&cache=no&src=https://raw.githubusercontent.com/bradfordvt/IEEE2654Tool/main/docs/hld/IEEE2654ConceptualModel.puml)
---
*Figure HLD. 1.1 - docs/hld/IEEE2654ConceptualModel.puml*

![uncached image](http://www.plantuml.com/plantuml/proxy?fmt=svg&cache=no&src=https://raw.githubusercontent.com/bradfordvt/IEEE2654Tool/main/docs/hld/message_layer.puml)
---
*Figure HLD. 1.2 - docs/hld/message_layer.puml*

![uncached image](http://www.plantuml.com/plantuml/proxy?fmt=svg&cache=no&src=https://raw.githubusercontent.com/bradfordvt/IEEE2654Tool/main/docs/hld/context_layer.puml)
---
*Figure HLD. 1.3 - docs/hld/context_layer.puml*

## Building the Project
### Ubuntu Jammy Jellyfish (22.04) Build
#### Required Packages
```bash
$ sudo apt update
$ sudo apt intall build-essential libtool autoconf unzip wget 
$ sudo apt-get install libcppunit-dev
$ sudo apt purge --auto-remove cmake
$  wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
$  sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ jammy main'
$ sudo apt update
$ sudo apt install cmake
$ sudo apt install protobuf-compiler
$ sudo apt install libpython3.10-dev
$ sudo apt-get install swig
```
#### Generating CMake Framework Build
Change to the build sub-directory of the project.
```bash
$ cd build/debug
$ cmake -DCMAKE_BUILD_TYPE=Debug ../..
$ cmake --build .
$ cd ../release
$ cmake -DCMAKE_BUILD_TYPE=Release ../..
$ cmake --build .
```
Purge the current build framework.
```bash
$ cd build/debug
$ rm -rf *
$ cd ../release
$ rm -rf *
```
Generate the build framework using the CMakeList.txt directives.
```bash
$ cd build/debug
$ cmake -DCMAKE_BUILD_TYPE=Debug ../..
$ cd ../release
$ cmake -DCMAKE_BUILD_TYPE=Release ../..
```
#### Building the Project
Make sure you are in the build/debug
and build/release sub-directories of the project (where you generated the build framework).

Call the build system to actually compile/link the project.
```bash
$ cd build/debug
$ cmake -DCMAKE_BUILD_TYPE=Debug ../..
$ cmake --build . --config debug
$ cd ../release
$ cmake -DCMAKE_BUILD_TYPE=Release ../..
$ cmake --build .
```
The final executables shall reside in the project bin sub-directory.
#### Setting up the environment for testing and running
##### Environment variables
```bash
$ export IEEE2654MODULES=~/VisualStudioCode/IEEE2654Tool/examples/model/tree
$ export IEEE2654PLUGINS=~/VisualStudioCode/IEEE2654Tool/bin/plugins
$ export IEEE2654PYTHON=~/VisualStudioCode/IEEE2654Tool/python
```	
#### Testing the Project
CMake includes a test infrastructure using CTest.
#### Running Calculator Example
To run the example with the debugable code:
```bash
$ cd ~/VisualStudioCode/IEEE2654Tool/bin
$ ./IEEE2654Toold -m TestTop_d -t test1_calculator.py
```
The link back to the C++ code from the Python interpreter is found in calculator.py.  This file contains the code to create the Command messages and handles the response.  The Command messages for the calculator entities (e.g., BUTTON, DISPLAY) are encapsulated in Python functions called from test1_calculator.py.