# humangl
School project: an introduction to rigging, animations and hierarchical modeling,<br>as well as keeping an application's animations in concert with real-time.

## Requirements
- macOS 10.14.6 or later, or Ubuntu 21.04 or later
- a system that can run OpenGL 4.1 or later
- git
- make
- cmake
- g++
- glfw (cmake might import this for you)

## Quick Start
### Compile and execute by running the following commands in your command shell:
>git clone git@github.com:kimdewinter/humangl.git<br/>
>cd humangl<br/>
>cmake -B build<br/>
>cmake --build build<br/>
>build/humangl<br/>

### Walking animation
- Compile and execute
- press return on keyboard ("enter")
- click on / alt-tab to your command shell
- type "skelly" and press return
- type "walk" and press return
- click on / alt-tab to your command shell
- yell "I'm walkin' here!" in your best New York accent

### Jumping animation
- Compile and execute
- press return on keyboard ("enter")
- click on / alt-tab to your command shell
- type "skelly" and press return
- type "jump" and press return
- click on / alt-tab to your command shell
- enjoy it jumping around like a frog, and yell "Here come dat boi!!!!!!"

### Selecting individual bodyparts
To select the torso and rotate:
- Compile and execute
- press spacebar on keyboard
- click on / alt-tab to your command shell
- type "skelly" and press return
- type "torso" and press return
- click on / alt-tab to your command shell
- press t/f/g/h/r/y to rotate the torso
- you can press c at any time to reset it

## Extended Explanation
This project had me creating an OpenGL C++ program from scratch. The only libraries I was allowed to use, are those necessary for window/context creation, OpenGL function bindings, and GLM for the creation of a quaternion-based rotation matrix. If future time permits, I'd like to manually implement quarternion rotation.

The requirements as per the subject.pdf are to make a humanoid model with separated upper and lower limbs, that can stay put, walk, and jump. It should also be possible to modify the scale of different body parts, after which related bodyparts should readjust.<br/>One criterion was somewhat limiting to creativity however:<br/>"Each body part will be drawn by one and only one function call. This function will draw a 1x1x1 geometric shape at the origin of the current matrix."<br/>This meant every body part is simply a cube, translated, rotated and scaled into position to look like a bodypart. If this constraint were absent I would've liked to make a system with proper vertex weight-based rigging of exterior skin.

>----- Controls -----<br/>
>Esc: close program<br/>
>C: re-set bodypart<br/>
>Return: select animation<br/>
>Spacebar: select bodypart<br/>
>WASDQE: translate bodypart (requires DESIGN_MODE to be set to 1 in main.h)<br/>
>TGFHRY: rotate bodypart<br/>
>IKJLUO: scale bodypart<br/>

And that's how we end up with this fabulous humanoid that walks around like they own the place!<br/>
![](https://i.imgur.com/fneQfSD.gif)

For more information you can read through the assignment PDF, included in the root of the repository.
