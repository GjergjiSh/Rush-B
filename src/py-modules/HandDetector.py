import cv2
import mediapipe as mp
import numpy as np
import time


class HandDetector():
    def __init__(self, mode=False, max_hands=2, detection_confidence=0.5, track_confdence=0.5):
        self.mode = mode
        self.max_hands = max_hands
        self.detection_confidence = detection_confidence
        self.track_confdence = track_confdence

        self.mp_hands = mp.solutions.hands
        self.hands = self.mp_hands.Hands(
            self.mode, self.max_hands, self.detection_confidence, self.track_confdence)
        self.mp_draw = mp.solutions.drawing_utils

    def get_results(self, img, draw=False):
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(img_rgb)

        if draw:
            if (self.results.multi_hand_landmarks):
                for hand_lms in self.results.multi_hand_landmarks:
                    self.mp_draw.draw_landmarks(
                        img, hand_lms, self.mp_hands.HAND_CONNECTIONS)

        return img

    def draw_finger_angles(self, image, joint_list):
        # Loop through hands
        if self.results.multi_hand_landmarks:
            for hand in self.results.multi_hand_landmarks:
                #Loop through joint sets
                for joint in joint_list:
                    # First coord
                    a = np.array([hand.landmark[joint[0]].x,
                                  hand.landmark[joint[0]].y])
                    # Second coord
                    b = np.array([hand.landmark[joint[1]].x,
                                  hand.landmark[joint[1]].y])
                    # Third coord
                    c = np.array([hand.landmark[joint[2]].x,
                                  hand.landmark[joint[2]].y])

                    radians = np.arctan2(
                        c[1] - b[1], c[0]-b[0]) - np.arctan2(a[1]-b[1], a[0]-b[0])
                    angle = np.abs(radians*180.0/np.pi)

                    if angle > 180.0:
                        angle = 360-angle

                    cv2.putText(image, str(round(angle, 2)), tuple(np.multiply(b, [640, 480]).astype(int)),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2, cv2.LINE_AA)

        return image

    def find_hand_position(self, img, handedness):
        landmark_list = []
        if self.results.multi_hand_landmarks:
            for num, hand in enumerate(self.results.multi_hand_landmarks):
                for idx, classification in enumerate(self.results.multi_handedness):
                    if (classification.classification[0].index == handedness) & (num == handedness):
                        for id, lm in enumerate(hand.landmark):
                            h, w, c = img.shape
                            cx, cy = int(lm.x*w), int(lm.y*h)
                            landmark_list.append([id, cx, cy])

        return landmark_list


def main():
    cap = cv2.VideoCapture(4)
    joint_list = [[8, 7, 6], [12, 11, 10], [16, 15, 14], [20, 19, 18]]
    pTime = 0
    cTime = 0

    detector = HandDetector()
    while True:
        success, img = cap.read()

        cTime = time.time()
        fps = 1/(cTime - pTime)
        pTime = cTime

        img = detector.get_results(img)
        img = detector.draw_finger_angles(img, joint_list)

        cv2.putText(img, str(int(fps)), (10, 70),
                    cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 2)
        cv2.imshow("Image", img)
        cv2.waitKey(1)


if __name__ == "__main__":
    main()
