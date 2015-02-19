node-boyd
=========

Building
========

## Windows

### Prerequisite
* OpenCV 3.0
  node-boyd assumes that `%OPENCV_DIR%` (e.g. `C:\OpenCV\x86\vc12`) is defined and `%OPENCV_DIR%\bin` was added to your system path
* Node.js 0.10
  The current version of node-boyd cannot be build with Node.js 0.12 as the C API [changed](http://strongloop.com/strongblog/node-js-v0-12-c-apis-breaking/)
