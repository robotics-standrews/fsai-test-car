# import can
import gs_usb.gs_usb

devs=gs_usb.gs_usb.GsUsb.scan()
for i,d in enumerate(devs):
    print(i, d)



# bus = can.interface.Bus(channel='0', bustype='gs_usb', bitrate=500000)
# msg = can.Message(arbitration_id=0x123, data=[1, 2, 3, 4], is_extended_id=False)
# bus.send(msg)
# print("Sent!")