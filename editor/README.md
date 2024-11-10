VPinball Editor
===============

A hopefully portable re-write of VPinball original editor.


Building
--------

External dependencies for VPinball standalone should have been built before
trying to compile the editor (ie: `external.sh` script must have ben run).

Editor can then be built as a classic CMake project:

```shell-session
$ cmake -B build-editor editor/
$ cmake --build build-editor -j $(nproc)
```
