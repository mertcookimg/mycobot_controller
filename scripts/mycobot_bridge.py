#!/usr/bin/env python2
import subprocess
import rospy
import rosparam

from std_msgs.msg import Float32MultiArray
from pymycobot.mycobot import MyCobot
from pymycobot.genre import Angle

class MycobotBridge:
    def __init__(self):
        port_str = rospy.get_param("/hardware_interface/mycobot_port", "default")
        if port_str == "default":
            port = subprocess.check_output(['echo -n /dev/ttyUSB*'], shell=True).decode()
        else:
            port = subprocess.check_output(['echo -n ' + port_str], shell=True).decode()

        self.mycobot_ = MyCobot(port)
        self.mycobot_.power_on()

        rospy.init_node('mycobot_bridge', anonymous=True)
        self.joint_res_pub_ = rospy.Publisher('/joint_res_', Float32MultiArray, queue_size=10)
        self.joint_cmd_sub = rospy.Subscriber("/joint_cmd_", Float32MultiArray, self._jointCommandCallback)

        self.rate_ = rospy.Rate(10)
        self.joint_state_array_ = []
        self.pre_data_list = []
        self.flag_first = True

        NUM_JOINT = 6
        for tmp_zero in range(NUM_JOINT):  
            tmp_zero = 0.0
            self.joint_state_array_.append(tmp_zero)

    def _joint_state_msg_sender(self):
        angles = self.mycobot_.get_radians()
        for index, value in enumerate(angles):
            if index != 2:
                value *= -1
            self.joint_state_array_[index] = value
        joint_state_msg = Float32MultiArray(data=self.joint_state_array_)
        self.joint_res_pub_.publish(joint_state_msg)

    def _jointCommandCallback(self, msg):
        data_list = []
        for index, value in enumerate(msg.data):
            if index != 2:
                value *= -1
            data_list.append(value)

        if self.flag_first:
            for value in data_list:
                self.pre_data_list.append(value)
            self.flag_first = False

        if self.pre_data_list != data_list:
            rospy.loginfo(rospy.get_caller_id() + "%s", msg.data)
            self.mycobot_.send_radians(data_list, 90)
            self.pre_data_list = []
            for value in data_list:
                self.pre_data_list.append(value)

    def run(self):
        while not rospy.is_shutdown():
            self._joint_state_msg_sender()
            self.rate_.sleep()

if __name__ == '__main__':
    try:
        mycobot_bridge = MycobotBridge()
        mycobot_bridge.run()
    except rospy.ROSInterruptException:
        pass

