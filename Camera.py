import cv2
import time
import datetime

cap = cv2.VideoCapture(0)
# capture the video / 0 indicates the number-1 camera in the system / setting up the camera

# calling classifier to detect body and face
face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
body_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + "haarcascade_fullbody.xml")

detect = False
detection_end_time = None
timer_start = False
extra_time = 5
out = 0
frame_size = (int(cap.get(3)), int(cap.get(4)))
# fourcc stands for Four character code for saving video and saves as mp4
fourcc = cv2.VideoWriter_fourcc(*"mp4v")

while True:
    # Reading one frame from the video and display it
    _, frame = cap.read()

    cv2.imshow("Camera", frame)

    # classifier to grey frames to identify objects to this code converts colour to black and white frames
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect various faces in camera
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    # Detect various body in camera (error)
    bodies = body_cascade.detectMultiScale(gray, 1.3, 5)

    # checking if any object present / if true record a video
    if len(faces) + len(bodies) > 0:
        if detect:
            # dont stop recording
            timer_start = False
        else:
            #start a new video
            detect = True
            #FORMAT video in form of day mounth year hour minutes and seconds
            current_time = datetime.datetime.now().strftime("%d-%m-%Y-%H-%M-%S")
            # saving video
            out = cv2.VideoWriter(
                f"{current_time}.mp4", fourcc, 20, frame_size)
            print("The Recording has started!!")
    elif detect:
        if timer_start:
            if time.time() - detection_end_time >= extra_time:
                #checks if extra waiting of 5 seconds are over
                detect = False
                timer_start = False
                out.release()
                print("Recording Ended!!")
        else:
            timer_start = True
            detection_end_time = time.time()
    if detect:
        out.write(frame)
    # checks if a button is clicked and terminates loop / ord() --> returns the Unicode code from a given character
    if cv2.waitKey(1) == ord("q"):
        break
# saves the video
out.release()
#release resource to other systems can use the camera
cap.release()
cv2.destroyAllWindows()
