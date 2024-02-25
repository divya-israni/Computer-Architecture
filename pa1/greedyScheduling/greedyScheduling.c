#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

int main(int argc, char* argv[]) {

    // First peek at how many jobs and timeslots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);

    // We've read the number of timeslots so close the file and start over
    fclose(fp);

    int* start_times = malloc(jobcount * sizeof(int));
    int* end_times = malloc(jobcount * sizeof(int));
    char* job_names = malloc(jobcount * sizeof(char));
    int count = 0;
    for (unsigned int slot=0; slot<timeslots; slot++) {

        FILE* fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        char buf[256];

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }

        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }

        // Now read the rest of the file
        for ( int line=0; line<jobcount; line++ ) {

            if (!fgets(buf, 256, fp)) {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int end;
            unsigned int start;
            if (!sscanf(buf, "%c %d %d", &job, &start, &end)) {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            }

            if( end==slot ) {
                start_times[count] = start;
                end_times[count] = end;
                job_names[count] = job;
                count++;      
            }

        }

        fclose(fp);

    }

    for(int i=0; i<jobcount-1; i++){
        int min = i;
        for(int j= i+1; j<jobcount; j++){
            if(end_times[j]<end_times[min]){
                min = j;
            }
        }
        if(min!=i){
            int temp = start_times[i];
            start_times[i] = start_times[min];
            start_times[min] = temp;

            int temp2 = end_times[i];
            end_times[i] = end_times[min];
            end_times[min] = temp2;

            char temp3 = job_names[i];
            job_names[i] = job_names[min];
            job_names[min] = temp3;
        }
    }
    int time=0;
    int count2=0;
    int* final = calloc(jobcount, sizeof(int));
    int index;
    int* final_start = calloc(jobcount, sizeof(int));
    int last_end = -1;

    
    
    while(time<timeslots){
        count2=0;
        time++;
        for(int i=0; i<jobcount; i++){
            final[i] = 0;
            final_start[i] = 0;
            if(end_times[i]==time && start_times[i]!=0){
                count2++;
                final[i] = end_times[i];
                index = i;
            }
        }
        
        if(count2==1 && start_times[index]>last_end){
            printf("%c\n", job_names[index]);
            last_end = end_times[index];
        }
        else if(count2>1){
            for(int i=0; i<jobcount; i++){
                if(final[i]!=0){
                    final_start[i] = start_times[i];
                }
            }
            int min = 100;
            int index2 = -1;
            for(int i=0; i<jobcount; i++){
                if(final_start[i]<=min && final_start[i]!=0 && start_times[i]>last_end){
                    min = final_start[i];
                    index2 = i;
                }
            }
            if(index2!=-1){
                printf("%c\n", job_names[index2]);
                last_end = end_times[index2];
            }
        }
    }
    
    free(start_times);
    free(end_times);
    free(job_names);
    free(final);
    free(final_start);


    exit(EXIT_SUCCESS);
}
