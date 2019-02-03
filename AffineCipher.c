#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z'};

//-------------------------Find index of a letter in alphabet---------------------------
int findIndex(char x){
	int pos = 0; int i;
	for (i = 0; i < 27; ++i)
	{
		if (x == alphabet[i]){
			pos = i;
		}
	}
	return pos;
}
//--------------------------------------------------------------------------------------

//-----------------Extended Euclidean Algorithm for find inverse of a-------------------
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
	values[0] = r0;		//gcd
	values[1] = S0;		
	values[2] = T0;		//Inverse	


	if (values[2] < 0){ //If inverse is negative is added with a 
		values[2] = a + values[2];
	}
}
//--------------------------------------------------------------------------------------

//----------------------------------Encrypt Function------------------------------------
char Encrypt(char plainText[], int size, int key[], char cipherText[]){
	int aux, shift, i;
	for (i = 0; i < size; ++i)
	{
		aux = findIndex(plainText[i]);
		shift = ((key[0] * aux) + key[1]) % 27;  	//((a*mi) + b)% n
		cipherText[i] = alphabet[shift];
	}
} 
//--------------------------------------------------------------------------------------

//----------------------------------Decrypt Function------------------------------------
char Decrypt(char cipherText[], int size, int key[], char plainText[], int inverse){
	int aux, shift, i;
	for (i = 0; i < size; ++i)
	{
		aux = findIndex(cipherText[i]);
		shift = (inverse * (aux - key[1])) % 27; 	//(a^-1 * (ci - b))% n   gcd(a, n)=1
		if(shift < 0){
			shift = shift + 27;
		}
		plainText[i] = alphabet[shift];
	}
} 
//--------------------------------------------------------------------------------------


int main()
{
	int key[1];
	int auxValues[2];
	
	char plainText[] = "autsiliomedesmashoaiunbiejolesbianoxdkikiki" ;
	
	int size = strlen(plainText);
	char cipherText[size];	
	char nplainText[size];	
	

	printf("\nEnter Key\n");
	printf("Enter a: ");
	scanf("%d", &key[0]);

	printf("Enter b: ");
	scanf("%d", &key[1]);
	
	printf("Tamaño: %d\n", size);
	printf("plainText: %s", plainText);

//------------------------------Encrypt--------------------------------------
	Encrypt(plainText, size, key, cipherText);
	printf("\nCipherText: %s", cipherText);
//---------------------------------------------------------------------------	
//---------------------------------EEA---------------------------------------
	ExtendedEuclideanAlgorithm(27, key[0], auxValues, 27); 
	printf("\nInverse of %d: %d", key[0] ,auxValues[2]);
//---------------------------------------------------------------------------
//------------------------------Decrypt--------------------------------------
	Decrypt(cipherText, size, key, nplainText, auxValues[2]);
	printf("\nplainText: %s", nplainText);
//---------------------------------------------------------------------------
}
