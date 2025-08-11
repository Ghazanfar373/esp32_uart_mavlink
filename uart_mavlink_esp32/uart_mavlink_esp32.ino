// Test code for the mavlink interface stuff
// Basically stuff from https://discuss.ardupilot.org/t/mavlink-and-arduino-step-by-step/25566
//
// Connect to the serial port via Mission Planner (115200 baud) and it should connect and send parameters

#include <mavlink.h> 
#define  LED_BUILTIN  2
// Hardware ports
COMMS_MAVLINK mavlink(Serial);
void send_param(void);
// Global variables
unsigned long _1Hz_timer = 0;
uint16_t _counter = 0;
// --- Your new custom parameter variable ---
float my_param = 0.0;

// --- Your new custom boolean parameter variable ---
bool fuel_line = false;

void setup()
{
  // Initialise the UART ports
  Serial.begin(115200);  // Open the mavlink port

  // LEDs
  pinMode(LED_BUILTIN,OUTPUT);

  // Set up the mavlink connection
  mavlink.init();

}

void loop()
{
  // Handle any data we're being sent
  mavlink.update();

  // Send a heartbeat at 1 Hz
  if (millis() - _1Hz_timer > 1UL * 1000) {
    // Update timer
    _1Hz_timer = millis();

    // Update LED
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));

    // Send some data and a heartbeat
    char buf[50];
    sprintf(buf, "Counter is at %3d", _counter++);
     if (_counter % 2 == 0) { // 50 * 100ms = 5 seconds
        fuel_line = !fuel_line;
    }
    mavlink.send_heartbeat();
    mavlink.send_string(buf,sizeof(buf));

    my_param = (float)random(0, 100) / 10.0; // Example: sending a random value
    send_param();
  }
}
// --- New function to send your custom parameter ---
void send_param(void) {

 mavlink_message_t msg;


 mavlink_msg_named_value_float_pack(mavlink.computer.system_id, mavlink.computer.component_id, &msg,
     millis(), "Fuel", my_param);




  mavlink.broadcast(msg);
  delay(100);

  mavlink_msg_named_value_int_pack(mavlink.computer.system_id, mavlink.computer.component_id, &msg,
     millis(), "Fuel_line", (int32_t)fuel_line);

  mavlink.broadcast(msg);

  return;
}
