# ov9655-camara-module


PERIPHERALS	                        MODES	FUNCTIONS	                                               PINS
DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D0	           PC6
           
DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D1	           PC7

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D2	           PC8

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D3	           PC9

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D4	           PE4

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_D5	           PD3

DCMI                          Slave 8 bits External Synchro	                                   DCMI_D6	           PE5

DCMI	                        Slave 8 bits External Synchro                                    DCMI_D7	           PE6

DCMI	                        Slave 8 bits External Synchro                                    DCMI_HSYNC          PA4

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_PIXCLK	       PA6

DCMI	                        Slave 8 bits External Synchro	                                   DCMI_VSYNC          PG9

I2C1	                                                                                        I2C	I2C1_SCL	       PB8

I2C1	                                                                                        I2C	I2C1_SDA	       PB9

RCC	                              BYPASS Clock Source                                         RCC_OSC_IN	      PH0/OSC_IN

RCC	                              BYPASS Clock Source	                                        RCC_OSC_OUT       PH1/OSC_OUT


RCC	                             Clock-out-1	                                                RCC_MCO_1 (DCMI_XCLX)	PA8



#Camera_module_interconnect

a camera module requires four main types of signals to transmit image data properly: control signals, image data signals, power supply signals and camera 
configuration signals


![Screenshot (1914)](https://user-images.githubusercontent.com/71934919/224428533-6170b131-0a74-47c4-8d9f-1b59a5072430.png)
#Control signals
These signals are used for clock generation and data transfer synchronization. The camera 
clock must be provided according to the camera specification.
The camera also provides data synchronization signals:
• HSYNC, used for line synchronization
• VSYNC, used for frame synchronization.
#Image data signals
Each of these signals transmits a bit of the image data. The image data signals width 
represents the number of bits to be transferred at each pixel clock. This number depends on 
the parallel interface of the camera module and on the embedded system interface.
#Power supply signals
As any embedded electronic system, the camera module needs to have a power supply. 
The operating voltage of the camera module is specified in its datasheet.
#Configuration signals
These signals are used to:
• configure the appropriate image features such as resolution, format and frame rate
• configure the contrast and the brightness
