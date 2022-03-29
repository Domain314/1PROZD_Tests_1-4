#include <stdio.h>



int add(int x, int y)
{
  return (x + y);
}

int subtract(int x, int y)
{
  return x - y;
}

int multiply(int x, int y)
{
  return x * y;
}



int remainder(int x, int y)
{
  char decision;
  printf("Division has remainder %d. Round (r), cut off (c), or discard (d)?\n", x%y);
  scanf("%c", &decision);
  int r = x%y;
  int z = x/y;
  printf("%d\n", z);

  switch (decision) {
    case 'r': if (r*2 > y) { return z + 1; } else { return z; } break;
    case 'c': return z;
    case 'd': printf("No new result."); return x;
  }

  return 0;
}



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

int calc(char op[2], int sum, int x)
{
  printf("\n%c", op[0]);
  switch (op[0]) {
    case '+': printf("add!"); sum = add(sum, x);
    case '-':  sum = subtract(sum, x);
    case '*':  sum = multiply(sum, x);
    case '/':  sum = divide(sum, x);
    case '=': printf("stop!");break;
  }
  printf("sum: %d\n", sum );
  return sum;
}

int main()
{
  int sum;

  printf("Number: ");
  scanf(" %d", &sum);

    do {
      char op[2];
      int x;

      printf("Operator: "); scanf(" %c", &op[0]);

      if (op[0] == '='){ break; }
      else
      {
        printf("Number: "); scanf(" %d", &x);
        calc(op[0], sum, x);
      }



    } while(0 < 1);
    return 0;

}


/*
int calc(char _op, int _sum, int _x)
{
  switch (op) {
    case '+': scanf("%d", &x); sum = add(sum, x); break;
    case '-': scanf("%d", &x); sum = subtract(sum, x); break;
    case '*': scanf("%d", &x); sum = multiply(sum, x); break;
    case '/': scanf("%d", &x); sum = divide(sum, x); break;
    case '=': break;
  }
}
*/
