#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2]; // File descriptors per la pipe
    // I file descriptor sono numeri interi assegnati dal sistema operativo 
    // per identificare i file aperti o altre risorse I/O come pipe o socket.
    // Nel caso delle pipe, il sistema operativo assegna due file descriptor:
    // uno per leggere (fd[0]) e uno per scrivere (fd[1]).
    // Questi file descriptor vengono utilizzati dalle funzioni di sistema 
    // come read() e write() per eseguire operazioni di I/O sui dati 
    // all'interno della pipe.

    // Creazione della pipe
    if (pipe(fd) == -1) {
        perror("Errore nella creazione della pipe");
        return 1;
    }

    // Creazione del processo figlio
    pid_t ritorno = fork();

    if (ritorno < 0) {
        perror("Errore nella fork");
        return 1;
    } else if (ritorno == 0) {
        // Processo figlio: legge dalla pipe

        // Chiusura dell'estremità di scrittura della pipe
        close(fd[1]);

        int numeroRicevuto; // Variabile intera per salvare il numero passato
        
        // Lettura del numero dalla pipe
        read(fd[0], &numeroRicevuto, sizeof(numeroRicevuto));

        printf("Figlio: Ho ricevuto il numero: %d\n", numeroRicevuto);

        // Chiusura dell'estremità di lettura
        close(fd[0]);

    } else {
        // Processo genitore: scrive nella pipe

        // Chiusura dell'estremità di lettura della pipe
        close(fd[0]);

        int numero = 12345; // Numero intero da passare attraverso la pipe
        
        // Scrittura nella pipe
        write(fd[1], &numero, sizeof(numero));

        printf("Genitore: Ho inviato il numero: %d\n", numero);

        // Chiusura dell'estremità di scrittura
        close(fd[1]);

        // Attesa della terminazione del figlio
        wait(NULL);
    }

    return 0;
}