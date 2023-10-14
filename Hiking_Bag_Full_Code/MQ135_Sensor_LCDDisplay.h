
#ifndef MQ135_SENSOR_LCDDISPLAY_H_
#define MQ135_SENSOR_LCDDISPLAY_H_

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#define delay(us)  _delay_us(us)
#define lcd_puts_P(__s)         lcd_puts_p(PSTR(__s))

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 405
#error "This library requires AVR-GCC 4.5 or later, update to newer AVR-GCC compiler !"
#endif


#ifdef _LCD_DEFINITIONS_FILE
#include "lcd_definitions.h"
#endif

#ifndef LCD_CONTROLLER_KS0073
#define LCD_CONTROLLER_KS0073 0  /**< Use 0 for HD44780 controller, 1 for KS0073 controller */
#endif


#ifndef LCD_LINES
#define LCD_LINES           4     /**< number of visible lines of the display */
#endif
#ifndef LCD_DISP_LENGTH
#define LCD_DISP_LENGTH    20     /**< visible characters per line of the display */
#endif
#ifndef LCD_LINE_LENGTH
#define LCD_LINE_LENGTH  0x40     /**< internal line length of the display    */
#endif
#ifndef LCD_START_LINE1
#define LCD_START_LINE1  0x00     /**< DDRAM address of first char of line 1 */
#endif
#ifndef LCD_START_LINE2
#define LCD_START_LINE2  0x40     /**< DDRAM address of first char of line 2 */
#endif
#ifndef LCD_START_LINE3
#define LCD_START_LINE3  0x14     /**< DDRAM address of first char of line 3 */
#endif
#ifndef LCD_START_LINE4
#define LCD_START_LINE4  0x54     /**< DDRAM address of first char of line 4 */
#endif
#ifndef LCD_WRAP_LINES
#define LCD_WRAP_LINES      0     /**< 0: no wrap, 1: wrap at end of visible line */
#endif

#define LCD_IO_MODE      1            /**< 0: memory mapped mode, 1: IO port mode */

#if LCD_IO_MODE

#ifndef LCD_PORT
#define LCD_PORT         PORTC        /**< port for the LCD lines   */
#endif
#ifndef LCD_DATA0_PORT
#define LCD_DATA0_PORT   LCD_PORT     /**< port for 4bit data bit 0 */
#endif
#ifndef LCD_DATA1_PORT
#define LCD_DATA1_PORT   LCD_PORT     /**< port for 4bit data bit 1 */
#endif
#ifndef LCD_DATA2_PORT
#define LCD_DATA2_PORT   LCD_PORT     /**< port for 4bit data bit 2 */
#endif
#ifndef LCD_DATA3_PORT
#define LCD_DATA3_PORT   LCD_PORT     /**< port for 4bit data bit 3 */
#endif
#ifndef LCD_DATA0_PIN
#define LCD_DATA0_PIN    3            /**< pin for 4bit data bit 0  */
#endif
#ifndef LCD_DATA1_PIN
#define LCD_DATA1_PIN    4            /**< pin for 4bit data bit 1  */
#endif
#ifndef LCD_DATA2_PIN
#define LCD_DATA2_PIN    5            /**< pin for 4bit data bit 2  */
#endif
#ifndef LCD_DATA3_PIN
#define LCD_DATA3_PIN    6            /**< pin for 4bit data bit 3  */
#endif
#ifndef LCD_RS_PORT
#define LCD_RS_PORT      LCD_PORT     /**< port for RS line         */
#endif
#ifndef LCD_RS_PIN
#define LCD_RS_PIN       0            /**< pin  for RS line         */
#endif
#ifndef LCD_RW_PORT
#define LCD_RW_PORT      LCD_PORT     /**< port for RW line         */
#endif
#ifndef LCD_RW_PIN
#define LCD_RW_PIN       1            /**< pin  for RW line         */
#endif
#ifndef LCD_E_PORT
#define LCD_E_PORT       LCD_PORT     /**< port for Enable line     */
#endif
#ifndef LCD_E_PIN
#define LCD_E_PIN        2            /**< pin  for Enable line     */
#endif

#elif defined(__AVR_AT90S4414__) || defined(__AVR_AT90S8515__) || defined(__AVR_ATmega64__) || \
defined(__AVR_ATmega8515__)|| defined(__AVR_ATmega103__) || defined(__AVR_ATmega128__) || \
defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__)
#define LCD_IO_DATA      0xC000    /* A15=E=1, A14=RS=1                 */
#define LCD_IO_FUNCTION  0x8000    /* A15=E=1, A14=RS=0                 */
#define LCD_IO_READ      0x0100    /* A8 =R/W=1 (R/W: 1=Read, 0=Write   */
#else
#error "external data memory interface not available for this device, use 4-bit IO port mode"
#endif


