BOARD=teensy41
MCU=TEENSY41
BAUD_RATE=115200
PYTHON3=python3


build:
	west build -p auto -b $(BOARD) app
