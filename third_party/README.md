# MoHex 2.0

MoHex is a local benchmarking opponent for COMP34111 Hex. The submodule pins the
unmodified [Benzene source](https://github.com/hexanna1/benzene-vanilla-cmake/tree/c80d3d3be151fb70082c49b5f6ac58c36a809899)
at commit `c80d3d3be151fb70082c49b5f6ac58c36a809899`.

From the team repository root, with CMake, a C++ compiler, Boost and Berkeley DB
development packages installed:

```sh
git submodule update --init -- third_party/mohex
cmake -S third_party/mohex -B build/mohex -DCMAKE_BUILD_TYPE=Release
cmake --build build/mohex --target mohex --parallel
```

Run `build/mohex/src/mohex/mohex` as a separate executable. Keep the engine
outside the coursework submission archive.

## Licence and attribution

Benzene's upstream README identifies its licence as the GNU Lesser General
Public License, version 3. See the [upstream licence and copyright notices](mohex/COPYING.LESSER)
and the [GNU GPL v3 text](https://www.gnu.org/licenses/gpl-3.0.html) incorporated
by the LGPL. Preserve the upstream notices if redistributing the engine or its
source. This repository records a source reference. Any separate distribution
of a compiled MoHex binary needs its own corresponding-source and licence
review.
