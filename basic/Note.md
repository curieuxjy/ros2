# Tutorials
> [Check environment variables](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html#check-environment-variables)
    
```commandline
printenv | grep -i ROS
```

## [Using turtlesim, ros2, and rqt](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim.html#using-turtlesim-ros2-and-rqt)
    
- turtlesim 패키지 확인: `ros2 pkg executables turtlesim`
- turtlesim 실행창: `ros2 run turtlesim turtlesim_node`
- turtlesim 명령창: `ros2 run turtlesim turtle_teleop_key`

- topic 확인: `ros2 topic list`
    ```
    avery@avery:~$ ros2 topic list
    /parameter_events
    /rosout
    /turtle1/cmd_vel
    /turtle1/color_sensor
    /turtle1/pose
    ```
  
- node 확인: `ros2 node list`
    ```commandline
    avery@avery:~$ ros2 node list
    /teleop_turtle
    /turtlesim
    ```
  
- service 확인: `ros2 service list`
    ```commandline
    avery@avery:~$ ros2 service list
    /clear
    /kill
    /reset
    /spawn
    /teleop_turtle/describe_parameters
    /teleop_turtle/get_parameter_types
    /teleop_turtle/get_parameters
    /teleop_turtle/list_parameters
    /teleop_turtle/set_parameters
    /teleop_turtle/set_parameters_atomically
    /turtle1/set_pen
    /turtle1/teleport_absolute
    /turtle1/teleport_relative
    /turtlesim/describe_parameters
    /turtlesim/get_parameter_types
    /turtlesim/get_parameters
    /turtlesim/list_parameters
    /turtlesim/set_parameters
    /turtlesim/set_parameters_atomically
    ```
  
- action 확인: `ros2 action list`
    ```commandline
    avery@avery:~$ ros2 action list
    /turtle1/rotate_absolute
    ```

## rqt 사용

