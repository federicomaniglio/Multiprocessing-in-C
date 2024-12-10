#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Errore nella creazione della pipe");
        return 1;
    }

    pid_t ritorno = fork();

    if (ritorno < 0) {
        perror("Errore nella fork");
        return 1;
    } else if (ritorno == 0) {
        close(fd[1]);

        char stringaRicevuta[100]; // Array di caratteri per la stringa

        // Lettura dalla pipe. Si usa sizeof(stringaRicevuta) -1
        // per evitare di leggere oltre la dimensione dell'array
        // e lasciare spazio per il carattere nullo di terminazione.
        read(fd[0], stringaRicevuta, sizeof(stringaRicevuta) - 1);

        // Assicurarsi che la stringa sia terminata da un nullo
        stringaRicevuta[sizeof(stringaRicevuta) - 1] = '\0';

        printf("Figlio: Ho ricevuto la stringa: %s\n", stringaRicevuta);
        close(fd[0]);

    } else {
        close(fd[0]);

        char stringa[] = "Questa è la stringa da passare.";


        // Scrittura della stringa. Si usa strlen per ottenere la lunghezza
        // effettiva, in modo da inviare solo i caratteri significativi.
        write(fd[1], stringa, strlen(stringa));

        printf("Genitore: Ho inviato la stringa: %s\n", stringa);

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}