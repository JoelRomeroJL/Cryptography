#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z'};
//char alphabetEn[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

//-------------------------Find index of a letter in alphabet---------------------------
int findIndex(char x){
	int pos = 0; int i;
	if (x == ' '){
		pos = 30;	
	}
	else{

	for (i = 0; i < 27; ++i)
	{  
		if (x == alphabet[i]){
			pos = i;
		}
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
		if (aux > 27){
			cipherText[i] = ' ';	
		}
		else{
			shift = ((key[0] * aux) + key[1]) % 27;  	//((a*mi) + b)% n
			cipherText[i] = alphabet[shift];
		}
	}
} 
//--------------------------------------------------------------------------------------

//----------------------------------Decrypt Function------------------------------------
char Decrypt(char cipherText[], int size, int key[], char plainText[], int inverse){
	int aux, shift, i;
	for (i = 0; i < size; ++i)
	{
		aux = findIndex(cipherText[i]);
		if (aux > 27){
			plainText[i] = ' ';	
		}
		else{
		shift = (inverse * (aux - key[1])) %27; 	//(a^-1 * (ci - b))% n   gcd(a, n)=1
			if(shift < 0){
				shift = shift + 27;
			}
		plainText[i] = alphabet[shift];
		}
	}
} 
//--------------------------------------------------------------------------------------

//------------------------------ReadFile------------------------------------------------
void ReadFile(char name[], char plainText[]){
 	FILE *archivo;
	archivo = fopen(name,"r");
	char caracter;
	int i = 0;
	if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
            return main();
        }
	else{
            while((caracter = fgetc(archivo)) != EOF){
		    	plainText[i] = caracter;
		    	i++;
	    	}
        }
/*	else{
 	    while (feof(archivo) == 0){
	 		fgets(plainText,500,archivo);
 	 	}
    }*/
  fclose(archivo);
}
//--------------------------------------------------------------------------------------


//------------------------------WriteFile-----------------------------------------------
void WriteFile(char name[], char text[]){
	FILE *fp;
 	
 	fp = fopen (name, "w" );
 	
 	fputs(text, fp);
 	
 	fclose (fp);
}
//--------------------------------------------------------------------------------------
	


int main()
{
	int key[1];
	int auxValues[2];
	int size;

	char plainText[500];
	char nplainText[500];
	char cipherText[500];
	
	char name[15]; char name2[15];;
	
	int response, response2;

	printf("\n1. Encrypt \n2. Decrypt \n3. Exit \nEnter option : ");
	scanf("%d", &response);
	
	switch(response){
		case 1:
			printf("Enter name of FILE with the plainText: ");
			scanf("%s", &name);

			ReadFile(name, plainText);
    		printf("\nplainText: %s\n",plainText);
			
			size = strlen(plainText);
			//cipherText[size];	
			
			printf("\nSize of plainText: %d\n", size);

			printf("\nEnter Key\n");
			printf("Enter a: ");
			scanf("%d", &key[0]);

			printf("Enter b: ");
			scanf("%d", &key[1]);
			
//------------------------------Encrypt--------------------------------------
			Encrypt(plainText, size, key, cipherText);
			printf("\nCipherText: %s\n", cipherText);
//---------------------------------------------------------------------------	

			printf("\nEnter name of FILE that save the CipherText: ");
			scanf("%s", &name2);

			WriteFile(name2, cipherText);			

			printf("\nDone! C:");
			break;

		case 2:
			printf("Enter name of FILE with the CipherText: ");
			scanf("%s", &name);

			ReadFile(name, plainText);
    		printf("\nCipherText: %s\n",plainText);

			size = strlen(plainText);
			//nplainText[size];	
			printf("\nSize of cipherText: %d\n", size);

			printf("\nEnter Key\n");
			printf("Enter a: ");
			scanf("%d", &key[0]);

			printf("Enter b: ");
			scanf("%d", &key[1]);

//---------------------------------EEA---------------------------------------
			ExtendedEuclideanAlgorithm(27, key[0], auxValues, 27); 
			printf("\nInverse of %d: %d", key[0] ,auxValues[2]);
//---------------------------------------------------------------------------
//------------------------------Decrypt--------------------------------------
			Decrypt(plainText, size, key, nplainText, auxValues[2]);
			printf("\nplainText : %s\n", nplainText);
//---------------------------------------------------------------------------

			printf("\nEnter name of FILE that save the plainText: ");
			scanf("%s", &name2);

			WriteFile(name2, nplainText);			

			printf("\nDone! C:");
		
			break;

		case 3:
			printf("\nBye! C:");
			return 0;		
			break;	
		default: printf("Seleccione alguna opción\n"); return main();
	}


}
