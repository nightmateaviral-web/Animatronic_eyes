from picamera2 import Picamera2
import cv2

# Start Pi camera
picam2 = Picamera2()

picam2.configure(
    picam2.create_preview_configuration(
        main={"format": "XRGB8888", "size": (640, 480)}
    )
)

picam2.start()

# Load face detector XML file
face_cascade = cv2.CascadeClassifier(
    'haarcascade_frontalface_default.xml'
)

print("Face detection started!")

while True:

    # Capture frame
    frame = picam2.capture_array()

    # Convert to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5
    )

    # Print coordinates
    for (x, y, w, h) in faces:
        print("Face detected at:", x, y)
