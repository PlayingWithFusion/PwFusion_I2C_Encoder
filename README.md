# PwFusion_I2C_Encoder

Are you looking for a way to take your project to the next level? Playing with Fusion's I2C Encoder board is the way to go! This device greatly simplifies connectivity to a microcontroller through the QWIIC system. The typical 5 wires required to use an encoder componet with a microcontroller can be reduced to one QWIIC cable. You can even chain multiple QWIIC devices together for maximum wiring efficiency! If that isn't enough, Playing with Fusion provides Arduino libraries to make writing code for these boards as easy as possible! Weather you are a beginner looking for a simple introduction to the world of hobbyist electronics or an advanced user looking for a rapid prototyping tool, Playing with Fusion's I2C Encoder is right for you!

## I2C Addresses

| ADR 0   |   ADR 1   |   Address |
| --- | --- | --- |
| uncut   |   uncut   |   0x01 |
| cut     |   uncut   |   0x02 |
| uncut   |   cut     |   0x03 |
| cut     |   cut     |   0x04 |

The Playing with Fusion I2C encoder board comes with 4 available I2C addresses, which can be easily selected by cutting the jumpers on the printed circuit board. This allows for 4 encoder boards to be used on the same QWIIC chain. If you would like more than 4, see docs/Programming Instructions and flash a modified firmware with additional I2C address options.

## Example Projects
RC Transmitter: https://github.com/PlayingWithFusion/RC_Transmitter

## Related
| Page | Link |
| --- | --- |
| PwFusion_I2C_Encoder_Arduino_Library:  | https://github.com/PlayingWithFusion/PwFusion_I2C_Encoder_Arduino_Library |
| PwFusion_Data_Transfer:                | https://github.com/PlayingWithFusion/PwFusion_Data_Transfer |
| IFB-40001 PwFusion_I2C_Encoder:   |  https://github.com/PlayingWithFusion/PwFusion_I2C_Encoder |
| IFB-40002 PwFusion_I2C_Joystick:  |  https://github.com/PlayingWithFusion/PwFusion_I2C_Joystick |
| IFB-40003 PwFusion_I2C_Switch:    |  https://github.com/PlayingWithFusion/PwFusion_I2C_Switch |
| IFB-40004 PwFusion_I2C_Buttons:   |  https://github.com/PlayingWithFusion/PwFusion_I2C_Buttons |

Visit https://www.playingwithfusion.com/ for more information.
