#include<stdio.h>
#include <stdlib.h>
#include<math.h>

int line = 0;

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

  	if( argc < 4 ){
		printf("There are no argments !\n");
		printf("argv[1] : result data\n");
    	printf("argv[2] : maximum range\n");
		printf("argv[3] : minimum range\n");

		exit(1);
	}

	line = count(argv[1]);
	printf("line:   %d\n", line);

	double range_max = atof(argv[2]);
	printf("max=    %e\n", range_max);
	double range_min = atof(argv[3]);
	printf("min=    %e\n", range_min);

	FILE *fp;
	int i, in = 0;
	double *time, *tmp;
	double *xaxis, *yaxis;

    double max_x = 0.0, max_y = 0.0, min_x = 0.0, min_y = 0.0;

	time = (double *)malloc(sizeof(double)*line);
	tmp = (double *)malloc(sizeof(double)*line);

	xaxis = (double *)malloc(sizeof(double)*line);
	yaxis = (double *)malloc(sizeof(double)*line);


	if( (fp=fopen( argv[1], "r")) == NULL ){
		printf("error : text->NULL\n");
		exit(1);
	}

    //ファイル内のデータを読み取り・格納
	for( i = 0; i < line; i++ ){
		fscanf( fp, "%lf %lf", &time[i], &tmp[i]);
	}

    //指定範囲内のデータを判別・出力
	for( i = 0; i < line; i++ ){
		if( ( range_max > time[i] ) && ( range_min < time[i] ) ){
            //printf("%e  %e\n", time[i], tmp[i]);
            xaxis[in] = time[i];
            yaxis[in] = tmp[i];
            in++;
        }
	}

    //指定範囲内で最大値
    for( i = 0; i < in; i++ ){
        if( i == 0 ){
          max_x = xaxis[i];
          max_y = yaxis[i];  
        } else if( i > 0 ){
            if( max_y < yaxis[i] ){
                max_x = xaxis[i];
                max_y = yaxis[i];
            }
        }
	}
    printf("max:    %e  %e\n", max_x, max_y);

    //指定範囲内で最小値
    for( i = 0; i < in; i++ ){
        if( i == 0 ){
          min_x = xaxis[i];
          min_y = yaxis[i];  
        } else if( i > 0 ){
            if( min_y > yaxis[i] ){
                min_x = xaxis[i];
                min_y = yaxis[i];
            }
        }
	}
    printf("min:    %e %e\n", min_x, min_y);

	fclose(fp);


	return 0;

}


