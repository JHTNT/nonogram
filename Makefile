.PHONY: all clean
all:
	$(MAKE) -C src all

clean:
	-rm bin/*.exe src/**/*.o