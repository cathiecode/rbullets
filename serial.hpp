#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/ttyACM0"

int serialFD;
unsigned char longbuf[128];
int longbufptr = 0;

void closeSerial() {
    close(serialFD);
}

void serialinit() {
    struct termios tio;
    int baudRate = B115200;

    serialFD = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (serialFD < 0) {
        std::cout << "シリアルポートを開けませんでした" << std::endl;
        exit(1);
    }

    tio.c_cflag += CREAD;
    tio.c_cflag += CLOCAL;
    tio.c_cflag += CS8;
    tio.c_cflag += 0;
    tio.c_cflag += 0;

    tio.c_lflag &= ~(ECHO | ICANON);
    tio.c_cc[VMIN] = 0;
    tio.c_cc[VTIME]= 0;

    cfsetispeed(&tio, baudRate);
    cfsetospeed(&tio, baudRate);

    cfmakeraw(&tio);

    tcsetattr(serialFD, TCSETS, &tio);

    atexit(closeSerial);
}

void serial2button(){
    unsigned char buf[2];
    bool changeTo;
    int keycode;
    while (read(serialFD, buf, 2) > 0) {
        keycode = buf[0] - 65 - 8;
        if (buf[1] == 33) { // KEYDOWN
            changeTo = true;
        } else {
            changeTo = false;
        }

        std::cout << changeTo << ":" << keycode << std::endl;

        switch (keycode) {
            case 0: // pin8
                Button::up = changeTo;
            break;
            case 1: //pin9
                Button::down = changeTo;
            break;
            case 2: //pin10
                Button::left = changeTo;
            break;
            case 3: //pin11
                Button::right = changeTo;
            break;
            case 4: //pin12
                Button::slow = changeTo;
            break;
            case 5: //pin13
                Button::bomb = changeTo;
            break;
        }
    }
}
