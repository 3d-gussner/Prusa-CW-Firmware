#pragma once

#include "MCP23S17.h"
#include "Trinamic_TMC2130.h"
#include "defines.h"

#define EVENT_COVER_OPENED			1
#define EVENT_COVER_CLOSED			2
#define EVENT_TANK_INSERTED			4
#define EVENT_TANK_REMOVED			8
#define EVENT_BUTTON_SHORT_PRESS	16
#define EVENT_BUTTON_LONG_PRESS		32
#define EVENT_CONTROL_UP			64
#define EVENT_CONTROL_DOWN			128

float celsius2fahrenheit(float);
float fahrenheit2celsius(float);

class Hardware {
public:
	Hardware();

	static void encoder_read();

	static void run_motor();
	static void stop_motor();
	static void enable_stepper();
	static void disable_stepper();
	static void speed_configuration(uint8_t speed, bool fast_mode, bool gear_shifting = false);
	static void acceleration();

	static void run_heater();
	static void stop_heater();

	static void run_led();
	static void stop_led();

	static bool is_cover_closed();
	static bool is_tank_inserted();

	static void echo();
	static void beep();
	static void warning_beep();

	static void set_fans(uint8_t* duties);
	static void set_target_temp(uint8_t target_temp);
	static void set_fan1_duty(uint8_t duty);
	static void set_fan2_duty(uint8_t duty);

	static uint8_t loop();

	#ifdef CW1S
		static void slow_pwm_tick();
		static void adjust_fan_speed(uint8_t fan, uint8_t duty);
		static uint8_t get_heater_pwm_duty();
		static void set_heater_pwm_duty(uint16_t duty);
	#endif

	static uint16_t fan_rpm[3];
	static volatile uint8_t fan_tacho_count[3];
	static volatile uint8_t microstep_control;
	static float chamber_temp_celsius;
	static float chamber_temp;
	static float uvled_temp_celsius;
	static float uvled_temp;
	static bool heater_error;
	#ifdef CW1S
		static bool wanted_heater_pin_state;
		static bool slow_pwm_on;
	#endif

private:
	static MCP outputchip;
	static Trinamic_TMC2130 myStepper;

	static void read_adc();
	static int16_t read_adc_raw(uint8_t pin);
	static void fans_duty();
	static void fans_duty(uint8_t fan, uint8_t duty);
	static void fans_PI_regulator();
	static void fans_check();
	#ifdef CW1S
		static void set_heater_pin_state(bool value);
	#endif

	static uint8_t lcd_encoder_bits;
	static volatile int8_t rotary_diff;
	static uint8_t target_accel_period;

	static uint8_t fan_duty[2];
	static uint8_t fan_pwm_pins[2];
	static uint8_t fan_enable_pins[2];
	static uint8_t fans_target_temp;

	static uint8_t fan_errors;

	static unsigned long accel_ms_last;
	static unsigned long fans_ms_last;
	static unsigned long adc_ms_last;
	static unsigned long heater_ms_last;
	static unsigned long button_timer;
	static double PI_summ_err;
	static bool do_acceleration;
	static bool cover_closed;
	static bool tank_inserted;
	static bool button_active;
	static bool long_press_active;
	static bool adc_channel;

	#ifdef CW1S
		static bool heater_on;
		static bool heater_pin_state;
		static uint16_t heater_pwm_duty;
	#endif
};

extern Hardware hw;
