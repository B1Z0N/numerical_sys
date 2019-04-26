#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_L 80
int integral_part(int num, int s2, char *fin_num);
void fractional_part(double fr, int s2, char *fin_num, int start);
double nega_pos(double *dec, int s2);
int c_to_i(char digit);
char i_to_c(int digit);
double todec(double s1, char *n);
void decto(double dec, int s2, char *fin_n);
void getdata(double *s1, int *s2, char *n);
void inversion(char *str, int s2);
int main()
{
  double sys1, dec_num;
  int sys2;
  char num[NUM_L];

  getdata(&sys1, &sys2, num);

  if((double)sys2 == sys1) return (0);//If systems are equal

  dec_num = todec(sys1, num);
  printf("Your number in (10)-system:%lf\n", dec_num);
  if(sys2 == 10) return(0);

  decto(dec_num, sys2, num);
  printf("Your number in (%d)-system: %s\n", sys2, num);

  return(0);
}
void decto(double dec, int s2, char *fin_n)
{
  int i;
  double f_part = fabs(dec - ((int) dec));
  _Bool b = 0;
  if(s2 > 0 && dec < 0) b = 1;

  if(s2 < 0) f_part = nega_pos(&dec, s2);

  i = integral_part((int) dec, s2, fin_n);
  fin_n[i++] = '.';
  if(f_part)
  {
  fractional_part(f_part, s2, fin_n, i);
  }
  if(b) inversion(fin_n, s2);

  return;
}
double todec(double s1, char *n)
{
  int i, real_i = 0, length, dot;
  double dec = 0;

  for(length = 0; n[length] != '\n'; length++);

  for(dot = 0; n[dot] != '.' && n[dot] != '\n'; dot++);
  if(n[dot] == '\n') dot--;

  for(i = length - 1; i >= 0; i--)
  {
    if(n[i] == '-' || n[i] == '.') continue;
    dec += c_to_i(n[i]) * pow(s1, real_i + dot - length + 1);
    real_i++;
  }

  if(n[0] == '-') dec = -dec;

  return(dec);
}
double nega_pos(double *dec, int s2)
{
  double fract = (*dec) - ((int) *dec);
  double sys = -s2;
  *dec = (int) *dec;
  if(*dec > 0)
  {
    if(fract > (sys-1)/(sys*sys - 1))//sum of geometrical progression
    {                             //1/s2^2 + 1/s2^4 + 1/s2^6 ...
      *dec += 1;
      fract -= 1;
    }
  }
  else {
    if(-fract > (sys-1)*sys/(sys*sys-1))//sum of geometrical progression
    {                           //1/s2 + 1/s2^3 + 1/s2^5 ...
      *dec -= 1;
      fract += 1;
    }
  }

  return (fract);
}
void fractional_part(double fr, int s2, char *fin_num, int start)
{
  double x;
  int accuracy = 20;
  char *str = (char *) malloc(sizeof(char) * NUM_L);
  int i = start, remainder;
  do{
    x = s2 * fr;
    remainder = ((int) x) % s2;
    fr = x - ((int) x);
    if(remainder < 0)
      fin_num[i] = i_to_c(remainder + fabs(s2));
    else
      fin_num[i] = i_to_c(remainder);
    i++;
    if(i - start == 19)
    {
      printf("Enter your accuracy between 20 and 60:  ");
      scanf("%d", &accuracy);
    }
  } while(fr && i - start < accuracy);
  fin_num[i] = '\0';

  return;
}
void inversion(char *str, int s2)
{
  int i, remainder = 1;

  for(i = 0; str[i]; i++)
  {
    if(str[i] == '.') continue;
    str[i] = i_to_c(s2 - c_to_i(str[i]) - 1);
  }
  for(int k = i - 1; k >= 0; k--)
  {
    if(str[k] == '.') continue;
    int temp = c_to_i(str[k]);
    if(temp + remainder > s2 - 1)
      str[k] = i_to_c(temp + remainder - s2);
    else
    {
      str[k] = i_to_c(temp + remainder);
      return;
    }
  }

  return;
}
int integral_part(int num, int s2, char *fin_num)
{
  if(s2 > 0 && num < 0) num = -num;
	int i = 0;
  do
	{
		int remainder = num % s2;
		num /= s2;
		if (remainder < 0)
		{
			remainder += fabs(s2);
			num += 1;
		}
		fin_num[i++] = i_to_c(remainder);
	} while (num != 0);

  for(int k = 0; k < i/2; k++)
  {
    char temp = fin_num[k];
    fin_num[k] = fin_num[i - k - 1];
    fin_num[i - k - 1] = temp;
  }
  fin_num[i] = '\0';

  return (i);
}
int c_to_i(char digit)
{
  if((digit >= 65) && (digit <= 90))
    return(digit - 55);
  else if((digit >= 48) && (digit <= 57))
    return (digit - 48);
  else return (0);

}
char i_to_c(int digit)
{
  if((digit >= 10) && (digit <= 36))
    return (digit + 55);
  else if((digit >= 0) && (digit <= 9))
    return (digit + 48);
  else return (' ');
}
void getdata(double *s1, int *s2, char *n)
{
  printf("Enter the first system: ");
  scanf("%lf", s1);
  printf("Enter the second system: ");
  scanf("%d", s2);
  printf("Enter the number: ");
  getchar();
  fgets(n, 80, stdin);

  return;
}
