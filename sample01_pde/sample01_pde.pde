// sample01_pde.pde

import processing.serial.*;
import ddf.minim.*;

final int BAUD = 57600;
final int FPS = 120;
final int LED_COUNT = 8;

Serial myPort;

Minim minim;
AudioInput in;

void setup() {
  size(320, 240);
  frameRate(FPS);

  String[] arrPorts = Serial.list();
  // printArray(arrPorts);
  String portName = arrPorts[2]; // COM4
  myPort = new Serial(this, portName, BAUD);

  minim = new Minim(this);
  in = minim.getLineIn();
}

void draw() {
  background(255);

  // int val = getValueFromMouse();
  int val = getValueFromAudio();
  // println(val);

  myPort.write(val);

  fill(128);
  text(String.format("%5.1f fps", frameRate), 5, 15);
  text(String.format("value %5d", value), 5, 30);
}

int getValueFromMouse() {
  ellipse(mouseX, mouseY, 20, 20);
  return (int)map(mouseX, 0, width, 0, LED_COUNT + 1);
}

int value = 0;
int getValueFromAudio() {
  float rmsLevel = (in.left.level() + in.left.level()) / 2.0;
  value = (int)map(rmsLevel, 0.0, 1.0, 0.0, LED_COUNT);
  return value;
}
