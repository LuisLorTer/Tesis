import serial

ser = serial.Serial('COM1', 9600)

OUTP_CODE = 0x01
OUTPW_CODE = 0x02
INP_CODE = 0x03


def outp(address, byte):
    data = [OUTP_CODE, (address >> 8) & 0xFF, address & 0xFF, byte]
    ser.write(data)


def outpw(address, word):
    data = [OUTPW_CODE, (address >> 8) & 0xFF, address & 0xFF, (word >> 8) & 0xFF, word & 0xFF]
    ser.write(data)


def inp(address):
    data = [INP_CODE, (address >> 8) & 0xFF, address & 0xFF]
    ser.write(data)
    response = ser.read()
    return response
