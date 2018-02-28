# dron3
Dron3

How to compile and change the code:

1. Download the git repository into the catkin_ws/src folder, using git, then you should have a folder called dron3. 
2. The source files is found in catkin_ws/src/dron3/src 
3. Do the nescessary changes to these files. 
4. Go to the catkin_ws folder in terminal and type catkin_make (this will build the code)
5. If catkin_make worked without errors, type source devel/setup.sh in the same folder (catkin_ws) (Now ros can find the node)

Setting up the simulator: 

1. Open a LOT of terminals! 
2. In one terminal, Go to the folder src/PX4_2018) and type make posix_sitl_default gazebo (Starting up the simulator)
3. In another terminal type: roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14557" 
(Setting up communication between mavros and simulator)

4  In another terminal type: roslaunch spacenav_node classic.launch 
(starting the 3D mouse) use: rostopic list and rostopic echo "the topic" to check if you get data

5. To run the code we have made, use (in another terminal): rosrun joystick_repeater joystick_repeater 
(runs velocity control with 3D mouse), or rosrun joystick_repeater attitude_repeater (attitude control with 3D mouse)

Now that all you code is running you have to give some commands to change the states to armed and offboard! 

This is done in the terminal you used in point 2. Write "commander arm" to arm the quadcopter (the rotors should now start in the simulator)
Then you should write commander mode offboard (Set the quadcopter to offboard mode)

To check if you have done this correct; In another terminal you could type: rostopic echo /mavros/state
(It will publish some data about the states, and you will see the changes here)

Typical deathpits: The quad might disarm, use the topic above to check this!


If in any case you feel lost and all alone, Chris should be reachable unless he has died! 
