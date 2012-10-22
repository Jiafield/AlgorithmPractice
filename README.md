3D Render by Ray Tracing
===========

Model
-----------
       /
      / light
     /

                  |	
        3D        |
        object    |      eye
                  |
                  |
                screen

Step 1
------

I will display a shadow of the 3D object on the screen using ray tracing.

Then generate a bitmap of the screen shadow. The size of the bitmap is
1024 * 768 bits.

Step 2
------

Introducing a surface light source in this model. Then objects would
reflect the ray from the eye. If the ray finally reaches the light
source, this point of the object will be bright, else the point will be
dark.
