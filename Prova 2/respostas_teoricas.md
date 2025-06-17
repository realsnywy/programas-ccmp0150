# Respostas Teóricas - Atividade Avaliativa II

## Questão 4: Quicksort Iterativo

### a) Explicação Teórica

#### i) Qual é o papel da pilha na função Quicksort e por que ela é necessária nessa versão do algoritmo?

Na versão iterativa do Quicksort, a **pilha** é usada para **simular a recursão**. Em uma implementação recursiva, o sistema operacional gerencia as chamadas de função em sua própria pilha de chamadas, armazenando os limites (`low`, `high`) de cada sub-array a ser ordenado. A versão iterativa não usa chamadas recursivas, então ela precisa de uma estrutura de dados explícita para "lembrar" quais partes do array ainda precisam ser processadas. A pilha armazena os pares de índices que definem esses sub-arrays pendentes. O algoritmo principal repetidamente desempilha um intervalo, o particiona e empilha os novos sub-intervalos resultantes para processamento futuro.

---

#### ii) Quais seriam as principais vantagens de usar a versão iterativa do Quicksort em comparação com a versão recursiva?

As principais vantagens da versão iterativa em relação à recursiva são:

* **Prevenção de Estouro de Pilha (Stack Overflow)**: A recursão profunda, especialmente em casos de partições desbalanceadas (como em um array já ordenado), pode esgotar a pilha de chamadas do sistema. A versão iterativa evita esse risco, pois utiliza uma pilha cujo tamanho é controlado pelo programador.
* **Controle sobre a Execução**: A abordagem iterativa permite um controle mais refinado. Por exemplo, pode-se otimizar a profundidade da pilha processando sempre o menor sub-array primeiro, garantindo que o uso da pilha seja no máximo `O(log n)`.
* **Possível Otimização de Performance**: Ao eliminar a sobrecarga (overhead) das chamadas de função, a versão iterativa pode ser marginalmente mais rápida e consumir um pouco menos de memória, embora essa diferença seja frequentemente pequena em compiladores modernos.

---

### b) Passo a Passo da Execução (Tracing)

Análise da execução de `Quicksort` com `v[] = {10, 7, 8, 9, 1, 5}`.

**Estado Inicial:**

* `array = {10, 7, 8, 9, 1, 5}`
* `Pilha: []` (vazia)

---

**Passo 1: Empilhar intervalo inicial**

* O intervalo `(0, 5)` é empilhado.
* **Pilha:** `[0, 5]`

---

**Passo 2: Desempilhar `(0, 5)` e Particionar**

* `low = 0`, `high = 5`. O pivô é `array[5] = 5`.
* `Partition` reorganiza o array.
* **Array:** `{1, 5, 8, 9, 10, 7}`
* O pivô `5` agora está no índice `p = 1`.
* **Pilha:** `[]`

---

**Passo 3: Empilhar sub-array da direita**

* Sub-array esquerdo `(0, 0)` é trivial e não é empilhado.
* Sub-array direito `(2, 5)` é válido e é empilhado.
* **Pilha:** `[2, 5]`

---

**Passo 4: Desempilhar `(2, 5)` e Particionar**

* `low = 2`, `high = 5`. O pivô é `array[5] = 7`.
* `Partition` é chamada para o sub-array `{8, 9, 10, 7}`.
* **Array:** `{1, 5, 7, 9, 10, 8}`
* O pivô `7` agora está no índice `p = 2`.
* **Pilha:** `[]`

---

**Passo 5: Empilhar sub-array da direita**

* Sub-array esquerdo `(2, 1)` é inválido.
* Sub-array direito `(3, 5)` é válido e é empilhado.
* **Pilha:** `[3, 5]`

---

**Passo 6: Desempilhar `(3, 5)` e Particionar**

* `low = 3`, `high = 5`. O pivô é `array[5] = 8`.
* `Partition` é chamada para `{9, 10, 8}`.
* **Array:** `{1, 5, 7, 8, 10, 9}`
* O pivô `8` agora está no índice `p = 3`.
* **Pilha:** `[]`

---

**Passo 7: Empilhar sub-array da direita**

* Sub-array esquerdo `(3, 2)` é inválido.
* Sub-array direito `(4, 5)` é válido e é empilhado.
* **Pilha:** `[4, 5]`

---

**Passo 8: Desempilhar `(4, 5)` e Particionar**

* `low = 4`, `high = 5`. O pivô é `array[5] = 9`.
* `Partition` é chamada para `{10, 9}`.
* **Array:** `{1, 5, 7, 8, 9, 10}`
* O pivô `9` agora está no índice `p = 4`.
* **Pilha:** `[]`

---

**Passo 9: Fim da Execução**

* Não há novos sub-arrays para empilhar. A pilha permanece vazia e o loop termina.
* **Array Final Ordenado:** `{1, 5, 7, 8, 9, 10}`
