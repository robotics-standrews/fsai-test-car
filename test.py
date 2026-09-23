import can
import gs_usb.gs_usb
import time

# devs=gs_usb.gs_usb.GsUsb.scan()
# for i,d in enumerate(devs):
#     print(i, d)


print("Opening CAN device...")

bus = can.Bus(
    interface="gs_usb",
    channel=0,
    bitrate=500000
)

print("CAN device opened successfully")
print("Sending message...")

msg = can.Message(
    arbitration_id=0x123,
    data=[1, 2, 3, 4],
    is_extended_id=False
)

try:
    bus.send(msg, timeout=2)
    print("SUCCESS: message sent")
except Exception as e:
    print("SEND ERROR:", repr(e))
finally:
    try:
        bus.shutdown()
    except Exception:
        pass

print("Done")


# bus1 = can.interface.Bus('test', interface='virtual')
# bus2 = can.interface.Bus('test', interface='virtual')

# msg1 = can.Message(arbitration_id=0xabcde, data=[1,2,3])
# bus1.send(msg1)
# msg2 = bus2.recv()

# #assert msg1 == msg2
# assert msg1.arbitration_id == msg2.arbitration_id
# assert msg1.data == msg2.data
# assert msg1.timestamp != msg2.timestamp


# bus1.shutdown()
# bus2.shutdown()
