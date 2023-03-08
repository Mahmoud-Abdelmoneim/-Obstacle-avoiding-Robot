/*
 * main.c
 *  Created on: 9 Sept 2022
 *      Author: Mahmoud Abdelmoniem
 */


#include "main.h"

Motor_t motor1={
		.in_1=PORTB_1,
		.in_2=PORTB_2
};
Motor_t motor2={
		.in_1=PORTB_3,
		.in_2=PORTB_4
};
Ultrasonic_t ultra ;
uint8 dis;
uint8 dis_right=0;
uint8 dis_left=0;
int main()
{
	sei();
	Dio_init();
	Ultrasonic_init();
	while(1){


		dis=UltrasonicReadDistance(&ultra);

		if(dis > STOP_DISTANCE)
		{

			Robot_Move_Forward();
		}
		else if (dis<STOP_DISTANCE)
		{
			Robot_Stop();
			Servo_angle(0);
			_delay_ms(1000);
			dis_right=UltrasonicReadDistance(&ultra);
			_delay_ms(300);
			Servo_angle(180);
			_delay_ms(1000);
			dis_left=UltrasonicReadDistance(&ultra);
			_delay_ms(300);
			Servo_angle(90);
			if(dis_right>dis_left)
			{
				Robot_turn_Right90();
			}
			else if(dis_right<dis_left)
			{
				Robot_turn_Left90();
			}

		}

	}

}

void Robot_Move_Forward()
{
	Motor_Move_Right(&motor1);
	Motor_Move_Right(&motor2);
}

void Robot_Move_Backward()
{
	Motor_Move_Left(&motor1);
	Motor_Move_Left(&motor2);
}

void Robot_Move_Right()
{
	Motor_Move_Right(&motor1);
	Motor_Stop(&motor2);
}

void Robot_Move_Left()
{
	Motor_Stop(&motor1);
	Motor_Move_Right(&motor2);
}

void Robot_turn_Right90()
{

	Robot_Move_Right();
	_delay_ms(1500);
	Robot_Stop();

}

void Robot_turn_Left90()
{

	Robot_Move_Left();
	_delay_ms(1500);
	Robot_Stop();

}

void Robot_Reverse()
{
	Robot_Speed(HIGH_SPEED);
	Robot_Move_Right();
	_delay_ms(3000);
}

void Robot_Move_Step()
{
	Robot_Speed(HIGH_SPEED);
	Robot_Move_Forward();
	_delay_ms(10);

}

void Robot_Stop()
{
	Motor_Stop(&motor1);
	Motor_Stop(&motor2);
	_delay_ms(600);
}

void Robot_Speed(Motor_Sped_t speed)
{
	PWM_SetDuty_Cycle_OCR1A(speed);
	PWM_SetDuty_Cycle_OCR1B(speed);
}