#ifndef LCD_DELAY_BOOTUP
#define LCD_DELAY_BOOTUP   16000      /**< delay in micro seconds after power-on  */
#endif
#ifndef LCD_DELAY_INIT
#define LCD_DELAY_INIT      5000      /**< delay in micro seconds after initialization command sent  */
#endif
#ifndef LCD_DELAY_INIT_REP
#define LCD_DELAY_INIT_REP    64      /**< delay in micro seconds after initialization command repeated */
#endif
#ifndef LCD_DELAY_INIT_4BIT
#define LCD_DELAY_INIT_4BIT   64      /**< delay in micro seconds after setting 4-bit mode */
#endif
#ifndef LCD_DELAY_BUSY_FLAG
#define LCD_DELAY_BUSY_FLAG    4      /**< time in micro seconds the address counter is updated after busy flag is cleared */
#endif
#ifndef LCD_DELAY_ENABLE_PULSE
#define LCD_DELAY_ENABLE_PULSE 1      /**< enable signal pulse width in micro seconds */
#endif

/* instruction register bit positions, see HD44780U data sheet */
#define LCD_CLR               0      /* DB0: clear display                  */
#define LCD_HOME              1      /* DB1: return to home position        */
#define LCD_ENTRY_MODE        2      /* DB2: set entry mode                 */
#define LCD_ENTRY_INC         1      /*   DB1: 1=increment, 0=decrement     */
#define LCD_ENTRY_SHIFT       0      /*   DB2: 1=display shift on           */
#define LCD_ON                3      /* DB3: turn lcd/cursor on             */
#define LCD_ON_DISPLAY        2      /*   DB2: turn display on              */
#define LCD_ON_CURSOR         1      /*   DB1: turn cursor on               */
#define LCD_ON_BLINK          0      /*     DB0: blinking cursor ?          */
#define LCD_MOVE              4      /* DB4: move cursor/display            */
#define LCD_MOVE_DISP         3      /*   DB3: move display (0-> cursor) ?  */
#define LCD_MOVE_RIGHT        2      /*   DB2: move right (0-> left) ?      */
#define LCD_FUNCTION          5      /* DB5: function set                   */
#define LCD_FUNCTION_8BIT     4      /*   DB4: set 8BIT mode (0->4BIT mode) */
#define LCD_FUNCTION_2LINES   3      /*   DB3: two lines (0->one line)      */
#define LCD_FUNCTION_10DOTS   2      /*   DB2: 5x10 font (0->5x7 font)      */
#define LCD_CGRAM             6      /* DB6: set CG RAM address             */
#define LCD_DDRAM             7      /* DB7: set DD RAM address             */
#define LCD_BUSY              7      /* DB7: LCD is busy                    */

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC            0x04   /* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT      0x05   /* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC_           0x06   /* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT      0x07   /* display shift on,  inc cursor move dir */

/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF             0x08   /* display off                            */
#define LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */

/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */

/* function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_8BIT_1LINE  0x30   /* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES 0x38   /* 8-bit interface, dual line,   5x7 dots */


#define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )

#define DDR(x) (*(&x - 1))      /* address of data direction register of port x */
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
/* on ATmega64/128 PINF is on port 0x00 and not 0x60 */
#define PIN(x) ( &PORTF==&(x) ? _SFR_IO8(0x00) : (*(&x - 2)) )
#else
#define PIN(x) (*(&x - 2))    /* address of input register of port x          */
#endif


#if LCD_IO_MODE
#define lcd_e_delay()   _delay_us(LCD_DELAY_ENABLE_PULSE)
#define lcd_e_high()    LCD_E_PORT  |=  _BV(LCD_E_PIN);
#define lcd_e_low()     LCD_E_PORT  &= ~_BV(LCD_E_PIN);
#define lcd_e_toggle()  toggle_e()
#define lcd_rw_high()   LCD_RW_PORT |=  _BV(LCD_RW_PIN)
#define lcd_rw_low()    LCD_RW_PORT &= ~_BV(LCD_RW_PIN)
#define lcd_rs_high()   LCD_RS_PORT |=  _BV(LCD_RS_PIN)
#define lcd_rs_low()    LCD_RS_PORT &= ~_BV(LCD_RS_PIN)
#endif

#if LCD_IO_MODE
#if LCD_LINES==1
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_1LINE
#else
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES
#endif
#else
#if LCD_LINES==1
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_8BIT_1LINE
#else
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_8BIT_2LINES
#endif
#endif

#if LCD_CONTROLLER_KS0073
#if LCD_LINES==4
#define KS0073_EXTENDED_FUNCTION_REGISTER_ON  0x2C   /* |0|010|1100 4-bit mode, extension-bit RE = 1 */
#define KS0073_EXTENDED_FUNCTION_REGISTER_OFF 0x28   /* |0|010|1000 4-bit mode, extension-bit RE = 0 */
#define KS0073_4LINES_MODE                    0x09   /* |0|000|1001 4 lines mode */
#endif
#endif

#if LCD_IO_MODE
static void toggle_e(void);
#endif


extern void lcd_init(uint8_t dispAttr);
extern void lcd_clrscr(void);
extern void lcd_home(void);
extern void lcd_display_MQ135_gotoxy(uint8_t x, uint8_t y);
extern void lcd_putc(char c);
extern void lcd_puts(const char *s);
extern void lcd_puts_p(const char *progmem_s);
extern void lcd_command(uint8_t cmd);
extern void lcd_data(uint8_t data);

static void lcd_write(uint8_t data,uint8_t rs);
static uint8_t lcd_read(uint8_t rs);
static uint8_t lcd_waitbusy(void);
static inline void lcd_newline(uint8_t pos);


#endif /* MQ135_SENSOR_LCDDISPLAY_H_ */