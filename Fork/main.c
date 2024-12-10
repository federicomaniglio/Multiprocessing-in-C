#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    // Creazione del processo figlio usando fork()
    pid_t ritorno = fork();

    if (ritorno < 0) {
        // Errore durante la creazione del processo figlio
        perror("Errore durante la fork");
        return 1;
    } else if (ritorno == 0) {
        // Questo codice viene eseguito nel **processo figlio**
        printf("Sono il processo figlio. Il mio PID è %d. Il PID del mio genitore è %d.\n", getpid(), getppid());
    } else {
        // Questo codice viene eseguito nel **processo genitore**
        printf("Sono il processo genitore. Il mio PID è %d. Il PID del mio figlio è %d.\n", getpid(), ritorno);
    }

    // La chiamata a wait() serve a far sì che il processo **genitore** aspetti la terminazione del processo **figlio**.
    // In questo caso, il processo genitore si sospenderà fino alla conclusione del figlio, rendendo possibile la raccolta del suo stato di uscita.
    // Nel caso del **figlio**, la funzione wait() non ha effetto pratico, in quanto non ha processi figli da attendere.
    wait(NULL);
    printf("Il processo genitore ha atteso la terminazione del figlio con PID %d.\n", ritorno);

    // Questo viene eseguito sia nel processo genitore che nel processo figlio
    printf("Processo con PID %d esce dal programma.\n", getpid());

    return 0;
}