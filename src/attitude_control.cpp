#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <sensor_msgs/Joy.h>
#include <msgs_definitions/setpoint_msg_attitude_defines.h>
#include <tf/transform_datatypes.h>

constexpr float PI_HALF = 1.570796; 

ros::Publisher pub_setpoint;


mavros_msgs::AttitudeTarget setpoint;

uint16_t attitude_control = 0; 



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

void buttonCallback(const sensor_msgs::Joy& input){

	static int button_pushed = 0; 
	static int button_2_pushed = 0; 

	if(!button_pushed && input.buttons[0]){
		setpoint.thrust += 0.01; 
		button_pushed = 1; 
	}
	if(!button_2_pushed && input.buttons[1]){
		setpoint.thrust -= 0.01; 
		if(setpoint.thrust < 0.0){
			setpoint.thrust = 0.0; 
		}
		button_2_pushed = 1; 
	}


	button_pushed = input.buttons[0];
	button_2_pushed = input.buttons[1]; 
	pub_setpoint.publish(setpoint); 
}




int main(int argc, char **argv)
{
	ros::init(argc, argv, "attitude_control"); 
	ros::NodeHandle n;

	setpoint.thrust = 0.5; 

	ros::Subscriber sub_joystick = n.subscribe("spacenav/twist", 100, joystickCallback);
	ros::Subscriber sub_buttons = n.subscribe("spacenav/joy", 100, buttonCallback); 

	pub_setpoint = n.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/attitude", 100);



	ros::spin();

	return 0;
}