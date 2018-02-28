#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/PositionTarget.h>
#include <msgs_definitions/setpoint_msg_defines.h>


constexpr float PI_HALF = 1.570796; 

ros::Publisher pub_setpoint;

mavros_msgs::PositionTarget setpoint;

uint16_t velocity_control = IGNORE_PX | IGNORE_PY | IGNORE_PZ |
	                    IGNORE_AFX | IGNORE_AFY | IGNORE_AFZ  |
	                    IGNORE_YAW;// | 
	                    //IGNORE_YAW_RATE;



void joystickCallback(const geometry_msgs::Twist& input){

	setpoint.header.stamp = ros::Time::now(); 
	setpoint.coordinate_frame = mavros_msgs::PositionTarget::FRAME_BODY_NED;
	setpoint.type_mask = velocity_control;
	setpoint.velocity.x = 3.0*input.linear.x;
	setpoint.velocity.y = 3.0*input.linear.y;
	setpoint.velocity.z = input.linear.z;				
	setpoint.header.frame_id = "fcu";
	setpoint.yaw = -PI_HALF;
	setpoint.yaw_rate = input.angular.z; 
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