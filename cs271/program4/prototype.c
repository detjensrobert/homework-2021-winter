#include <math.h>
#include <stdio.h>

int UPPER_LIMIT = 300;

void info();

int get_input();
int validate_input(int user_input);

void show_composites(int bound);
int is_composite(int num);

void goodbye();

int main(int argc, char** argv) {
  info();

  int bound = get_input();

  show_composites(bound);

  goodbye();
}

void info() {
  printf("PROGRAM 4: Composite Numbers - Robert Detjens\n");
  printf("This program can generate a list of up to ");
  printf("%i", UPPER_LIMIT);
  printf(" composite numbers.\n");
}

int get_input() {
  int user_input;
  prompt:
  printf("Enter the upper limit for a set of numbers to generate [1..");
  printf("%i", UPPER_LIMIT);
  printf("]: ");

  scanf("%i", &user_input);
  if (!validate_input(user_input)) {
    printf("ERR: out of range\n");
    goto prompt;
  }

  return user_input;
}

int validate_input(int user_input) {
  if (user_input < 1) return 0;
  if (user_input > UPPER_LIMIT) return 0;
  return 1;
}

void show_composites(int bound) {
  int printed = 0;
  for (int i = 1; printed < bound; i++) {
    if (is_composite(i)) {
      printf("%i     ", i);
      printed++;
      if (printed % 10 == 0) {
        printf("\n");
      }
    }
  }
}

int is_composite(int num) {
  int sqrt = round(sqrtf(num));

  for (int i = 2; i <= sqrt; i++) {
    if (num % i == 0) {
      return 1;
    }
  }
  return 0;
}

void goodbye() { printf("\nGoodbye, world!\n"); }
