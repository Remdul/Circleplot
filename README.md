circleplot
==========

A repot for teaching and putting circles on a map
#Notes:
1. 2014-06-23 We want to group all of the related data together in a single object. For this we will use classes. Have a look at the regex demo for use of classes in c++. For those of you working in python, try to figure out how to use classes. I will be pushing a demo using classes shortly. 
 

#Intructions:
1. Clone the repo
  1. `git clone https://github.com/walterschell/circleplot`
2. Add your name or handle to the contributors.txt file. 
3. Commit your changes. 
  1. `git commit -am 'Adding my name'`
3. Push your changes back to the master branch on the origin (github)
  1. `git push origin`


#Tasks:
There is a set of sample data in this repository. This data consists of a point name, MGRS coordinates, a radius and a description of the point. Your task is to write a program to parse the file and then return the data back to you. Note that all of the radiuses should be expressed as meters when they are displayed  back, but the sample data contains mixed units. For this portion of the task, each student should create their own branch of this repo. Make sure to push your branch back into the origin.

1. Make a branch
  1. `git branch schell` Name your branch something descriptive that won't conflict with other people
2. Switch to your branch
  1. `git checkout schell`
3. Make some code!
4. Even if it doesn't work, check it in often so you can get help if you are stumpted
  1. If this is a new file to git `git add newfile.c`
  2. `git commit -am 'A commit message'`
  3. `git push origin schell` *REALLY IMPORTANT* if you don't do this your changes won't make it back up for everyone to see

#How to get things to compile:
1. Get a compiler if you are on a debian system, run
  1. `sudo apt-get install gcc`
2. Write some code. This repo has an example hello_world.cpp program
3. Compile your code. Note that if you forget to specify an output file, it will go to a.out
  1. `g++ -o hello hello_world.cpp`
4. Run your program
  1. `./hello`

#How to look at the c++ regex demo
1. Make sure your compiler supports C++0x11 (Most newer ones will)
2. Update your copy of the repo
   1. `git fetch origin`
3. Create a local branch that follows the regexdemo remote branch
   1. `git checkout --track origin/regexdemo`
4. Compile the example
   1. `g++ -o example example.cpp`
5. Run the example
   1. `./example people.txt`
6. Examine the code in whatever text editor you like
7. Remember to switch back to your branch when you are done looking around
   1. `git checkout schell`

