#include <stdio.h>
#include <math.h>

/* Function: isPrime
 * ---------------------------
 *  Checks if the given number is prime or not
 *
 *  n: Number to check if prime
 *  
 *  returns: 1 if n is prime, 0 otherwise
 */
int isPrime(int n)
{
    if (n <= 1)
        return 0;
    else
    {
        for (int i = 2; i <= (int)(sqrt(n)); i++)
        {
            if (n % i == 0)
                return 0;
        }
    }
    return 1;
}

/* Function: getNextPermutation
 * ---------------------------
 *  Generates the next permutation of the given number
 *
 *  n: Number whose next permutation is to be generated
 *  digs: Digits of the number n
 *
 *  returns: Next permutation of n
 */
int getNextPermutation(int n, int digs)
{
    int quotient = n / 10;
    int remainder = n % 10;
    int power = pow(10, digs - 1);
    return ((remainder * power) + quotient);
}

/* Function: findNumberOfDigits
 * ---------------------------
 *  Gives the number of digits of the given number
 *
 *  n: Number whose number of digits is to be calculated
 *  
 *  returns: Number of digits of n
 */
int findNumberOfDigits(int n)
{
    int digits = 0;
    while(n)
    {
        digits++;
        n /= 10;
    }
    return digits;
}

int main()
{
    int input, result = 1;
    scanf("%d", &input);
    if (input <= 0)
        result = -1;
    else
    {
        int flag = 1;
        int numOfDigs = findNumberOfDigits(input);
        // Loop to check primality of each permutation
        for (int i = 0; i < numOfDigs; i++)
        {
            if (! (isPrime(input)))
            {
                result = 0;
                break;
            }
            input = getNextPermutation(input, numOfDigs);
        }
    }
    printf("%d", result);
}