# To-do

## Geral:
- [x] Desconfio que as funções Item_new em queue.c e em stack.c conflitarão em um arquivo que importe ambas as estruturas
- [ ] Escrever testes completos pras EDs existentes

## Vector:
- [ ] Criar uma função isEmpty
- [ ] Criar uma função at() que retorna o elemento num determinado índice (para ocultar a implementação interna de v->items)
- [ ] Criar uma função de insert em um índice qualquer do Vector
- [ ] Criar uma função de erase em um índice qualquer do Vector
- [ ] Fazer o vetor dar resize pra metade quando o size é 1/4 da capacity

## Queue:
- [x] Criar uma função destroy para dar free
- [x] Adicionar tratamento de erro na função enqueue

## Stack:
- [x] Criar uma função destroy para dar free
- [x] Adicionar tratamento de erro na função push

## Bag:
- [x] Criar uma função destroy para dar free
- [x] Adicionar tratamento de erro na função add
