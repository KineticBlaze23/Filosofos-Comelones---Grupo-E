# Filosofos-Comelones---Grupo-E
# Objetivo General
Implementar una solución al problema de los cinco filósofos comelones mediante procesos, hilos y semáforos en lenguaje C, ejecutada en VirtualBox con Ubuntu Server. El propósito es comprender la sincronización en sistemas operativos y asegurar la correcta administración de recursos compartidos, evitando condiciones de carrera (race condition), interbloqueo (deadlock) e inanición (starvation).

# Descripción del problema
El problema de los filósofos comelones plantea a cinco filósofos sentados alrededor de una mesa que alternan entre pensar y comer.
Para comer, cada filósofo necesita dos tenedores (izquierdo y derecho), pero solo hay uno entre cada par de filósofos.
Esto genera la necesidad de coordinar el acceso a los recursos compartidos (tenedores) para evitar bloqueos y garantizar equidad.

# Solucion propuesta
La solución propuesta utiiliza:
* Hilos (pthread) para representar a cada filósofo.
* Semáforos (sem_t) para controlar el acceso a los tenedores y evitar condiciones de carrera.
* Un semáforo adicional (max_philosophers) que limita a N-1 filósofos en la zona de comer simultáneamente, previniendo el deadlock.

## Logica de ejecucion:
1. Cada filósofo piensa un tiempo aleatorio.
2. Solicita entrar a la zona crítica controlada por max_philosophers.
3. Toma los dos tenedores (semáforos individuales).
4. Come durante un tiempo aleatorio.
5. Suelta los tenedores y libera su turno.

De esta forma la ejecucion no genera bloqueos ni inanición.

# Prevención de problemas.
Los problemas que fueron controlados fueron los siguientes:
* **Race Condition**: Este problema surge cuando varios hilos acceden o modifican un recurso compartido al mismo tiempo, generando resultados inconsistentes. En el programa, cada tenedor se protege con un semáforo individual (sem_wait y sem_post), asegurando que solo un filósofo pueda usarlo a la vez. Esto garantiza exclusión mutua y elimina las condiciones de carrera.
* **Deadlock**: El interbloqueo aparece cuando todos los filósofos toman un tenedor y esperan el otro indefinidamente. Para evitarlo, se implemento un semáforo adicional llamado max_philosophers, que limita a N-1 filósofos dentro de la zona crítica. Así, siempre queda al menos un tenedor libre, permitiendo que uno de ellos pueda completar su ciclo de comer y liberar los recursos.
* **Starvation**: La inanición ocurre cuando uno o más filósofos nunca logran acceder a los recursos porque otros monopolizan los tenedores. La solución evita esto mediante el uso de semáforos justos y liberación ordenada de recursos, de modo que todos los filósofos obtienen turnos equitativos para comer con el paso del tiempo.

# Ejecucion
## Requisitos
* VirtualBox (Ubuntu Server)

## Compilacion y ejecución
<img width="938" height="38" alt="image" src="https://github.com/user-attachments/assets/92d6a34b-4652-4c2f-93c1-2e765d573ae9" />

* **lpthread** : Libreria POSIX threads, permite crear y gestionar hilos.

  ## Capturas
 * **Ejecución en terminal**  
  **Nota:** La ejecución del programa es **infinita**, ya que los filósofos repiten constantemente  el ciclo de **pensar** y **comer** hasta que se interrumpe manualmente (**Ctrl + C**).
  <img width="711" height="485" alt="image" src="https://github.com/user-attachments/assets/e698e73f-2343-402c-bec5-313476173ee3" />
 
* **Monitoreo de procesos**  
  Visualización de **hilos activos** con `htop`, mostrando la ejecución simultánea de los filósofos en tiempo real.
<img width="1020" height="242" alt="image" src="https://github.com/user-attachments/assets/5d1b02c7-f0d8-4dd6-a6bc-060a1e463ce6" />


