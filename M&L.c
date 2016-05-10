/*
 * M&L.c
 * 
 * Copyright 2016 Thalyson <Thalyson@THALYSON-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int aleatorio(int min,int max){
		int r;
		r = rand();
		r = r % max;
		if(r < min)
		r += min;
		return r;
	}

int main()
{
	int m,n,q,num1,num2,i;
	printf("Informe numero minimo:");
	scanf("%d",&m);
	printf("Informe o numero maximo:");
	scanf("%d",&n);
	printf("Informe o numero de coordenadas a serem geradas: ");
	scanf("%d",&q);
	for(i=0;i<q;i++){
	srand(time(NULL));
	num1 = aleatorio(m,n);
	sleep(1);
	num2 = aleatorio(m,n);
	printf("\nNum1 = %d\nNum2 = %d\n",num1,num2);
}
	return 0;
}

