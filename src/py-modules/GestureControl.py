import VideoSubscriber as vs
import HandDetector as htm
import cv2

video_subscriber = vs.VideoSubscriber()
hand_detector = htm.HandDetector()

while True:
    if not video_subscriber.frame_available():
        continue

    frame = video_subscriber.frame()
    frame = hand_detector.find_hands(frame)

    cv2.imshow("Rush-B Video Feed", frame )
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
