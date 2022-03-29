#include <stdio.h>



int add(int x, int y)
{
  return x + y;
}

int subtract(int x, int y)
{
  return x - y;
}

int multiply(int x, int y)
{
  return x * y;
}
/*
int remainder(int x, int y)
{
  char decision;
  printf("Division has remainder %d. Round (r), cut off (c), or discard (d)?\n", x%y);
  scanf("%c", &decision);
  int r = x%y;
  int z = x/y;
  printf("%d\n", z);
  /*
  switch (decision) {
    case 'r': if (r*2 > y) { return z + 1; } else { return z; } break;
    case 'c': return z;
    case 'd': printf("No new result."); return x;
  }

  return 0;
}
*/
int divide(int x, int y)
{
  if (y == 0) {
    printf("Division by 0.\n");
    return x;
  } else if (x%y != 0){
    return 5;//remainder(x, y);
  } else {
    return x/y;
  }
}



int main()
{
  char op = '+';
  printf("%c\n", op);
  int sum, x;

  printf("Number: ");
  scanf("%d", &sum);
    do {
      printf("Operator: ");
      scanf("%c\n", &op);

      switch (op) {
        case '+': scanf("%d", &x); sum = add(sum, x); break;
        case '-': scanf("%d", &x); sum = add(sum, x); break;
        case '*': scanf("%d", &x); sum = add(sum, x); break;
        case '/': scanf("%d", &x); sum = add(sum, x); break;
        case '=': break;
        default:  printf("Unknown operator."); break;

      }

    } while(op != '=');
    return 0;

}
