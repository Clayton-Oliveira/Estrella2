#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}rgb;
rgb avg (rgb **image, int x, int y, int cols, int rows);

int main (){
	int bla = 0;
	FILE *file;
	int i, j, rows, columns, max;
	rgb **image;
	file = fopen("in.ppm", "rb");
	fseek(file, 2, SEEK_SET);
	fscanf(file, "%d", &columns);
	fscanf(file, "%d", &rows);
	image = (rgb**) malloc (rows*sizeof(rgb*));
	for(i = 0; i < rows; i++){
		image[i] = (rgb*)malloc(columns*sizeof(rgb));
	}
	fscanf(file,"%d\n",&max);
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			fread(&image[i][j],sizeof(rgb),1,file);
		}
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			image[i][j] = avg(image, j, i,columns,rows);
		}
	}

	fclose(file);
	file = fopen("out.ppm", "wb");
	fprintf(file, "P6\n");
	fprintf(file, "%d %d\n",columns,rows);
	fprintf(file, "%d\n",max);
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			fwrite(&image[i][j],sizeof(rgb),1,file);
		}
	}
	fclose(file);
	for(i = 0; i < rows; i++){
		free(image[i]);
	}
	free(image);
}

rgb avg (rgb **image, int x, int y, int cols, int rows){
	int i, j;
	rgb avg;
	int sum_r = 0, sum_g = 0, sum_b = 0, count = 0;
	for(i = y-2; i < y+2; i++){
		for(j = x-2; j < x+2; j++){
			if((j < 0 || j > cols-1) || (i < 0 || i > rows-1));
			else{				
				sum_r += image[i][j].r;
				sum_g += image[i][j].g;
				sum_b += image[i][j].b;
				count++;
			}
		}
	}
	avg.r = sum_r/count;
	avg.g = sum_g/count;
	avg.b = sum_b/count;
	return avg;
}
