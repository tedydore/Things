#include "ros/ros.h"
#include "carla_msgs/CarlaEgoVehicleControl.h"
#include "carla_msgs/CarlaEgoVehicleInfoWheel.h"
#include "geometry_msgs/Twist.h"
#include <algorithm>

bool reverse = false;
float throttle = 0, steer = 0;
float x = 0, z = 0;
float max_steer_angle = 1.221730351448059;
float MAX_LON_ACCELERATION = 10;
ros::Publisher pubControl;


void setThrottle() {
	if (x = 0) {
		throttle = 0;
		return;
	}
	if (x > 0) {
		reverse = false;
		throttle = 1;
	} else {
		reverse = true;
		throttle = 1;
	}
}

void setSteer() {
	if (z = 0) {
		steer = 0;
		return;
	}
	if (z > 0) {
		steer = -std::min(max_steer_angle, z)/max_steer_angle;
	} else {
		steer = -std::max(-max_steer_angle, z)/max_steer_angle;
	}
}

void getTwistParams(const geometry_msgs::Twist twistmsg) {
	x = twistmsg.linear.x;
	z = twistmsg.angular.z;
	carla_msgs::CarlaEgoVehicleControl controlmsg;
		setThrottle();
		setSteer();
		controlmsg.throttle = throttle;
		controlmsg.steer = steer;
		controlmsg.reverse = reverse;
		pubControl.publish(controlmsg);
}

//void getVehicleInfo(const carla_msgs::CarlaEgoVehicleInfoWheel infomsg){
//	max_steer_angle = infomsg.max_steer_angle;
//}

int main(int argc, char **argv) {
	ros::init(argc, argv, "twistToControl") ;
	ros::NodeHandle n;
	pubControl = n.advertise<carla_msgs::CarlaEgoVehicleControl>("/carla/ego_vehicle/vehicle_control_cmd", 1000);
	//ros::Subscriber subInfo = n.subscribe<carla_msgs::CarlaEgoVehicleInfoWheel>("/carla/ego_vehicle/vehicle_info", 1000, getVehicleInfo);
	ros::Subscriber subTwist = n.subscribe<geometry_msgs::Twist>("/cmd_vel", 1000, getTwistParams);
	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
