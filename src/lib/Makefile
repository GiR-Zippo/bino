SRC = usb_libusb.c nvstusb.c
OBJ = $(SRC:.c=.o)
OUT = libnvstusb.a

CC = gcc

CFLAGS = -O2 -g
LIBS = -ldl -lusb-1.0

all: $(OUT) $(LIBS)

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)
