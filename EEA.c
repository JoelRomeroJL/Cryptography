#include <stdio.h>
#include <stdlib.h>

//-----------------ExtendedEuclideanAlgorithm------------------------
int ExtendedEuclideanAlgorithm(int r0, int r1, int values[], int a){
	int S0 = 1; int T0 = 0;
	int S1 = 0; int T1 = 1;
	int q, tmp_r, tmp_s, tmp_t;

	while (r1 != 0){
		tmp_r = r1;
		r1 = r0 % tmp_r;
		q = (int)((r0-r1)/tmp_r);

		tmp_s = S1;
		S1 = (S0 - (q * tmp_s));

		tmp_t = T1;
		T1 = (T0 - (q *tmp_t));

		S0 = tmp_s; T0 = tmp_t;
		r0 = tmp_r;
	}

	values[0] = r0;
	values[1] = S0;
	values[2] = T0;

	if (values[2] < 0){
		values[2] = a + values[2];
	}

}
//-------------------------------------------------------------------

int main()
{
	int values[2];
	int a, b;

	printf("Extended Euclidean Algorithm\n");

	printf("Enter a: ");
	scanf("%d", &a);

	printf("Enter b: ");
	scanf("%d", &b);

	ExtendedEuclideanAlgorithm(a, b, values, a);


	printf("\na = %d   b = %d \n", a, b);

	printf("gcd: %d\n", values[0]);
	printf("Coefficient s: %d\n", values[1]);
	printf("Coefficient t (Inverse): %d\n", values[2]);


	return 0;
}
