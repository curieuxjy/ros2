# ros2
ros2 humble study

## Installation

1. Ubuntu Update & Locale Setting
   ```commandline
   sudo apt update && sudo apt install locales
   ```
   ```commandline
   sudo locale-gen en_US en_US.UTF-8
   sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
   export LANG=en_US.UTF-8
   ```
   Check: `locale`

2. Ubuntu Universe repository
   ```commandline
   sudo apt install software-properties-common
   sudo add-apt-repository universe
   ```
   
3. Add ROS2 GPG key 
   ```commandline
   sudo apt update && sudo apt install curl -y
   sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
   ```
   
4. Add repository to source list
   ```commandline
   echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
   ```
   
5. Install ROS2
   ```commandline
   sudo apt update
   sudo apt upgrade
   ```
   ```commandline
   sudo apt install ros-humble-desktop
   ```
   ```commandline
   sudo apt install ros-dev-tools
   ```
   
6. Edit `~/.bashrc`
   ```commandline
   source /opt/ros/humble/setup.bash
   source ~/.bashrc
   ```
   
7. Check Installation
   ```commandline
   ros2 run demo_nodes_cpp talker
   
   ros2 run demo_nodes_py listener
   ```