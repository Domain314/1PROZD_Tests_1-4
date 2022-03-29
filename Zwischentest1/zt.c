/*
* BasicCalculator314 by Artjom Moisejev - Copyright (C) 2021 <domain_69@hotmail.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

//global variables
int even = 0, odd = 0;

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

// check number: even or odd
void evenOdd(int sum)
{
  if (sum % 2 == 0) { even++; }
  else { odd++; }
}

//check result and print it
void newResult(int r)
{
  evenOdd(r);
  printf("\nResult: %d\n", r);
}

void noNewResult()
{
  printf("\nNo new result.\n");
}

// calculate and manage division with remainder
int divisionRemainder(int x, int y)
{
  char decision = '0';
  int r = x%y;
  int z = x/y;
  printf("\nDivision has remainder %d. Round (r), cut off (c), or discard (d)?\n", x%y);

  // asks infinitly for a decision
  do {
    printf("Option: "); scanf(" %c", &decision);

    switch (decision) {
      case 'r': if (r*2 > y) { newResult(z + 1); return z + 1; }
                else { newResult(z); return z; } break;
      case 'c': newResult(z); return z;
      case 'd': noNewResult(); return x;
      default: printf("\nUnknown option.\n");
    }
  } while(decision != 'r' && decision != 'c' && decision != 'd');

  return z;
}

// check if divisor is 0, than if division has a remainder, then it calculates the remainderless division
int divide(int x, int y)
{
  if (y == 0) {
    printf("\nDivision by 0."); noNewResult(); return x;
  } else if (x%y != 0){
    return divisionRemainder(x, y);
  } else {
    newResult(x/y); return x/y;
  }
}

// scans and returns input number with proper prefix string
int getNum()
{
  int x;
  printf("\nNumber: "); scanf("%d", &x);
  return x;
}

int main()
{
  char op[2];
  int sum, x;
  sum = getNum(); printf("\n");

  //infinitly ask for operators and numbers, until '='
  do {
    printf("Operator: "); scanf(" %c", &op[0]);
    if (op[0] == '=') { continue; }

    switch (op[0]) {
      case '+': x = getNum(); newResult(sum = add(sum, x)); break;
      case '-': x = getNum(); newResult(sum = subtract(sum, x)); break;
      case '*': x = getNum(); newResult(sum = multiply(sum, x)); break;
      case '/': x = getNum(); sum = divide(sum, x); break;
      default:  printf("\nUnknown operator.\n"); break;
      }

    } while(op[0] != '=');

    printf("\nFinal result: %d\nNumber of even: %d\nNumber of odd: %d", sum, even, odd);
    return 0;
}
