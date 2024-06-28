#include<stdio.h>
#include <stdlib.h>
#include<math.h>

#define eps_max  5.0e-7
#define eps_min -5.0e-7

int line = -1;
//double theory_static = 1.3;

int count(char *file){
	FILE *fp;
	int cnt = 0;
	char chr;

	printf("File : %s\n", file);
	if(( fp = fopen( file, "r" )) == NULL){
		printf("File not found!!\n");
		exit(1);
	}
	
	while( ( chr = fgetc(fp) ) != EOF )
	{
		if( chr == '\n' ){
			cnt++;
		}
	}

	fclose(fp);

	return cnt;
}


int main(int argc, char *argv[]){

	if( argc < 3 ){
		printf("There are no argments !\n");
		printf("argv[1] : result data\n");
		printf("argv[2] : middle in y direction ( optional )\n");
		exit(1);
	}

	line = count(argv[1]);
	printf("line:%d\n", line);

	double mid_line = atof(argv[2]);
	printf("%e\n", mid_line);

	printf("eps_max= %e eps_min= %e\n", eps_max, eps_min);

	FILE *fp;
	int i, j = 0, k;
	double *time, *tmp;
	double min_time[100], min_disp[100], max_time[100], max_disp[100];
	int tag = 0;
	
	time = (double *)malloc(sizeof(double)*line);
	tmp = (double *)malloc(sizeof(double)*line);

	if( (fp=fopen( argv[1], "r")) == NULL ){
		printf("error : text->NULL\n");
		exit(1);
	}


	for( i = 0; i < line; i++ ){
		fscanf( fp, "%lf %lf", &time[i], &tmp[i]);
	}

/*
	for( i = 0; i < line; i++ ){
		if( tmp[i] < eps_max && tmp[i] > eps_min ) printf("time= %e tmp= %e\n", time[i], tmp[i]);
	}
*/


	min_time[0] = time[0];
	min_disp[0] = tmp[0];
	
	max_time[0] = 0.0;
	max_disp[0] = 0.0;

	for( i = 1; i < line; i++ ){
		if( mid_line > tmp[i] ){
			if( tag == 1 ){
				tag = 0;
				j++;
				min_disp[j] = tmp[i];
			}
			if( tmp[i] < min_disp[j] ){
				min_time[j] = time[i];
				min_disp[j] = tmp[i];
			}
		}else if( mid_line < tmp[i] ){
			if( tag == 0 ){
				tag = 1;
				max_disp[j] = tmp[i];
			}
			if( tmp[i] > max_disp[j] ){
				max_time[j] = time[i];
				max_disp[j] = tmp[i];
			}
		}
	}


	printf("MIN\n");
	for( k = 0; k <= j; k++ ){
		printf("min:	time=	%e	,	min_disp	=	%e\n", min_time[k], min_disp[k]);
	}

	printf("MAX\n");
	for( k = 0; k <= j; k++ ){
		printf("max:	time=	%e	,	max_disp	=	%e\n", max_time[k], max_disp[k]);
	}



//	printf("Priod\n");
/*
	double T;
	for ( k = 1; k <= j; k++ ){
		T = min_time[k] - min_time[k-1];
		printf("priod(%d):	%e\n", k, T);
	}
*/

/*
	for( i = 0; i < line; i++ ){
		if( tmp[i] < eps_max && tmp[i] > eps_min ) printf("time= %e tmp= %e\n", time[i], tmp[i]);
	}
*/

	fclose(fp);


	return 0;

}


