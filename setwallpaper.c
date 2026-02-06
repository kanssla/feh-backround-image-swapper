#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc == 1){

		int count = 0;
    		char buffer[256];
    		char buffer2[256];
		int change = 0;
		long act = 0;
		char path[512];
		snprintf(path, sizeof(path), "%s/.config/cw/cw.txt", getenv("HOME"));
        	FILE *fpp = fopen(path, "r");
		if (!fpp) {
    			perror("fopen cw.txt");
		    	return 1;
		}

		char *end;
    		while (fgets(buffer, sizeof(buffer), fpp) != NULL) {
			act = strtol(buffer, &end, 10);
    		}
    		fclose(fpp);

        	FILE *fp = popen("ls ~/Documents/wallpapers/", "r");
		char firstim[256] = {0};
		strcpy(buffer2, "feh --bg-scale ~/Documents/wallpapers/");

    		while(fgets(buffer, sizeof(buffer), fp) != NULL) {
			if(count == 0){
				buffer[strcspn(buffer, "\n")] = 0;
				strcpy(firstim, buffer);
			}
			if(count == act){
				buffer[strcspn(buffer, "\n")] = 0;
				strcat(buffer2, buffer);
				system(buffer2);
				change = 1;
				break;
			}
			count++;
    		}
		if(!change && count != 0){
			strcat(buffer2, firstim);
			system(buffer2);
			count = 0;
		}else if(!change){
			fprintf(stderr, "Keine Wallpaper gefunden!");
			return 1;
		}

    		pclose(fp);
		
		FILE *fppp = fopen(path, "w");
		if(fppp == NULL){
			printf("Fehler beim oeffnen der Datei.");
			return 1;
		}
		char str[256];
		sprintf(str, "%d", count);
		fputs(str, fppp);

		fclose(fppp);
    	}else{
        	printf("Invalid number of arguments: %i \n", argc-1);
    	}

    	return 0;
}
