### Bug description

Test initial result of `glfwGetFrameBufferSize` and `glfwGetWindowContentScale` is incorrect on MacOS, when I run on retina display but set `GLFW_COCOA_RETINA_FRAMEBUFFER` to `GLFW_FALSE`.

`glfwPollEvents()` will correct that result, but `framebufferSizeCallback` is never invoked.

https://github.com/glfw/glfw/issues/1968

### Platform

* GLFW version:  glfw-3.3.4.bin.MACOS
* Compiler: Apple clang version 12.0.0 (clang-1200.0.32.27)
* Target: x86_64-apple-darwin20.5.0
* MacOS version: 11.4

### The result

#### Test CASE 1

use retina display = false
poll events before loop = false

````shell
./main.bin
frame#-2, fbSize=1280x800, scale=2.00x2.00
frame#-1, fbSize=1280x800, scale=2.00x2.00

frame#0, fbSize=1280x800, scale=2.00x2.00
frame#1, fbSize=640x400, scale=1.00x1.00
frame#2, fbSize=640x400, scale=1.00x1.00
frame#3, fbSize=640x400, scale=1.00x1.00
frame#4, fbSize=640x400, scale=1.00x1.00
frame#5, fbSize=640x400, scale=1.00x1.00
frame#6, fbSize=640x400, scale=1.00x1.00
frame#7, fbSize=640x400, scale=1.00x1.00
frame#8, fbSize=640x400, scale=1.00x1.00
frame#9, fbSize=640x400, scale=1.00x1.00
````

#### Test CASE 2

use retina display = false
poll events before loop = true

````shell
./main.bin poll
frame#-2, fbSize=1280x800, scale=2.00x2.00
frame#-1, fbSize=640x400, scale=1.00x1.00

frame#0, fbSize=640x400, scale=1.00x1.00
frame#1, fbSize=640x400, scale=1.00x1.00
frame#2, fbSize=640x400, scale=1.00x1.00
frame#3, fbSize=640x400, scale=1.00x1.00
frame#4, fbSize=640x400, scale=1.00x1.00
frame#5, fbSize=640x400, scale=1.00x1.00
frame#6, fbSize=640x400, scale=1.00x1.00
frame#7, fbSize=640x400, scale=1.00x1.00
frame#8, fbSize=640x400, scale=1.00x1.00
frame#9, fbSize=640x400, scale=1.00x1.00
````

#### Test CASE 3

use retina display = true
poll events before loop = false


````shell
./main.bin retina
frame#-2, fbSize=1280x800, scale=2.00x2.00
frame#-1, fbSize=1280x800, scale=2.00x2.00

frame#0, fbSize=1280x800, scale=2.00x2.00
frame#1, fbSize=1280x800, scale=2.00x2.00
frame#2, fbSize=1280x800, scale=2.00x2.00
frame#3, fbSize=1280x800, scale=2.00x2.00
frame#4, fbSize=1280x800, scale=2.00x2.00
frame#5, fbSize=1280x800, scale=2.00x2.00
frame#6, fbSize=1280x800, scale=2.00x2.00
frame#7, fbSize=1280x800, scale=2.00x2.00
frame#8, fbSize=1280x800, scale=2.00x2.00
frame#9, fbSize=1280x800, scale=2.00x2.00
````

#### Test CASE 4

use retina display = true
poll events before loop = true

````shell
./main.bin retina poll
frame#-2, fbSize=1280x800, scale=2.00x2.00
frame#-1, fbSize=1280x800, scale=2.00x2.00

frame#0, fbSize=1280x800, scale=2.00x2.00
frame#1, fbSize=1280x800, scale=2.00x2.00
frame#2, fbSize=1280x800, scale=2.00x2.00
frame#3, fbSize=1280x800, scale=2.00x2.00
frame#4, fbSize=1280x800, scale=2.00x2.00
frame#5, fbSize=1280x800, scale=2.00x2.00
frame#6, fbSize=1280x800, scale=2.00x2.00
frame#7, fbSize=1280x800, scale=2.00x2.00
frame#8, fbSize=1280x800, scale=2.00x2.00
frame#9, fbSize=1280x800, scale=2.00x2.00
````