
SKETCH=perlin-noise
CC = processing-java


.PHONY: clean

all: run

run:
	$(CC) --force --sketch=$(SKETCH) --output=$(SKETCH)/out --run

clean:
	rm -rf $(SKETCH)/out/
