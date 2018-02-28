#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <msgs_definitions/setpoint_msg_attitude_defines.h>
#include <tf/transform_datatypes.h>

constexpr float PI_HALF = 1.570796; 

ros::Publisher pub_setpoint;


mavros_msgs::AttitudeTarget setpoint;

uint16_t attitude_control = IGNORE_ATTITUDE | IGNORE_THRUST; 



void joystickCallback(const geometry_msgs::Twist& input){

	tf::Quaternion q = tf::createQuaternionFromRPY(input.angular.x, input.angular.y, input.angular.z);
	q.normalize(); 

	setpoint.orientation.x = q[0];
	setpoint.orientation.y = q[1]; 
	setpoint.orientation.z = q[2];
	setpoint.orientation.w = q[3];
	setpoint.type_mask = attitude_control;
	setpoint.header.frame_id = "fcu";

	pub_setpoint.publish(setpoint);
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "joystick_repeater"); 
	ros::NodeHandle n;

	ros::Subscriber sub_joystick = n.subscribe("spacenav/twist", 100, joystickCallback); 

	pub_setpoint = n.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/local", 100);

	ros::spin();

	return 0;
}