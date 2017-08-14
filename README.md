# mongoose-restapi-wrapper
REST API wrapper over Cesanta Mongoose

Simple Express like interface to easily implement a basic REST HTTP server with C++.
Note that, as it is right now, the implementation is neither robust nor secure.

Check main.demo.cpp to see an usage example.

Currently, CMakeLists.txt builds the project as a static library. 
To integrate with some other project, add this repository as a git submodule under the source directory.
Check https://github.com/adrian-mb/taller-ii-appserver to see how it can be done.
