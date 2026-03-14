CC ?= gcc
CFLAGS += -std=c11 -Wall -Wextra -Werror -ICore/Inc

TEST_BIN := build/test_state_machine

.PHONY: test clean

test: $(TEST_BIN)
	@$(TEST_BIN)

$(TEST_BIN): test/test_state_machine.c Core/Src/charger_state_machine.c | build
	$(CC) $(CFLAGS) $^ -o $@

build:
	mkdir -p build

clean:
	rm -rf build
