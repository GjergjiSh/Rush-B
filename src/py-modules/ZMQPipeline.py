import zmq
from zmq.sugar.constants import LINGER
import PBDriverWish_pb2 as dw


class DWPublisher():
    def __init__(self, interface_transport = 'interfacetransport'):
        self.interface_transport = interface_transport
        self.zmq_context = zmq.Context()
        self.dw_pub_socket = self.zmq_context.socket(zmq.PUB)
        self.dw_pub_socket.setsockopt(zmq.LINGER, 0)
        self.dw_pub_socket.bind("ipc://{}".format(interface_transport))

    def DriverWish(self, top_servo=0, left_servo=90, right_servo=90):
        driver_wish = dw.PBDriverWish()
        driver_wish.top_servo = top_servo
        driver_wish.left_servo = left_servo
        driver_wish.right_servo = right_servo

        return driver_wish

    def publish(self, driver_wish):
        message = driver_wish.SerializeToString()
        self.dw_pub_socket.send(message)


if __name__ == '__main__':

    publisher = DWPublisher()
    driver_wish = publisher.DriverWish(0,90,90)
    publisher.publish(driver_wish)




