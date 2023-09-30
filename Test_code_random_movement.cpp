// Importing file libraries and defining all the instances to control 6 servo motors
#include <Servo.h>
Servo top_left_eyelid;
Servo bottom_left_eyelid;
Servo top_right_eyelid;
Servo bottom_right_eyelid;
Servo Yarm;
Servo Xarm;

// setup function, we have declared which part of the eye is connected to which pin of the Arduino
void setup() {
  top_left_eyelid.attach(10);
  bottom_left_eyelid.attach(11);
  top_right_eyelid.attach(5);
  bottom_right_eyelid.attach(6);
  Yarm.attach(9);
  Xarm.attach(3);
  //we initialize the serial for debugging and we call some functions in order to keep the eye open and in the center and we also add some delay for stability.
  Serial.begin(9600);
  open_eye();
  eye_ball_centert();
  delay(2000);
}


// random movements of up down left right
// The for loops are there as an example of how you can achieve smooth motion or move the eyeballs.
void loop() {
  eye_ball_left();
  delay(680);
  eye_ball_right();
  delay(680);
  eye_ball_centert();
  delay(450);
  synchronous_close();
  eye_ball_centert();
  delay(450);
  look_up();
  delay(400);
  look_down();
  delay(400);
  eye_ball_centert();
  delay(300);
  random_close();
  delay(450);
  look_up();
  delay(400);
  look_down();
  delay(400);
  random_movement();
  delay(400);
  eye_ball_centert();
  delay(300);
  top_left_eyelid.write(2);
  bottom_left_eyelid.write(120);
  delay(200);
  top_left_eyelid.write(55);
  bottom_left_eyelid.write(36);
  delay(200);
  open_eye();
  delay(500);
  for (int i = 60; i < 120; i++)
  {
    Xarm.write(i);
    Yarm.write(i - 5);
    delay(10);
  }
  eye_ball_centert();
  delay(400);
  synchronous_close();
  for (int i = 120; i > 60; i--)  {
    Xarm.write(i);
    Yarm.write(i - 5);
    delay(10);
  }
}

// move eye randomly
void random_movement() {
  Xarm.write(60);
  delay(random(250, 340));
  Yarm.write(80);
  delay(random(250, 340));
  Xarm.write(120);
  delay(random(250, 340));
  Yarm.write(140);
  Xarm.write(60);
  delay(random(250, 340));
  Yarm.write(80);
  delay(random(250, 340));
  Xarm.write(120);
  delay(random(250, 340));
  Yarm.write(140);
  eye_ball_centert();
  delay(300);
  synchronous_close();
  random_close();
}

// random blinking 
void random_close() {
  close_eye();
  // calls close void once
  delay(random(220, 880));
  //calls open void once
  open_eye();
  delay(random(220, 880));
  // random helps create the unprdictable blinks and how long is it going to keep it shut
}

// blinking
void synchronous_close() {
  // calls close void once
  close_eye();
  delay(420);
  //calls open void once
  open_eye();
  delay(222);
  // resulting in one open and close making a blink
}

// Xarm refer to the arm which helps move the eye in X axis
void eye_ball_left() {
  // call servos to move the eyeball left
  Xarm.write(50);
}
void eye_ball_right() {
  // call servos to move the eyeball right
  Xarm.write(130);
}
// keeping th eye ball at exact center (90 , 90) for the center position in other terms (0,0)
void eye_ball_centert() {
  Xarm.write(90);
  Yarm.write(90);
}

// Yarm refer to the arm which helps move the eye in Y axis
void look_up() {
  // calls the servos to move the eye ball up
  Yarm.write(132);
}
void look_down() {
  //calls the servos to move the eye ball up
  Yarm.write(45);
}

void close_eye() {
  // shuting eyelid fully 
  top_left_eyelid.write(2);
  bottom_left_eyelid.write(120);
  top_right_eyelid.write(46);
  bottom_right_eyelid.write(55);
}

void open_eye() {
  // keeping the eye open 
  top_left_eyelid.write(55);
  bottom_left_eyelid.write(36);
  top_right_eyelid.write(2);
  bottom_right_eyelid.write(160);
}

