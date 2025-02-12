# Scheduler de Processos com Simulação de Alocação

Este projeto implementa um escalonador de processos capaz de utilizar três políticas de escalonamento:
- **FIFO (First In, First Out)**
- **SJF (Shortest Job First)**
- **RR (Round Robin)**

Além disso, o projeto simula a alocação de memória para os processos utilizando um mock de heap (um array estático). Cada processo possui atributos essenciais, como:
- **PID** – identificador único do processo.
- **Burst Time** – tempo total necessário para a execução.
- **Remaining Time** – tempo restante para a conclusão do processo.
- **State** – estado atual do processo (READY, RUNNING ou TERMINATED).
- **Contexto** – simulação dos registradores para possibilitar a troca de contexto.

## Funcionalidades

- **Políticas de Escalonamento:**
  - **FIFO:** Processos são executados na ordem de criação.
  - **SJF:** O processo com o menor tempo restante é escolhido para execução.
  - **RR:** Os processos são alternados de forma cíclica, respeitando um quantum de tempo (configurado como 4 ticks por padrão).

- **Alocação de Processos:**
  - Os processos são criados com a função `create_process()`, que utiliza um mock de heap para alocar a memória.
  - É possível alterar o número de processos para testar a robustez do sistema de alocação.

- **Simulação de Execução:**
  - A execução dos processos é simulada por meio de “ticks” do relógio, com mensagens impressas para indicar a troca de contexto e a execução.

## Requisitos

- Compilador C (ex: GCC)
- Ambiente Linux, macOS ou similar que suporte compilação com gcc

## Compilação

Para compilar o projeto, execute o seguinte comando no terminal (assegure-se de que todos os arquivos `.c` e `.h` estejam no mesmo diretório):

```bash
gcc -o scheduler main.c scheduler.c process.c heap.c screen.c -Wall -Wextra
```

## Execução

Após a compilação, execute o programa com:

```bash
./scheduler
```

## Como Testar as Diferentes Políticas de Escalonamento

O arquivo `main.c` possui a função `test_scheduler()`, que simula vários "ticks" (passos) da execução do escalonador. Para testar cada política:

1. **SJF (Shortest Job First):**  
   No `main.c`, altere a política para SJF:
   ```c
   set_scheduling_policy(SCHED_SJF);
   ```
   Execute o programa e verifique se o processo com o menor `remaining_time` é escalonado sempre que possível.

2. **FIFO (First In, First Out):**  
   Altere para FIFO:
   ```c
   set_scheduling_policy(SCHED_FIFO);
   ```
   O escalonador deverá executar os processos na ordem em que foram criados, ignorando os tempos de execução.

3. **RR (Round Robin):**  
   Altere para RR:
   ```c
   set_scheduling_policy(SCHED_RR);
   ```
   O escalonador deverá alternar entre os processos respeitando o quantum de tempo (4 ticks por padrão).  
   *Dica:* Para testar um quantum diferente, modifique a variável `time_quantum` em `scheduler.c`.

Após alterar a política desejada, salve, recompile e execute o programa para observar o comportamento.

## Testando a Alocação de Processos

Além de testar a política de escalonamento, você pode explorar a alocação de processos:

1. **Criação e Identificação dos Processos:**
   - A função `mock_processes()` em `main.c` cria três processos com diferentes `burst_time`.
   - Verifique, pela saída do terminal, se os processos são alocados corretamente e identificados pelo seu `PID`.

2. **Simulação da Execução e Finalização:**
   - Observe as mensagens de "Context switch" e "Running process" que indicam a troca de contexto e a execução.
   - Verifique se os processos terminam quando o `remaining_time` chega a zero e se o escalonador ignora processos com estado `TERMINATED`.

3. **Modificando o Número de Processos:**
   - Para testar os limites da alocação, adicione chamadas à função `create_process()` com diferentes `burst_time` na função `mock_processes()`.
   - Lembre-se de que o mock de heap foi dimensionado para suportar até 15 processos. Caso deseje testar mais, ajuste a constante `MAX_PROCESSES` em `heap.h` e `heap.c`.

## Exemplo de Saída

Ao executar o programa com a política SJF, a saída pode ser semelhante a:

```
Context switch to process 1
Running process 1
Tick 0
Context switch to process 1
Running process 1
...
Process 1 finished!
Context switch to process 0
Running process 0
Tick 3
...
```

## Considerações Finais

- **Round Robin:** Se o processo atual ainda não completou seu quantum, ele continuará a ser executado. Caso contrário, o scheduler buscará o próximo processo ativo.
- **Heap:** A simulação de heap utiliza um array estático. Assim, os testes com muitos processos podem evidenciar a limitação de memória alocada.
- **Customizações:** Sinta-se à vontade para alterar os valores de `burst_time`, `time_quantum` ou o número de processos para explorar diferentes cenários e aprofundar o entendimento do comportamento do escalonador.

Este README fornece as instruções necessárias para compilar, executar e testar o projeto. Caso haja dúvidas ou sugestões, os comentários no código e as mensagens impressas no terminal ajudarão na compreensão do funcionamento do sistema.

Boa sorte e bons testes!
```