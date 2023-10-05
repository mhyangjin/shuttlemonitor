#!/usr/bin/env python
import rospy
import sys
from std_msgs.msg import String
from shuttle_monitor.msg import Can
import random

def talker():
	print("talker")
	pub = rospy.Publisher('/can', Can, queue_size=100)
	rospy.init_node('car', anonymous=True)
	rate = rospy.Rate(1) # 10hz
	#rand_status =random.randrange(0,2)
	rand_status=1
	count=1

	while not rospy.is_shutdown():
		print("while")
		can_msg=Can()
		if count<10:
			can_msg.veh_ctrl_mode = 1
			can_msg.veh_driving_state=4
			can_msg.battery_soc=random.randrange(0,100)
			can_msg.veh_speed=random.randrange(0,120)
			can_msg.emergency_stop=0
			count +=1
		else:
			can_msg.veh_ctrl_mode = 0
			can_msg.veh_driving_state=0
			can_msg.battery_soc=random.randrange(0,100)
			can_msg.veh_speed=0
			can_msg.emergency_stop=0
			if ( count > 20):
				count=1
			else:
				count +=1

		pub.publish(can_msg)

		rate.sleep()

if __name__ == '__main__':
	print("Start")
	try:
		talker()
	except rospy.ROSInterruptException:
		print("Exception")
		pass
