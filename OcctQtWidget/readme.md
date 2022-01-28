This example is a  `QWidget library` implemenation of opencascade.
-----------------------

Test gui to run the qt widget library:

    ~/OcctQtApp/

The testgui can pass the qt pallete to the widget. 

In this way the background color of the opencascade widget is more or less the same as your gui color.

The widget source:

    ~/OcctQtLib/

The library is containing 3 cpp classed to achieve our goals.
The difficulty is keeping the qt and opencascade opengl includes separated. 

Signal and slots are used.


![gui_preview](https://user-images.githubusercontent.com/44880102/151471698-0d010bd5-c03e-41b2-b735-5368c0205b6c.jpg)
