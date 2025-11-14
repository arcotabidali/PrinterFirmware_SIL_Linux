
# Linux host SIL build for full firmware as a shared object
HOST_CC     = gcc
HOST_CFLAGS = -O2 -g -Wall -fPIC -DHOST_BUILD -ICore/Inc -ISIL_Stubs
HOST_SRC    = $(wildcard Core/Src/*.c) $(wildcard SIL_Stubs/*.c)
HOST_OUT    = build/libprinter_firmware.so

all: $(HOST_OUT)

$(HOST_OUT): $(HOST_SRC)
	mkdir -p build
	$(HOST_CC) $(HOST_CFLAGS) -shared -o $@ $^

clean:
	rm -rf build
