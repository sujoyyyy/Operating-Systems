include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>

#define isnumber(number) (number) > '9' || (number) < '0'
#define gosleep(max) {if (max != 0) sleep(rand() % max); }
#define checkiffault(boolean, string) { if (boolean) {\
  fprintf(stderr, string);\
  exit(1);\
} }

int R,    //Number of riders                    R > 0
    C,    //Bus capacity                        C > 0
    ART,  //max time (ms) for generating riders ART >= 0 && ART <= 1000
    ABT;  //max time (ms) of bus ride           ABT >= 0 && ABT <= 1000

//output file
FILE *f_out = NULL;

sem_t *boarding, *bus_stop, *zapis_proces, *bus_endtrip, *writting = NULL;

//pointers to shared memory
int *process_oder_number, *transported_riders, *waiting_riders, *num_of_free_seats = NULL;

//variable ids in shared memory
int ID_poradi_procesu, ID_prepravenych_riders, ID_waiting_riders, ID_volnych_sedadel = 0;

/*
 * @brief Check if arguments are positives
 * @param argv array of pointers to strings with arguments
*/
void jsou_cisla(char const **argv) {
    for (short i = 1; i <= 4; i++) {
        int delka = strlen(argv[i]);
        for (int j = 0; j < delka; j++)
            if (isnumber(argv[i][j])) {
                fprintf(stderr,
                        "Nektery z argumentu neni cele cislo nebo je zaporny.\nMusi platit:\nR > 0    C > 0    ART >= 0    ABT >= 0\n");
                exit(1);
            }
    }
}


/*
 * @brief Process arguments entered in format: ./bus_sync R C ART ABT
 * @param argc number of elements
 * @param argv array of pointers to strings with arguments
*/
void process_arguments(int argc, char const **argv) {
    if (argc != 5) {
        fprintf(stderr, "Spatny pocet argumentu.\n");
        exit(1);
    }

    jsou_cisla(argv);

    R = atoi(argv[1]);
    C = atoi(argv[2]);
    if ((ART = (atoi(argv[3]))) > 1000) {
        fprintf(stderr, "Nevhodne zadany argument. ART musi byt z intervalu <0,1000>\n");
        exit(1);
    }
    if ((ABT = (atoi(argv[4]))) > 1000) {
        fprintf(stderr, "Nevhodne zadany argument. ABT musi byt z intervalu <0,1000>\n");
        exit(1);
    }
}


int increase(int *puvodni) {
    sem_wait(zapis_proces);
    int tmp = *puvodni;
    *puvodni = *puvodni + 1;
    sem_post(zapis_proces);
    return tmp;
}

