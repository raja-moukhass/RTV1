
[![Build Status](https://travis-ci.org/anfederico/Clairvoyant.svg?branch=master)](https://travis-ci.org/anfederico/Clairvoyant)
![Dependencies](https://img.shields.io/badge/dependencies-up%20to%20date-brightgreen.svg)
![Dependencies](https://img.shields.io/badge/dependencies-up%20to%20date-brightgreen.svg)
[![GitHub Issues](https://img.shields.io/github/issues/anfederico/Clairvoyant.svg)](https://github.com/anfederico/Clairvoyant/issues)
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-orange.svg)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

<p align="center"><img width=60% src="https://github.com/raja-moukhass/RTV1/blob/main/images/ray_tracing.png"></p>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

# RTV1
- This mini-project is the first step to create a Raytracing program, for you to
finally be able to render computer-generated images.
# Functionalities:
- The program traces rays from one camera to n objects, the objects have shading and cast shadows on each other based the position of a single source of light.
- RTv1 takes as input a custom file format based on comma separated values (examples found in the scenes folder), from the file it can get these informations:
	- camera (location and direction);
	- light (location);
	- objects:
		- sphere (color, location and radius);
		- cylinder (color, location, axis and radius);
		- cone (color, location, axis and angle);
		- plane (color, normal and distance from 0,0,0);

# Installation
To generate an executable for this project run make in the root of the project directory after you've downloaded or cloned it.

This project will only work on MacOS El Capitan/Sierra/HighSierra and even then, no promises!

### how to run the project 
Run the following commands:

* To compile
	- `make`
* To remove objects:
	- `make clean`
* To remove objects and binary file (program):
	- `make fclean`
* To re-compile:
	- `make re`


# Challenges
this program was created without much help from standard libraries, these are all the standard function used:

- open
- read
- write
- malloc
- free
- math:
	- sin()
	- cos()
	- pow()
- mlx graphic library:
	- to create a window
	- use keyboard input
- ![lines of code](imgs/lines.png)

## Parsing file format

```sh

Under the construction

```


**Camere**

```sh
camera <look from> <look at>  
```

**light**

```sh
light <position> <color> 
```
**Sphere**

```sh
sphere <position> <translation> <rotation> <color> <raduis>
```

**Plane**

```sh 
plane <position> <translation> <rotation> <color> <norme>
```
**Cylindre**

```sh
cylindre <position>  <translation> <rotation> <color> <raduis> <axis>
```

**Cone**

```sh
cone <position>  <translation> <rotation> <color> <raduis> <axis>
```

- screen1
<img src="https://github.com/raja-moukhass/RTV1/blob/main/images/back_bone.png" width="1000" />

<img src="https://github.com/raja-moukhass/RTV1/blob/main/images/sphere.png" width="1000" />

<img src="https://github.com/raja-moukhass/RTV1/blob/main/images/shadow.png" width="1000" />

<img src="https://github.com/raja-moukhass/RTV1/blob/main/images/scene_.png" width="1000" />



- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing
- https://www.purplealienplanet.com/node/20
- https://www.scratchapixel.com/index.php?redirect
- https://www.gabrielgambetta.com/computer-graphics-from-scratch/basic-ray-tracing.html
- http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
- http://www.hugi.scene.org/online/coding/hugi%2023%20-%20d9ray.htm (intersection)


- https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces (vectors)
- https://github.com/raja-moukhass/RTV1.git
- https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf (ray tracing one week)
- https://www.youtube.com/watch?v=Ahp6LDQnK4Y&feature=youtu.be&ab_channel=UCDavisAcademics (all about it)
- http://viclw17.github.io/archives/ (raytracing c++)
- http://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/basic_algo.pdf (pdf)
-https://medium.com/swlh/ray-tracing-from-scratch-in-python-41670e6a96f9 (very goooooood)
- http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm (hugi)
- https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/#:~:text=We%20define%20a%20ray%20with,O%20%E2%86%92%20%2B%20t%20D%20%E2%86%92%20.
(cone intersection)
- https://github.com/raja-moukhass/RTV1.git (good resources)
- https://github.com/VBrazhnik/FdF/wiki/How-to-rotate-figure-in-3D%3F (rotation)
- - https://www.youtube.com/watch?v=yF8cKSIw6l4&t=127s (rotation video)
