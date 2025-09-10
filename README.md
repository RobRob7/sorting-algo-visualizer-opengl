# OpenGL Sorting Algorithm Visualizer
Tool that provides a visualization of sorting algorithms using OpenGL 3.3 Core, C++17. For use with Windows only.

<h2>
<img src="https://previews.123rf.com/images/asmati/asmati1602/asmati160202823/52174375-exclamation-mark-sign-flat-style-icon-on-transparent-background.jpg" height="30" align="center">
Requirements
</h2>

> - [Download](https://visualstudio.microsoft.com/vs/community/) Visual Studio 2022 Community Edition.
> -- Install workloads: *Desktop development with C++*.
> - Download and install [CMake](https://cmake.org/download/)(at least v3.20).

<h2>
<img src="https://cdn-icons-png.freepik.com/512/8964/8964273.png" height="30",align = "center">
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
<img src="https://em-content.zobj.net/source/microsoft-teams/337/hammer-and-wrench_1f6e0-fe0f.png" height="30",align = "center">
Run
</h2>

```
Release/algorithm-visualizer.exe
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
<img src="https://img.favpng.com/19/7/16/vector-graphics-computer-icons-document-illustration-computer-file-png-favpng-xJ7warkhEDQsS0DxyYzeddGNq.jpg" height="30",align = "center">
Project Structure
</h2>

- This project follows the MVC design pattern. Project layout:
> src
|-> model/
|-> view/
|-> controller/
|-> main.cpp
res
|-> font/
|-> shader/

