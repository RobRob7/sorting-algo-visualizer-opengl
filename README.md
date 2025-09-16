# OpenGL Sorting Algorithm Visualizer
- Tool that provides a visualization of sorting algorithms using OpenGL 3.3 Core, C++17. For use with Windows based machines.
- Sorting Algorithms:
  - Bubble Sort
  - Insertion Sort
  - Selection Sort
  - Quick Sort
- Maximize program window for optimal viewing.

<h2>
<img src="https://em-content.zobj.net/source/microsoft-teams/400/bar-chart_1f4ca.png" height="25" align="center">
Preview
</h2>
<div style="display: flex; gap: 20px;">
    <img src="./gif/bubble_sort.gif" height="240"/>
    <img src="./gif/insertion_sort.gif" height="240"/>
    <img src="./gif/selection_sort.gif" height="240"/>
    <img src="./gif/quick_sort.gif" height="240"/>
</div>

<h2>
<img src="https://lh4.googleusercontent.com/proxy/4_Zan5D7FOYcviw14ecpCpx8Tvq-ii1DoLIe15O2eDy9INbz2mhP-27Z3HCWby3EaQned-UF-1n4zFzbkSEFt9p7sOQUnsX-q_GyjI4C1-bSIVXTG0z0dugD" height="30" align="center">
Requirements
</h2>

> - [Download](https://visualstudio.microsoft.com/vs/community/) Visual Studio 2022 Community Edition.
> -- Install workloads: *Desktop development with C++*.
> - [Download](https://cmake.org/download/) and install CMake (>= v3.20).

<h2>
<img src="https://em-content.zobj.net/source/microsoft-teams/337/hammer-and-wrench_1f6e0-fe0f.png" height="30",align = "center">
Build
</h2>

- Clone repo:
```
git clone https://github.com/RobRob7/sorting-algo-visualizer-opengl.git
```
- Then run commands:
```
cd sorting-algo-visualizer-opengl
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
<h2>
<img src="https://cdn-icons-png.freepik.com/512/8964/8964273.png" height="30",align = "center">
Run
</h2>

```
cd Release
/algorithm-visualizer.exe
```


<h2>
<img src="https://em-content.zobj.net/source/microsoft-3D-fluent/406/package_1f4e6.png" height="30",align = "center">
Dependencies
</h2>

Libraries already provided, the following are used:
|Library|Usage|Version|
|-------|-------|-----|
|[FreeType](https://freetype.org/download.html)|Font rendering|v2.10.0|
|[Glad](https://glad.dav1d.de/)|OpenGL loader generator|N/A|
|[GLFW](https://www.glfw.org/download.html)|API for creating windows, contexts and surfaces, receiving input and events|v3.4|
|[GLM](https://github.com/g-truc/glm/releases/tag/1.0.1)|Header only C++ mathematics library|v1.01|


<h2>
<img src="https://www.traptct.com/wp-content/uploads/2020/04/file-folder-png-1.png" height="30",align = "center">
Project Structure
</h2>

This project follows the MVC design pattern. The model portion pertains to CPU side data like the sorting algorithm line positioning, and the custom font loader using FreeType. The view portion is strictly utilizing OpenGL to create and utilize shader programs, and setup VAO's and VBO's for rendering the lines and text on screen. The controller portion makes calls to model and view objects while also handling user inputs and window management. Project layout:
- **src/**
  - **model/**
    - **fontmodel/** → Font rendering data
        - `fontmodel.h`
        - `fontmodel.cpp`
    - **sortermodel/** → Sorting algorithm rendering data
        - **isortermodel/** → Pure abstract interface for sorter model
          - `isortermodel.h`
        - **sortingalgo/** → Sorting algorithms
          - `bubblesort.h`
          - `bubblesort.cpp`
          - `insertionsort.h`
          - `insertionsort.cpp`
          - `selectionsort.h`
          - `selectionsort.cpp`
          - `quicksort.h`
          - `quicksort.cpp`
        - `sortermodel.h`
        - `sortermodel.cpp`
  - **view/**
    - **fontview/** → Font rendering OpenGL
        - `fontview.h`
        - `fontview.cpp`
    - **sorterview/** → Sorting algorithm rendering OpenGL
        - `sorterview.h`
        - `sorterview.cpp`
    - **shader/** → Shader program creation
        - `shader.h`
        - `shader.cpp`
- **controller/**
    - **appcontroller/** → Window control
      - `appcontroller.h`
      - `appcontroller.cpp`
- **res/**
  - **font/** → Font for text rendering
  - **shader/** → Shaders
- **deps/** → Dependency files

