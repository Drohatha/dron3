#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/PositionTarget.h>
#include <msgs_definitions/setpoint_msg_defines.h>
#include <tf/transform_datatypes.h>

constexpr float PI_HALF = 1.570796; 

ros::Publisher pub_setpoint;


mavros_msgs::AttitudeTarget setpoint;

uint16_t attitude_control = 



void joystickCallback(const geometry_msgs::Twist& input){

	tf::Quaternion q = tf::createQuaternionFromRPY(input.angular.x, input.angular.y, input.angular.z);
	q.normalize(); 


	setpoint.type_mask = velocity_control;
	setpoint.orientation.x = ?
	setpoint.orientation.y = ?
	setpoint.orientation.z = ?
	setpoint.orientation.w = ? 
	setpoint.type_mask = velocity_control;
	setpoint.header.frame_id = "fcu";

	pub_setpoint.publish(setpoint);
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "joystick_repeater"); 
	ros::NodeHandle n;

	ros::Subscriber sub_joystick = n.subscribe("spacenav/twist", 100, joystickCallback); 

	pub_setpoint = n.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 100);

	ros::spin();

	return 0;
}