import HandDetector as htm
import ZMQPipeline as zpipe
import cv2
import time
import math
import time


class GestureController():
    speed_trigger_distance: int
    steering_trigger_distance: int
    snap_tolerance: int
    speed_increment: int
    lh_landmarks: list
    rh_landmarks: list
    hand_detector: htm.HandDetector
    dw_publisher: zpipe.DWPublisher

    def __init__(self, speed_trigger_distance=150, steering_trigger_distance=115, snap_tolerance=80, speed_increment=10):
        self.speed_trigger_distance = speed_trigger_distance
        self.steering_trigger_distance = steering_trigger_distance
        self.snap_tolerance = snap_tolerance
        self.speed_increment = speed_increment

        self.left_shown = False
        self.right_shown = False
        self.left_palm = False
        self.right_palm = False
        self.left_trigger = False
        self.right_trigger = False

        self.hand_detector = htm.HandDetector(
            detection_confidence=0.8, track_confdence=0.7)
        self.dw_publisher = zpipe.DWPublisher()

        self.lh_landmarks = []
        self.rh_landmarks = []

    def gesture_controls(self, img, driver_wish, debug=False):
        self.hand_detector.get_results(img, draw=True)
        self.lh_landmarks = self.hand_detector.find_hand_position(img, 0)
        self.rh_landmarks = self.hand_detector.find_hand_position(img, 1)
        self.control_left_servo(driver_wish)
        self.control_right_servo(driver_wish)

        if ((self.right_palm) & self.right_palm):
            driver_wish.left_servo = 90
            driver_wish.right_servo = 90

        self.dw_publisher.publish(driver_wish)

        if debug:
            print('Left Servo {} Right Servo {} Top Servo {}'.format(
                driver_wish.left_servo, driver_wish.right_servo, 0))

    def control_left_servo(self, driver_wish):
        if (len(self.lh_landmarks) != 0):
            # wrist coordiantes
            l_x0, l_y0 = self.lh_landmarks[0][1], self.lh_landmarks[0][2]
            # thumb coordiantes
            l_x1, l_y1 = self.lh_landmarks[4][1], self.lh_landmarks[4][2]
            # middle finger coordinates
            l_x3, l_y3 = self.lh_landmarks[12][1], self.lh_landmarks[12][2]
            # pinky coordinates
            l_x5, l_y5 = self.lh_landmarks[20][1], self.lh_landmarks[20][2]
            self.left_palm = (l_x1 > l_x5)
            l_mw_distance = math.hypot(l_x0-l_x3, l_y0-l_y3)

            if (not self.left_palm):
                if ((l_mw_distance < self.speed_trigger_distance) & (driver_wish.left_servo < 180)):
                    driver_wish.left_servo += self.speed_increment
            elif (l_mw_distance < self.speed_trigger_distance) & (driver_wish.left_servo > 0):
                driver_wish.left_servo -= self.speed_increment

    def control_right_servo(self, driver_wish):
        if (len(self.rh_landmarks) != 0):
            # wrist coordiantes
            r_x0, r_y0 = self.rh_landmarks[0][1], self.rh_landmarks[0][2]
            # thumb coordiantes
            r_x1, r_y1 = self.rh_landmarks[4][1], self.rh_landmarks[4][2]
            # middle finger coordinates
            r_x3, r_y3 = self.rh_landmarks[12][1], self.rh_landmarks[12][2]
            # pinky coordinates
            r_x5, r_y5 = self.rh_landmarks[20][1], self.rh_landmarks[20][2]
            self.right_palm = (r_x1 < r_x5)
            r_mw_distance = math.hypot(r_x0-r_x3, r_y0-r_y3)

            if (not self.right_palm):
                if ((r_mw_distance < self.speed_trigger_distance) & (driver_wish.right_servo < 180)):
                    driver_wish.right_servo += self.speed_increment
            elif (r_mw_distance < self.speed_trigger_distance) & (driver_wish.right_servo > 0):
                driver_wish.right_servo -= self.speed_increment

    def control_top_servo(self):
        pass


if __name__ == '__main__':
    gesture_controller = GestureController()
    driver_wish = gesture_controller.dw_publisher.create_driver_wish(
        90, 90, 90)

    cap = cv2.VideoCapture(0)
    pTime = 0
    cTime = 0
    joint_list = [[8, 7, 6], [12, 11, 10], [16, 15, 14], [20, 19, 18]]

    while True:
        success, img = cap.read()
        cTime = time.time()
        fps = 1/(cTime - pTime)
        pTime = cTime

        gesture_controller.gesture_controls(img, driver_wish, debug=True)

        cv2.putText(img, str(int(fps)), (10, 70),
                    cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 2)
        cv2.imshow("Image", img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    gesture_controller.dw_publisher.kill()
