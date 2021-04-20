# miniRT | 107/100
## Mini Ray Tracing with miniLibX

```
make
./miniRT [filename.rt]
```

### Map syntax {filename.rt}

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

![image: wolf](https://github.com/bbetsey/miniRT/blob/master/img/wolf.jpeg?raw=true)

![image: big](https://github.com/bbetsey/miniRT/blob/master/img/big_one.jpeg?raw=true)

![image: big](https://github.com/bbetsey/miniRT/blob/master/img/big_two.jpeg?raw=true)
