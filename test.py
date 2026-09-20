import can
import gs_usb.gs_usb
import time

# devs=gs_usb.gs_usb.GsUsb.scan()
# for i,d in enumerate(devs):
#     print(i, d)


# bus = can.interface.Bus(channel='0', bustype='gs_usb', bitrate=500000)
# msg = can.Message(arbitration_id=0x123, data=[1, 2, 3, 4], is_extended_id=False)
# bus.send(msg)
# print("Sent!")


bus1 = can.interface.Bus('test', interface='virtual')
bus2 = can.interface.Bus('test', interface='virtual')

msg1 = can.Message(arbitration_id=0xabcde, data=[1,2,3])
bus1.send(msg1)
msg2 = bus2.recv()

#assert msg1 == msg2
assert msg1.arbitration_id == msg2.arbitration_id
assert msg1.data == msg2.data
assert msg1.timestamp != msg2.timestamp


bus1.shutdown()
bus2.shutdown()
