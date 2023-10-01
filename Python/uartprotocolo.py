import uart_lib

uart_lib.outp(0x01, 0xAB)
uart_lib.outpw(0x02, 0x1234)
data = uart_lib.inp(0x03)
print(data)

