### **Update: [Check out preview of all new GeoGen Studio!](NewStudioPreview.md)** ###

GeoGen is an open-source procedural height map generator using the Squirrel scripting language. GGen grants the scripts ability to generate the most various terrain shapes while keeping them simple and easy to read.

## Downloads ##
GeoGen alpha 8 ([r915](https://code.google.com/p/geogen/source/detail?r=915)) for win32 (includes only the executables, script examples, overlay examples and documentation):

<a href='http://geogen.googlecode.com/files/GeoGen_a8_Setup.zip'>Windows Installer (2.8 MB)</a><br />
<a href='http://geogen.googlecode.com/files/GeoGen_a8.zip'>Windows Archive (2.4 MB)</a>

GeoGen Studio requires <a href='http://www.microsoft.com/download/en/details.aspx?id=17851'>.NET Framework 4.0</a> and <a href='http://www.microsoft.com/download/en/details.aspx?id=5555'>Visual C++ Runtime Libraries 2010 (x86)</a>. The installer will check and install these dependencies automatically. Console interface works on any Windows 2000 or newer.

Source can be downloaded in the "Source" section.

## Version history ##
**1.0 alpha 8 (10.10.2011)**
  * New natural simulation functions Erosion, ThermalWeathering and FlowMap
  * Compatibility improvements (UAC support, fixed crashes because of missing libraries)
  * Numerous bugfixes and stability improvements
**1.0 alpha 7 (6.1.2011)**
  * Numerous new scripting functions added: Distort, NormalMap, NormalDifferenceMap, ConvexityMap, StrokePath, Shrink, Outline and more
  * New and better random noise generator
  * Fixed many crashes and bugs in Studio (expecially regarding texture and height map)
**1.0 alpha 6 (9.6.2010)**
  * New (and better) text editor
  * Numerous critical bugs fixed (all major memory leaks are now fixed)
**1.0 alpha 5**
  * First version featuring GeoGen Studio

## Features ##

**Warning**: GeoGen is still in development. Certain features may be unfinished. Please feel free to contact me about any issues with the application at **matej AT ihvar DOT cz** .

**Core**
  * Uses powerful C-like <a href='http://squirrel-lang.org/'>Squirrel</a> scripting language
  * Fast script execution
  * Rich scripting API with more than 100 different functions
  * Supports C++ and .NET binding via extremely simple external API
  * Visual Studio 2008 and newer and GCC 4.0 and newer supported

**Studio**
  * Advanced text editor with syntax highlighting, code suggestions and more
  * Real-time syntax checking
  * 2D and 3D heightmap visualisation
  * Script benchmarking

<table border='0'><tr><td><a href='http://matejz.wz.cz/studio1.png'><img src='http://matejz.wz.cz/studio1sm.png' width='300' /></a></td>
<td><a href='http://matejz.wz.cz/studio2.png'><img src='http://matejz.wz.cz/studio2sm.png' width='300' /></a></td></tr></table>

## What do the scripts look like? ##
Body of a simple script generating a hilly map with roughly radial lake in the middle:
```
// load map parameters
local width = GGen_GetArgValue("width");
local height = GGen_GetArgValue("height");

// create a radial gradient with height 1 in the center and height 1200 on the outer rim
local base = GGen_Data_2D(width, height, 0);
base.RadialGradient(width / 2, height / 2, width > height ? height / 2 : width / 2, 1, 1200, true);

// create a separate noise map using default noise settings
local noise = GGen_Data_2D(width, height);
noise.Noise(2, width > height ? height / 8 : width / 8, GGEN_STD_NOISE);

// adjust the range of the noise
noise.ScaleValuesTo(-500, 500);

// combine the maps
base.AddMap(noise);

// raise the water level so 9% of the map is under level 0
base.Flood(0.91);

return base;
```
Sample output of this script:

![http://matejz.wz.cz/lake.jpg](http://matejz.wz.cz/lake.jpg)

## How does it work? ##
> Slightly simplified scheme of how a complex heightmap can be composed from several simple parts using the GeoGen API:

![http://matejz.wz.cz/scheme.jpg](http://matejz.wz.cz/scheme.jpg)