#include <Arduino.h>

/*
A B
C D
*/
#define BUTTON_A_PIN 8
#define BUTTON_B_PIN 9
#define BUTTON_C_PIN 7
#define BUTTON_D_PIN 3

int button_A_state = 0;
int button_B_state = 0;
int button_C_state = 0;
int button_D_state = 0;

void buttons_init(void)
{
  pinMode(BUTTON_A_PIN, INPUT);
  pinMode(BUTTON_B_PIN, INPUT);
  pinMode(BUTTON_C_PIN, INPUT);
  pinMode(BUTTON_D_PIN, INPUT);
}

void buttons_handle(void)
{
  button_A_state = digitalRead(BUTTON_A_PIN);
  button_B_state = digitalRead(BUTTON_B_PIN);
  button_C_state = digitalRead(BUTTON_C_PIN);
  button_D_state = digitalRead(BUTTON_D_PIN);
}

bool buttons_pressed(String button = "a")
{
  if (button == "a")
  {
    return button_A_state;
  }
  else if (button == "b")
  {
    return button_B_state;
  }
  else if (button == "c")
  {
    return button_C_state;
  }
  else if (button == "d")
  {
    return button_D_state;
  }
}