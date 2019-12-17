void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  reboot();
  Serial.print("Badge rebooted\r\n");
  ReadGreeting();
  Serial.write("Greeting readed\nEntered command mode\n");
  cmdDebug();
  Serial.write("Debug mode on\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  cmdPassword();
}

void reboot()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);
}


void ReadGreeting() {
  char temp;
  do
  {
    temp = Serial1.read();
  } while(temp != '5');
  Serial1.write("enter\r\n");
  do
  {
    temp = Serial1.read();
  } while (temp != '>');
}

void cmdDebug() {
  char temp;
  Serial1.print("debug on\r\n");
  do
  {
    temp = Serial1.read();
  } while (temp != '>');
  delay(500);
}

void password_check_started()
{
  bool is_led_on = false;
  while(!is_led_on)
  {
    if(analogRead(8) < 150)
      is_led_on = true;
  }
  while(is_led_on)
  {
    if(analogRead(8) > 300)
      is_led_on = false;
  }
}

unsigned long check_time()
{
  unsigned long timediff;
  bool is_led_on = false;
  timediff = millis();
  while(!is_led_on)
  {
    if(analogRead(8) < 150)
      is_led_on = true;
  }
  while(is_led_on)
  {
    if(analogRead(8) > 300)
      is_led_on = false;
  }
  return millis() - timediff;
}

void cmdPassword() {
  char temp;
  int pos = 0;
  unsigned int val;
  unsigned long timediff;
  bool is_led_on = false;
  unsigned char buf[8];
  Serial.println("enter password\r\n");
  while (pos != 8)
  {
    val = Serial.read();
    if (val == -1)
    continue;
    buf[pos] = Serial.read();
    pos++;
  }
  Serial1.print("password ");
  Serial1.write(buf, 8);
  Serial1.print("\r\n");

  password_check_started();
  Serial.println(check_time());

  do
  {
    temp = Serial1.read();
  } while (temp != '>');
}
