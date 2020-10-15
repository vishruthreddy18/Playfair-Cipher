#include<stdio.h>
#include<string.h>
#include<ctype.h>

//b[i][j] = *(b[i] + j) = *(*(b + i) + j)

int main(){
	char playfair[5][5];
	char ip[1028],txt[1028], cipher_txt[1028], decoded_txt[1028];
	char c;
	int i, j, k, x, r1, c1, r2, c2, len, m, n;
	int flag = 0;

	puts("\n\t\t---PLAYFAIR CIPHER---\n");
	printf("Enter plain text :");
	scanf("%[^\n]", ip);

	i = 0;
	j = 0;

	//removing spaces and appending to a new array
	while(ip[i] != '\0'){
		if(!(isspace(ip[i]))){
			txt[j++] = ip[i];
		}
		i++;
	}
	txt[j] = '\0';

	//making text caps
	for(i = 0; txt[i] >= 'A' && txt[i] <= 'z'; i++){
		if(islower(txt[i])){
			txt[i] -= 32;
		}
	}

	len = strlen(txt);

	//altering string with repeated letters
	for(i = 0, j = 1; i <= len; i += 2, j += 2){
		if(txt[i] == txt[j]){
			for(k = len; k > i; k--)
				txt[k+1] = txt[k];

            txt[j] = 'X';
            len++;
		}
	}
	txt[i] = '\0';
	len = strlen(txt);

	//adding 'X' if the length of the string is still odd
	if ((len % 2) != 0)
		txt[len] = 'X';
	
	//changing the playfair grid
	i = 0;
	while(txt[i] != '\0'){
		if(txt[i] == 'J')
			flag = 1;
		i++;
	}

	printf("\nText before encryption, after preparation: %s\n", txt);

	//creating 5x5 matrix
	char grid[26] = "MONARCHYBDEFGIKLPQSTUVWXZ";
	
	if(flag == 1)
		 grid[13] = 'J';
		
	x = 0;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			playfair[i][j] = grid[x++];
		}
	}
	putchar('\n');

	//displaying grid
	for (i = 0; i < 5; i++){
		putchar('\t');
		for (j = 0; j < 5; j++)
			printf("%c   ", playfair[i][j]);
		putchar('\n');
	}


	x = 0;
	//creating cipher text
	for(m = 0, n = 1; txt[m] != '\0'; m += 2, n += 2){
		for(i = 0; i < 5; i++){
			for(j = 0; j < 5; j++){
				if(playfair[i][j] == txt[m]){
					r1 = i;
					c1 = j;
				}
				else if(playfair[i][j] == txt[n]){
					r2 = i;
					c2 = j;
				}
			}
		}

		//checking conditions
		if(r1 == r2){
			if(c2 == 4){
				//printf("%c%c", playfair[r1][c1+1], playfair[r2][0]);
				cipher_txt[x++] = playfair[r1][c1+1];
				cipher_txt[x++] = playfair[r2][0];
			}
			else if(c1 == 4){
				//printf("%c%c", playfair[r1][0], playfair[r2][c2+1]);
				cipher_txt[x++] = playfair[r1][0];
				cipher_txt[x++] = playfair[r2][c2+1];
			}
			else{
				//printf("%c%c", playfair[r1][c1+1], playfair[r2][c2+1]);
				cipher_txt[x++] = playfair[r1][c1+1] ;
				cipher_txt[x++] = playfair[r2][c2+1];
			}
		}
		else if(c1 == c2){
			if(r2 == 4){
				//printf("%c%c", playfair[r1+1][c1], playfair[0][c2]);
				cipher_txt[x++] = playfair[r1+1][c1];
				cipher_txt[x++] = playfair[0][c2];
			}
			else if(r1 == 4){
				//printf("%c%c", playfair[0][c1], playfair[r2+1][c2]);
				cipher_txt[x++] = playfair[0][c1];
				cipher_txt[x++] = playfair[r2+1][c2];
			}
			else{
				//printf("%c%c", playfair[r1+1][c1], playfair[r2+1][c2]);
				cipher_txt[x++] = playfair[r1+1][c1];
				cipher_txt[x++] = playfair[r2+1][c2];
			}
		}
		else if(r1 != r2 && c1 != c2){
			//printf("%c%c", playfair[r1][c2], playfair[r2][c1]);
			cipher_txt[x++] = playfair[r1][c2];
			cipher_txt[x++] = playfair[r2][c1];
		}
	}
	cipher_txt[x] = '\0';
	printf("\nThe encrypted text is :%s\n", cipher_txt);
	putchar('\n');

	while(1){
		fflush(stdin);
		printf("Would you like to decipher this text(Y/N)? ");
		c = toupper(getchar());
		if(c == 'Y')
			goto decipher;
		
		else if(c == 'N'){
			puts("Okay cool.");
			goto end;
		}
		else
			puts("Enter a valid answer!!");
	}

	decipher:
		x = 0;
		for(m = 0, n = 1; cipher_txt[m] != '\0'; m += 2, n += 2){
			for(i = 0; i < 5; i++){
				for(j = 0; j < 5; j++){
					if(playfair[i][j] == cipher_txt[m]){
						r1 = i;
						c1 = j;
					}
					else if(playfair[i][j] == cipher_txt[n]){
						r2 = i;
						c2 = j;
					}
				}
			}

			//checking conditions
			if(r1 == r2){
				if(c1 == 0){
					//printf("%c%c", playfair[r1][4], playfair[r2][c2-1]);
					decoded_txt[x++] = playfair[r1][4];
					decoded_txt[x++] = playfair[r2][c2-1];
				}
				else if(c2 == 0){
					//printf("%c%c", playfair[r1][c1-1], playfair[r2][4]);
					decoded_txt[x++] = playfair[r1][c1-1];
					decoded_txt[x++] = playfair[r2][4];
				}
				else{
					//printf("%c%c", playfair[r1][c1-1], playfair[r2][c2-1]);
					decoded_txt[x++] = playfair[r1][c1-1] ;
					decoded_txt[x++] = playfair[r2][c2-1];
				}
			}
			else if(c1 == c2){
				if(r1 == 0){
					//printf("%c%c", playfair[4][c1], playfair[r2-1][c2]);
					decoded_txt[x++] = playfair[4][c1];
					decoded_txt[x++] = playfair[r2-1][c2];
				}
				else if(r2 == 0){
					//printf("%c%c", playfair[r1-1][c1], playfair[4][c2]);
					decoded_txt[x++] = playfair[r1-1][c1];
					decoded_txt[x++] = playfair[4][c2];
				}
				else{
					//printf("%c%c", playfair[r1-1][c1], playfair[r2-1][c2]);
					decoded_txt[x++] = playfair[r1-1][c1];
					decoded_txt[x++] = playfair[r2-1][c2];
				}
			}
			else if(r1 != r2 && c1 != c2){
				//printf("%c%c", playfair[r1][c2], playfair[r2][c1]);
				decoded_txt[x++] = playfair[r1][c2];
				decoded_txt[x++] = playfair[r2][c1];
			}
		}

		decoded_txt[x] = '\0';
		len = strlen(decoded_txt);

		//removing X's
		for(i = 0, j = 1; i <= len; i++, j++){
	    	if(decoded_txt[i] == decoded_txt[j+1] && decoded_txt[j] == 'X'){
	            for(k = j; k < len; k++)
	                decoded_txt[k] = decoded_txt[k+1];
	            len--;
	        }
	    }
		
		decoded_txt[len] = '\0';
		if(decoded_txt[len-1] == 'X')
	    	decoded_txt[len-1] = '\0';
			
		printf("\nDeciphered text: %s\n",decoded_txt);
		goto end;

	end:
		return 0;
}
