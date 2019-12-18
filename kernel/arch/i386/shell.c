#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <kernel/shell.h>

#define MAX_INPUT 10

char input_buffer[MAX_INPUT];
size_t input_len;

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
  printf("help - print this list\n");
  printf("date - print the current time\n");
}

command_entry commands[] = {
  { "help", help_command },
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
  if (isprint(c)) {
    if (input_len + 1 < MAX_INPUT) {
      input_buffer[input_len++] = c;
      putchar(c);
    }
  } else if (c == '\n') {
    putchar('\n');
    run_command(input_buffer);
    restart_prompt();
  } else if (c == '\b') {
    if (input_len > 0) {
      terminal_delete_char();
      input_buffer[--input_len] = '\0';
    }
  }
}