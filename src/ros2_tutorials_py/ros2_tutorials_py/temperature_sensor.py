#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
import random
import serial
from serial.tools.list_ports import comports

import time


class TemperatureSensorNode(Node):
    def __init__(self):
        super().__init__("temperature_sensor")
        self.temperature_publisher_ = self.create_publisher(
            Int64, "temperature", 10)
        self.temperature_timer_ = self.create_timer(
            2.0, self.publish_temperature)
    def publish_temperature(self):

        print("step 1")
        ser.write('1\n20\n15000\n1\n20\n15000\n'.encode())
        print("step 2")
        time.sleep(4)
        temperature = random.randint(20, 30)
        msg = Int64()
        msg.data = temperature
        self.temperature_publisher_.publish(msg)
def main(args=None):
    print("step 1")
    global ser
    for port in list(comports()):
        port1 = port.device
    ser = serial.Serial(port1, 9600)
    rclpy.init(args=args)
    node = TemperatureSensorNode()
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()
