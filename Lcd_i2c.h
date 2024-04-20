#define _LCD_FIRST_ROW          0x80     //Move cursor to the 1st row
#define _LCD_SECOND_ROW         0xC0     //Move cursor to the 2nd row
#define _LCD_THIRD_ROW          0x94     //Move cursor to the 3rd row
#define _LCD_FOURTH_ROW         0xD4     //Move cursor to the 4th row
#define _LCD_CLEAR              0x01     //Clear display
#define _LCD_RETURN_HOME        0x02     //Return cursor to home position, returns a shifted display to
                                         //its original position. Display data RAM is unaffected.
#define _LCD_CURSOR_OFF         0x0C     //Turn off cursor
#define _LCD_UNDERLINE_ON       0x0E     //Underline cursor on
#define _LCD_BLINK_CURSOR_ON    0x0F     //Blink cursor on
#define _LCD_MOVE_CURSOR_LEFT   0x10     //Move cursor left without changing display data RAM
#define _LCD_MOVE_CURSOR_RIGHT  0x14     //Move cursor right without changing display data RAM
#define _LCD_TURN_ON            0x0C     //Turn Lcd display on
#define _LCD_TURN_OFF           0x08     //Turn Lcd display off
#define _LCD_SHIFT_LEFT         0x18     //Shift display left without changing display data RAM
#define _LCD_SHIFT_RIGHT        0x1E     //Shift display right without changing display data RAM

// LCD Definitions
#define LCD_ADDR 0x4E

// Lcd constants

void I2C_LCD_Cmd(char out_char) {

    char hi_n, lo_n;
    char rs = 0x00;

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    I2C1_Start();
    I2C1_Is_Idle();
    I2C1_Wr(LCD_ADDR);
    I2C1_Is_Idle();
    I2C1_Wr(hi_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(hi_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    Delay_us(100);
    I2C1_Wr(lo_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(lo_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    I2C1_stop();

    if(out_char == 0x01)Delay_ms(2);
}

void I2C_LCD_Chr(char row, char column, char out_char) {

    char hi_n, lo_n;
    char rs = 0x01;

    switch(row){
        case 1:
        I2C_LCD_Cmd(0x80 + (column - 1));
        break;
        case 2:
        I2C_LCD_Cmd(0xC0 + (column - 1));
        break;
        case 3:
        I2C_LCD_Cmd(0x94 + (column - 1));
        break;
        case 4:
        I2C_LCD_Cmd(0xD4 + (column - 1));
        break;
    };

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    I2C1_Start();
    I2C1_Is_Idle();
    I2C1_Wr(LCD_ADDR);
    I2C1_Is_Idle();
    I2C1_Wr(hi_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_ms(5);
    I2C1_Wr(hi_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    Delay_ms(10);
    I2C1_Wr(lo_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_ms(5);
    I2C1_Wr(lo_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    I2C1_stop();
}

void I2C_LCD_Chr_Cp(char out_char) {

    char hi_n, lo_n;
    char rs = 0x01;

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    I2C1_Start();
    I2C1_Is_Idle();
    I2C1_Wr(LCD_ADDR);
    I2C1_Is_Idle();
    I2C1_Wr(hi_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(300);
    I2C1_Wr(hi_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    Delay_us(100);
    I2C1_Wr(lo_n | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(300);
    I2C1_Wr(lo_n | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    I2C1_stop();
}


void I2C_LCD_Init() {

    char rs = 0x00;

    I2C1_Start();
    I2C1_Is_Idle();
    I2C1_Wr(LCD_ADDR);
    I2C1_Is_Idle();

    Delay_ms(30);

    I2C1_Wr(0x30 | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(0x30 | rs | 0x00 | 0x08);
    I2C1_Is_Idle();

    Delay_ms(10);

    I2C1_Wr(0x30 | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(0x30 | rs | 0x00 | 0x08);
    I2C1_Is_Idle();

    Delay_ms(10);

    I2C1_Wr(0x30 | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(0x30 | rs | 0x00 | 0x08);
    I2C1_Is_Idle();

    Delay_ms(10);

    I2C1_Wr(0x20 | rs | 0x04 | 0x08);
    I2C1_Is_Idle();
    Delay_us(50);
    I2C1_Wr(0x20 | rs | 0x00 | 0x08);
    I2C1_Is_Idle();
    I2C1_Stop();

    Delay_ms(10);

    I2C_LCD_Cmd(0x28);
    I2C_LCD_Cmd(0x06);
}

void I2C_LCD_Out(char row, char col, char *text) {
    while(*text)
         I2C_LCD_Chr(row, col++, *text++);
}

void I2C_LCD_Out_Cp(char *text) {
    while(*text)
         I2C_LCD_Chr_Cp(*text++);
}