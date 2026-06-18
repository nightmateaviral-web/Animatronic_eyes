from picamera2 import Picamera2
import cv2

picam2 = Picamera2()

picam2.configure(
    picam2.create_preview_configuration(
        main={"format": "XRGB8888", "size": (640, 480)}
    )
)

picam2.start()

face_cascade = cv2.CascadeClassifier(
    'haarcascade_frontalface_default.xml'
)

while True:

    frame = picam2.capture_array()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.1, 5)

    for (x, y, w, h) in faces:

        # Draw rectangle
        cv2.rectangle(
            frame,
            (x, y),
            (x+w, y+h),
            (0, 255, 0),
            2
        )

        print("Face detected at:", x, y)

    # Show camera window
    cv2.imshow("Face Tracking", frame)

    # ESC key exits
    if cv2.waitKey(1) == 27:
        break

cv2.destroyAllWindows()