/*
 * @brief Alocates memory in shared memory and opens input file
*/
int set_resources() {
    if ((f_out = fopen("bus_sync.out", "w")) == NULL) {
        fprintf(stderr, "Chyba pri otevirani souboru\n");
        exit(1);
    }

    // memory for process order number
    if ((ID_poradi_procesu = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666)) == -1)
        return -1;
    if ((process_oder_number = (int *) shmat(ID_poradi_procesu, NULL, 0)) == NULL)
        return -1;

    // memory for  transported_riders
    if ((ID_prepravenych_riders = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666)) == -1)
        return -1;
    if ((transported_riders = (int *) shmat(ID_prepravenych_riders, NULL, 0)) == NULL)
        return -1;

    // memory for waiting_riders
    if ((ID_waiting_riders = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666)) == -1)
        return -1;
    if ((waiting_riders = (int *) shmat(ID_waiting_riders, NULL, 0)) == NULL)
        return -1;

    // memory for num_of_free_seats
    if ((ID_volnych_sedadel = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666)) == -1)
        return -1;
    if ((num_of_free_seats = (int *) shmat(ID_volnych_sedadel, NULL, 0)) == NULL)
        return -1;

    if ((boarding = sem_open("/xdorda00_boarding1", O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED) {
        return -1;
    }

    if ((bus_stop = sem_open("/xdorda00_zastavka1", O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        sem_close(boarding);
        sem_unlink("/xdorda00_boarding1");
        return -1;
    }

    if ((zapis_proces = sem_open("/xdorda00_zapis_proces1", O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        sem_close(boarding);
        sem_close(bus_stop);
        sem_unlink("/xdorda00_boarding1");
        sem_unlink("/xdorda00_zastavka1");
        return -1;
    }

    if ((bus_endtrip = sem_open("/xdorda00_bus_endtrip1", O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED) {
        sem_close(boarding);
        sem_close(bus_stop);
        sem_close(zapis_proces);
        sem_unlink("/xdorda00_boarding1");
        sem_unlink("/xdorda00_zastavka1");
        sem_unlink("/xdorda00_zapis_proces1");
        return -1;
    }

    if ((writting = sem_open("/xdorda00_zapis1", O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        sem_close(boarding);
        sem_close(bus_stop);
        sem_close(zapis_proces);
        sem_close(bus_endtrip);
        sem_unlink("/xdorda00_boarding1");
        sem_unlink("/xdorda00_zastavka1");
        sem_unlink("/xdorda00_zapis_proces1");
        sem_unlink("/xdorda00_bus_endtrip1");
        return -1;
    }

    return 0;
}


/*
 * @brief clean_resources frees memory and semaphores, closes files
*/
int clean_resources(void) {
    if (shmctl(ID_poradi_procesu, IPC_RMID, NULL) == -1)
        return -1;
    if (shmctl(ID_prepravenych_riders, IPC_RMID, NULL) == -1)
        return -1;
    if (shmctl(ID_waiting_riders, IPC_RMID, NULL) == -1)
        return -1;
    if (shmctl(ID_volnych_sedadel, IPC_RMID, NULL) == -1)
        return -1;

    sem_close(boarding);
    sem_close(bus_stop);
    sem_close(zapis_proces);
    sem_close(bus_endtrip);
    sem_close(writting);
    sem_unlink("/xdorda00_boarding1");
    sem_unlink("/xdorda00_zastavka1");
    sem_unlink("/xdorda00_zapis_proces1");
    sem_unlink("/xdorda00_bus_endtrip1");
    sem_unlink("/xdorda00_zapis1");

    fclose(f_out);
    return 0;
}


void process_rider(int i) {
    sem_wait(writting);
    fprintf(stdout, "%d\t: RID %d\t: start\n", increase(process_oder_number), i);
    sem_post(writting);

    sem_wait(bus_stop);

    sem_wait(writting);
    fprintf(stdout, "%d\t: RID %d\t: enter: %d\n", increase(process_oder_number), i, ++(*waiting_riders));
    sem_post(writting);

    sem_post(bus_stop);
    int sedim_v_buse = 0;
    while (sedim_v_buse == 0) {
        sem_wait(boarding);
        if (*num_of_free_seats > 0) {

            sem_wait(writting);
            fprintf(stdout, "%d\t: RID %d\t: boarding\n", increase(process_oder_number), i);
            sem_post(writting);

            (*num_of_free_seats)--;
            (*waiting_riders)--;
            sedim_v_buse = 1;
        }
        sem_post(boarding);
    }
    sem_wait(bus_endtrip);

    sem_wait(writting);
    fprintf(stdout, "%d\t: RID %d\t: finish\n", increase(process_oder_number), i);
    sem_post(writting);

    (*transported_riders)++;
    exit(0);
}


void gen_rider() {
    for (int i = 1; i <= R; i++) {
        pid_t rider = fork();
        if (rider == 0) {
            process_rider(i);
        }
        gosleep(ART)
    }
    exit(0);
}


void process_bus() {

    sem_wait(writting);
    fprintf(stdout, "%d\t: BUS\t: start\n", increase(process_oder_number));
    sem_post(writting);

    *transported_riders = 0;
    while (*transported_riders < R) {
        sem_wait(bus_stop);

        sem_wait(writting);
        fprintf(stdout, "%d\t: BUS\t: arrival\n", increase(process_oder_number));
        sem_post(writting);

        *num_of_free_seats = C;
        if (*waiting_riders > 0) {

            sem_wait(writting);
            fprintf(stdout, "%d\t: BUS\t: start boarding: %d\n", increase(process_oder_number), *waiting_riders);
            sem_post(writting);

            sem_post(boarding);

            while (*waiting_riders > 0 && *num_of_free_seats > 0);

            sem_wait(writting);
            fprintf(stdout, "%d\t: BUS\t: end boarding: %d\n", increase(process_oder_number), *waiting_riders);
            sem_post(writting);

            sem_wait(boarding);
        }

        sem_wait(writting);
        fprintf(stdout, "%d\t: BUS\t: depart\n", increase(process_oder_number));
        sem_post(writting);

        sem_post(bus_stop);
        gosleep(ABT)

        sem_wait(writting);
        fprintf(stdout, "%d\t: BUS\t: end\n", increase(process_oder_number));
        sem_post(writting);

        sem_post(bus_endtrip);
    }

    sem_wait(writting);
    fprintf(stdout, "%d\t: BUS\t: finish\n", increase(process_oder_number));
    sem_post(writting);

    exit(0);
}

int main(int argc, char const **argv) {
    process_arguments(argc, argv);

    if (set_resources() == -1) {
        clean_resources();
        fprintf(stderr, "Error while allocating memory\n");
        exit(1);
    }

    setbuf(stdout, NULL);//TODO setbuf(f_out, NULL);

    *process_oder_number = 1;
    *waiting_riders = 0;

    //fork of process
    pid_t generator;
    pid_t BUS = fork();
    if (BUS == -1) {
        fprintf(stderr, "Error while forking\n");
        if (clean_resources() == -1)
            fprintf(stderr, "Error while freeing memory\n");
        exit(1);
    } else if (BUS == 0)
        process_bus();
    else {
        generator = fork();
        if (generator == 0)
            gen_rider();
    }

    waitpid(BUS, NULL, 0);//TODO
    waitpid(generator, NULL, 0);

    //free memory
    if (clean_resources() == -1) {
        fprintf(stderr, "Error while freeing shared memory\n");
        exit(1);
    }

    exit(0);
}
