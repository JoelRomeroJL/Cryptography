#include <stdlib.h>
#include <stdio.h>

//------------Function of greatest common divisor--------------	
int gcd(int a, int b){
	int tmp;
	while (b != 0){
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}
//-------------------------------------------------------------	

//------------------Euler's Phi Function-----------------------	
int EulerPhi(int n){
	int size=0;

	for(int p = 1; p <= n; p++) {
		if(gcd(p, n) == 1) {
			size ++;
		}
	}	
	return size;
}
//-------------------------------------------------------------	

//-------Euler's Phi Function for obtain the coprimes----------	
void phi(int n, int phi_values[]){
	int i = 0;
		for(int p = 1; p < n; p++) {
			if(gcd(p, n) == 1) {
				phi_values[i]= p;
				i ++;			
			}
		}
}
//-------------------------------------------------------------	

int main(){
	int n; int size;
	
	printf("Multiplication Table of Z*n \n\n");
	
	printf("Enter n: ");
	scanf("%d", &n);
	
	printf("Value of n: %d \n", n);
//------------------obtaining coprime numbers------------------
	size = EulerPhi(n);
	printf("Number of coprimes: %d \n", size);

	int phi_values[size];
	phi(n, phi_values);

	printf("\nCoprime factors: \n");
		
	for(int i = 0; i<size ;i++) {
		printf( "%d ", phi_values[i]);
	}
	printf("\n");
//-------------------------------------------------------------	
	
//---------Construction of multiplication table----------------	
	int table[size+1][size+1];
	table[0][0]=0;
	int b, mult, a;
	
	for(int y = 0; y<size+1; y++){
		a = phi_values[y];
		table[y+1][0]=a; 
					
		for(int j = 0; j<size+1; j++){
			b = phi_values[j];
			table[0][j+1]=b;
			mult = (a * b) % n;
			table[y+1][j+1] = mult;
		}
	}	
//-------------------------------------------------------------

//----------------------Show Table-----------------------------
	printf("\nTable of Z%dn \n\n",n);
	for(int x=0; x<size+1; x++){
		for(int a=0; a<size+1; a++){
			printf(" %2d ", table[x][a]);
		}
		printf("\n");	
	}
//-------------------------------------------------------------	
	
}
