# Scheduler de Processos com Simulação de Alocação

Este projeto implementa um escalonador de processos que suporta três políticas de escalonamento:
- **FIFO (First In, First Out)**
- **SJF (Shortest Job First)**
- **RR (Round Robin)**

Além disso, o projeto simula a alocação de memória para os processos utilizando um mock de heap (um array estático). Cada processo possui atributos essenciais, tais como:
- **PID** – identificador único do processo.
- **Burst Time** – tempo total necessário para a execução.
- **Remaining Time** – tempo restante para a conclusão.
- **State** – estado atual (READY, RUNNING ou TERMINATED).
- **Contexto** – simulação dos registradores para possibilitar a troca de contexto.

## Funcionalidades

- **Políticas de Escalonamento:**
  - **FIFO:** Processos são executados na ordem de criação.
  - **SJF:** O processo com o menor tempo restante é escolhido para execução.
  - **RR:** Os processos são alternados de forma cíclica, respeitando um quantum de tempo (configurado como 4 ticks por padrão).

- **Alocação de Processos (Interativa):**
  - O usuário pode adicionar quantos processos desejar (até o limite máximo, definido como 15) por meio do terminal.
  - Para cada processo, o usuário informa o burst time.
  - O endereço base de cada processo é gerado automaticamente (exemplo: 0x1000, 0x2000, 0x3000, etc).

- **Escolha Interativa da Política de Escalonamento:**
  - Após a criação dos processos, o usuário escolhe qual política utilizar (FIFO, SJF ou RR) por meio de um menu interativo.

- **Simulação de Execução:**
  - A execução dos processos é simulada por meio de "ticks" do relógio. O escalonador roda até que todos os processos sejam finalizados, com mensagens impressas indicando a troca de contexto e a execução.

## Requisitos

- Compilador C (ex: GCC)
- Ambiente Linux, macOS ou similar que suporte compilação com gcc

## Compilação

Certifique-se de que todos os arquivos `.c` e `.h` estejam no mesmo diretório. Para compilar o projeto, execute:

```bash
gcc -o scheduler main.c scheduler.c process.c heap.c screen.c -Wall -Wextra
```

## Execução

Após a compilação, execute o programa:

```bash
./scheduler
```

## Uso Interativo

Ao executar o programa, o usuário (por exemplo, o professor) poderá:

1. **Adicionar Processos:**
   - O programa perguntará:  
     `Deseja adicionar um novo processo? (S/N):`
   - Se o usuário digitar `S` ou `s`, será solicitado o burst time do processo.
   - Os processos serão criados com endereços base "mockados" (ex.: 0x1000, 0x2000, 0x3000, ...).
   - O usuário pode continuar adicionando processos até atingir o limite (15 processos) ou responder com outro caractere para encerrar a adição.

2. **Escolher a Política de Escalonamento:**
   - Após a criação dos processos, um menu interativo permitirá escolher a política de escalonamento:
     - Digite **1** para FIFO.
     - Digite **2** para SJF.
     - Digite **3** para RR.
   - Caso seja digitada uma opção inválida, o sistema adotará FIFO como padrão.

3. **Execução do Scheduler:**
   - O escalonador executará os processos "tick a tick" até que todos os processos sejam finalizados.
   - Durante a execução, mensagens indicarão as trocas de contexto e qual processo está sendo executado a cada tick.
   - Ao término, uma mensagem informará que todos os processos foram finalizados.

## Testando as Diferentes Políticas de Escalonamento

Embora o programa agora seja interativo, você pode testar cada política conforme o menu apresentado. Lembre-se que:
- **FIFO** executa os processos na ordem de criação.
- **SJF** escolhe o processo com o menor tempo restante.
- **RR** alterna entre os processos, respeitando o quantum configurado (4 ticks por padrão).  
  *Dica:* Para testar um quantum diferente, modifique a variável `time_quantum` em `scheduler.c`.

## Testando a Alocação de Processos

Além de testar a política de escalonamento, você pode explorar a alocação dos processos:
- **Criação e Identificação:**
  - Ao adicionar processos, verifique se os processos são alocados corretamente e identificados pelo seu PID.
- **Simulação da Execução e Finalização:**
  - Observe as mensagens de "Context switch" e "Running process" indicando a troca de contexto e a execução.
  - Confirme que, quando o `remaining_time` de um processo chega a zero, ele é marcado como `TERMINATED` e não é mais escalonado.

## Considerações Finais

- **Round Robin:** O processo atual continuará executando até que seu quantum seja esgotado; depois, o escalonador alterna para o próximo processo ativo.
- **Heap:** A simulação de heap utiliza um array estático. Testes com muitos processos podem evidenciar a limitação de memória.
- **Customizações:** Sinta-se à vontade para modificar os valores de `burst_time`, `time_quantum` ou o número máximo de processos (alterando `MAX_PROCESSES` em `heap.h` e `heap.c`) para explorar diferentes cenários.

## Autor

**Arthur Silva Carneiro**  
Matrícula: **202006321**

---

Este README fornece todas as instruções necessárias para compilar, executar e testar o projeto. Em caso de dúvidas, os comentários no código e as mensagens impressas no terminal ajudarão na compreensão do funcionamento do sistema.

Boa sorte e bons testes!
```