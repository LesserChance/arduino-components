/**
 * Use this to handle a gray value rotary encoder with a push button
 * https://www.sparkfun.com/products/9117
 * 
 * At least one encoder pin should be interrupt enabled
 * You should replace VAR with whatever you're actually controlling
 */
#include <Encoder.h>
#include <Bounce.h>

// encoder connections
const int VAR_PIN_A = 3;      // Pin for the rotary encoder
const int VAR_PIN_B = 7;      // Pin for the rotary encoder
const int VAR_BUTTON_PIN = 8; // Pin for the rotary encoder button

// variables
Encoder var_encoder(VAR_PIN_A, VAR_PIN_B);
long var_encoder_value = 0;

Bounce var_button = Bounce();
int var_encoder_button_value = 0;

void setup() {
  Serial.begin(9600);
  
  setupVar();
}

void loop() {
  // read the rotation value
  readVar();

  // read the button value
  readVarButton();
}

/**
 * Initialize the pins for var
 */
void setupVar() {
  var_button.attach(VAR_BUTTON_PIN);
  var_button.interval(5);
}

/**
 * Read the rotary encoder rotation state
 */
void readVar() {
  long new_encoder_value = (var_encoder.read() + 2) / 4;
  
  if (new_encoder_value != var_encoder_value) {
    handleEncoderValue(new_encoder_value - var_encoder_value);
    var_encoder_value = new_encoder_value;
  }
}

/**
 * Read the rotary encoder button state
 */
void readVarButton() {
  var_button.update();

  int new_value = var_button.read();
  if (new_value != var_encoder_button_value) {
    var_encoder_button_value = new_value;
    handleEncoderButton(var_encoder_button_value);
  }
}

/**
 * The rotary encoder has changed
 * @param int encoder_direction - 1 or -1 based on direction
 */
void handleEncoderValue(int encoder_direction) {
  Serial.print("encoder rotated: ");
  Serial.println(encoder_direction);
}

/**
 * The rotary encoder button has changed
 * @param int button_value - 0 or 1 for button state
 */
void handleEncoderButton(int button_value) {
  Serial.print("encoder button: ");
  Serial.println(button_value);
}
