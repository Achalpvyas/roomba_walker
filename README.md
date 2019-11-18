# Gazebo tutorial
[![License: BSD](https://opensource.org/licenses/BSD-3-Clause)]

# Overview
Project about Gazebo.

## Dependencies			
 Ubuntu 16.04 Xenial 
 ROS kinetic 
 Catkin   
 Gazebo 

## install turtle_bot

```
$sudo apt-get install ros-kinetic-turtlebot-gazebo 
```

## Setting up workspace and packages

```
$ mkdir -p ~/<Workspace>
$ cd <Workspace>
$ mkdir src
$ catkin_make
$ cd src
$ git clone https://github.com/Achalpvyas/roomba_walker.git
$ cd ..
$ catkin_make
```

## Run

### Using roslaunch


```
$ roslaunch roomba_walker roomba_walker.launch
```
 terminate using ctrl+c


### Generating

```
$ roslaunch roomba_walker roomba_walker.launch enableRosBag:=true
```
#### Playing 

```
$ roscore
```
Open another terminal
```
$ cd <Workspace>
$ source devel/setup.bash
$ cd src/roomba_walker/results
$ rosbag play recording.bag
```
To terminate ctrl+c





