#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/shell.h>
#include <kernel/date.h>
#include <kernel/ata.h>

#define MAX_INPUT 256

char input_buffer[MAX_INPUT];
size_t input_len;

bool disabled = false;

void restart_prompt() {
  input_len = 0;
  memset(input_buffer, 0, sizeof(input_buffer));

  printf("> ");
}

typedef struct {
  const char *name;
  void (*handler)(void);
} command_entry;

void help_command(void) {
  printf("help   - print this list\n");
  printf("date   - print the current date\n");
  printf("time   - print the current time\n");
  printf("drives - list attached drives\n");
  printf("exit   - exit the system\n");
}

void exit_command(void) {
  disabled = true;
  terminal_init();
  printf("It is now safe to turn off your computer\n");
}

void date_command(void) {
  datetime date = get_date();
  printf(
      "%d-%s%d-%s%d\n",
      date.year,
      date.month > 9 ? "" : "0",
      date.month,
      date.day > 9 ? "" : "0",
      date.day
  );
}

void time_command(void) {
  datetime date = get_date();
  printf(
      "%s%d:%s%d:%s%d\n",
      date.hour > 9 ? "" : "0",
      date.hour,
      date.minute > 9 ? "" : "0",
      date.minute,
      date.second > 9 ? "" : "0",
      date.second
  );
}

void drives_command(void) {
  ide_print_summary();
}

command_entry commands[] = {
  { "help", help_command },
  { "date", date_command },
  { "time", time_command },
  { "drives", drives_command },
  { "exit", exit_command },
  { "", NULL }
};


void run_command(const char *command) {
  for (command_entry *cmd = commands; cmd->handler; cmd++) {
    if (strcmp(cmd->name, command) == 0) {
      cmd->handler();
      return;
    }
  }

  printf("%s: command not found\n", command);
}

void init_shell() {
  printf(
      "            (_)         \n"
      " _ __   ___  _  ___ ___ \n"
      "| '_ \\ / _ \\| |/ __/ _ \\\n"
      "| | | | (_) | | (_|  __/\n"
      "|_| |_|\\___/|_|\\___\\___|\n"
  );

  restart_prompt();
}

void shell_append(char c) {
  if (disabled) {
    return;
  }
  if (isprint(c)) {
    if (input_len + 1 < MAX_INPUT) {
      input_buffer[input_len++] = c;
      putchar(c);
    }
  } else if (c == '\n') {
    putchar('\n');
    if (input_len > 0) {
      run_command(input_buffer);
    }

    if (!disabled) {
      restart_prompt();
    }
  } else if (c == '\b') {
    if (input_len > 0) {
      terminal_delete_char();
      input_buffer[--input_len] = '\0';
    }
  }
}
