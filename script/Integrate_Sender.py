#!/usr/bin/env python
import rospy
import sys
from std_msgs.msg import String
from shuttle_monitor.msg import IntergrateRecognition, Ps_recog
import random

def talker():
	print("talker")
	pub = rospy.Publisher('/iIntegrateRecognition', IntergrateRecognition, queue_size=100)
	rospy.init_node('iIntegrateRecognition', anonymous=True)
	rate = rospy.Rate(1) # 10hz
	#rand_status =random.randrange(0,2)
	rand_status=1
	count=1

	ir_msg=IntergrateRecognition()
	ir_msg.ps_recog=[]
	male_adult1=Ps_recog()
	male_adult1.ps_id=11
	male_adult1.ps_status=1
	male_adult1.ps_gender="M"
	male_adult1.ps_age="A"

	female_adult1=Ps_recog()
	female_adult1.ps_id=12
	female_adult1.ps_status=1
	female_adult1.ps_gender="F"
	female_adult1.ps_age="A"

	male_child1=Ps_recog()
	male_child1.ps_id=13
	male_child1.ps_status=1
	male_child1.ps_gender="M"
	male_child1.ps_age="C"

	female_child1=Ps_recog()
	female_child1.ps_id=13
	female_child1.ps_status=1
	female_child1.ps_gender="F"
	female_child1.ps_age="C"

	while not rospy.is_shutdown():
		print("while")
		ir_msg=IntergrateRecognition()

		male_adult1.ps_status=rand_status =random.randrange(0,3)
		female_adult1.ps_status=rand_status =random.randrange(0,3)
		male_child1.ps_status=rand_status =random.randrange(0,3)
		female_child1.ps_status=rand_status =random.randrange(0,3)
		ir_msg.ps_recog.append(male_adult1)
		ir_msg.ps_recog.append(male_child1)
		ir_msg.ps_recog.append(female_adult1)
		ir_msg.ps_recog.append(female_child1)
		ir_msg.ps_numb=len(ir_msg.ps_recog)

		pub.publish(ir_msg)
		rate.sleep()

if __name__ == '__main__':
	print("Start")
	try:
		talker()
	except rospy.ROSInterruptException:
		print("Exception")
		pass
