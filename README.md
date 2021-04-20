# miniRT | 107/100
## Mini Ray Tracing with miniLibX

![image: wolf](https://github.com/bbetsey/miniRT/blob/master/img/wolf.jpeg?raw=true)

```
make
./miniRT [filename.rt]
```

## Map syntax *filename.rt*

**Resolution:**
```
R 1920 1080
----------------
» identifier: R
» x render size
» y render size
```

**Ambient lightning:**
```
A 0.2 255,255,255
--------------------
» identifier: A
» ambient lighting ratio in range [0.0, 1.0]
» R,G,B colors in range [0 - 255]
```

**Camera:**
```
c -50.0,0,20  0,0,1  70
------------------------
» identifier: c
» x,y,z coordinates of the view point
» 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
» FOV : Horizontal field of view in degrees in range [0,180]
```

**Light:**
```
l -40.0,50.0,0  0.6  10,255,255
--------------------------------
» identifier: l
» x,y,z coordinates of the light point
» the light brightness ratio in range [0.0, 1.0]
» R,G,B colors in range [0 - 255]
```

**Sphere:**
```
sp 0.0,0.0,20.6  12.6  10,0,255   300   0
--------------------------------
» identifier: sp
» x,y,z coordinates of the sphere center
» the sphere diameter
» R,G,B colors in range [0 - 255]
» specular (optional, default: 300)
» reflective (optional, default: 0) in range [0.0, 1.0]
```

**Plane:**
```
pl 0.0,0.0,20.6  0,1.0,0  10,0,255   300   0.2
---------------------------------------------
» identifier: pl
» x,y,z coordinates
» 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
» R,G,B colors in range [0 - 255]
» specular (optional, default: 300)
» reflective (optional, default: 0) in range [0.0, 1.0]
```

**Square:**
```
sq 0.0,0.0,20.6   1.0,0.0,0.0   12.6   255,0,255   300   0.6
-------------------------------------------------------------
» identifier: sq
» x,y,z coordinates of the square center
» 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
» side size
» R,G,B colors in range [0 - 255]
» specular (optional, default: 300)
» reflective (optional, default: 0) in range [0.0, 1.0]
```

![image: big](https://github.com/bbetsey/miniRT/blob/master/img/big_one.jpeg?raw=true)

![image: big](https://github.com/bbetsey/miniRT/blob/master/img/big_two.jpeg?raw=true)
