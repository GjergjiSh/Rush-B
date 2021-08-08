import cv2
import mediapipe as mp
import time


class HandDetector():
    def __init__(self, mode=False, max_hands=2, detection_confidence=0.5, track_confdence=0.5):
        self.mode = mode
        self.max_hands = max_hands
        self.detection_confidence = detection_confidence
        self.track_confdence = track_confdence

        self.mp_hands = mp.solutions.hands
        self.hands = self.mp_hands.Hands( self.mode, self.max_hands, self.detection_confidence, self.track_confdence)
        self.mp_draw = mp.solutions.drawing_utils


    def find_hands(self, img, draw=True ):
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(img_rgb)

        if self.results.multi_hand_landmarks:
            for hand_lms in self.results.multi_hand_landmarks:
                if draw:
                    self.mp_draw.draw_landmarks(img, hand_lms, self.mp_hands.HAND_CONNECTIONS)

        return img

    def find_hand_position(self, img, hand_nr=0, draw=True):
        landmark_list = []

        if self.results.multi_hand_landmarks:
            hand = self.results.multi_hand_landmarks[hand_nr]

            for id, lm in enumerate(hand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x*w), int(lm.y*h)
                landmark_list.append([id, cx, cy])

                if draw:
                    cv2.circle(img, (cx,cy), 8, (0,0,255), cv2.FILLED)
        return landmark_list

def main():
    cap = cv2.VideoCapture(0)
    pTime = 0
    cTime = 0

    detector = HandDetector()
    while True:
        success, img = cap.read()

        cTime = time.time()
        fps = 1/(cTime - pTime)
        pTime = cTime

        img = detector.find_hands(img)
        landmark_list = detector.find_hand_position(img)

        cv2.putText(img, str(int(fps)), (10, 70),
                    cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 2)
        cv2.imshow("Image", img)
        cv2.waitKey(1)


if __name__ == "__main__":
    main()
