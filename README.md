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
```
#### Generating CMake Framework Build
Change to the build sub-directory of the project.
```bash
$ cd build
```
Purge the current build framework.
```bash
$ rm -rf *
```
Generate the build framework using the CMakeList.txt directives.
```bash
$ cmake ..
```
#### Building the Project
Make sure you are in the build sub-directory of the project (where you generated the build framework).

Call the build system to actually compile/link the project.
```bash
$ cmake --build .
```
The final executables shall reside in the project bin sub-directory.
#### Testing the Project
CMake includes a test infrastructure using CTest.