/**Copyright <2019> <Achal Pragneshkumar Vyas>
 *Copyright <YEAR> <COPYRIGHT HOLDER>

*Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are *met:

*1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

*2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the *documentation and/or other materials provided with the distribution.

*3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this *software without specific prior written permission.

*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT *LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT *HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT *LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON *ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE *USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**


/**
* @file roomba_walker.cpp
* @brief walker class Implementation
* @details Implementation of walker class
* @author  Achal Vyas
*/

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "roomba_walker.hpp"

Walker::Walker() {
    velPub = n.advertise <geometry_msgs::Twist> ("/cmd_vel_mux/input/navi",
    1000);
    laserSub = n.subscribe <sensor_msgs::LaserScan> ("/scan", 500,
    &Walker::checkObstacle, this);

   
    collision_flag = false;
}

Walker::~Walker() {
    
    velocity.linear.x = 0;
    velocity.linear.z = 0;
    velPub.publish(velocity);
}

void Walker::checkObstacle(const sensor_msgs::LaserScan::ConstPtr& msg) {
    
    collision_flag = false;
    for (auto i : msg->ranges) {
     if ( i < 0.8 ) {
        collision_flag = true;
      }
    }
}

void  Walker::walk() {
    ros::Rate loop_rate(10);
    while (ros::ok()) {
       
        if (collision_flag) {
            ROS_INFO("object detected");
       
          velocity.linear.x = 0.0;
          velocity.angular.z = 0.4;
        } else {

            ROS_INFO("moving ahead");
            velocity.angular.z = 0.0;
            velocity.linear.x = 0.4;
        }
        velPub.publish(velocity);
        ros::spinOnce();
        loop_rate.sleep();
    }
}


