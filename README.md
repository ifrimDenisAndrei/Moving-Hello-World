# Moving-Hello-World

## Description
  A simple window displaying a coloured hello world text sorrounded by a rectangle and a circle. The text is read from a text file and can be moved by pressing the arrow keys. 

## Usage 
  The code is already compiled and built , it can be ran by double clicking on the executable "MovingHelloWorld", or "hello_world" in the autotools version.
  Alternatively if you wish to rebuild it , use the following commands :

 Cmake: 
`cmake -B <folder_name> -S .` <br>
 
 Makefile : `make` ( to build it )
            `make execute` ( to run it)
            `make clean` (to delete the executable)
 Autotools ( must be in the autotools_hello_world folder) : `autoreconf --install` , `./configure`, `make`
