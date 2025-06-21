# 🚨 Simulador de Atendimento Inteligente em Situações de Emergência Urbana

Um sistema de simulação completo para gerenciamento de emergências urbanas, desenvolvido como projeto da disciplina **Estruturas de Dados I - 2025**.

## 📋 Descrição

Este projeto simula um sistema de atendimento de emergência urbana em uma cidade inteligente, onde diferentes serviços (ambulâncias, bombeiros e polícia) respondem a ocorrências em diversos bairros com base em prioridades, gravidade e disponibilidade de recursos.

O sistema foi projetado para demonstrar a aplicação prática de estruturas de dados fundamentais em um contexto realista e socialmente relevante.

## 🎯 Objetivos

- **Aplicação prática** de estruturas de dados em um cenário real
- **Desenvolvimento incremental** com refatoração progressiva
- **Simulação inteligente** de atendimentos de emergência
- **Otimização de respostas** baseada em prioridade e localização

## 🏗️ Arquitetura do Sistema

### Estruturas de Dados Implementadas

| Estrutura | Status | Aplicação no Sistema |
|-----------|--------|---------------------|
| **Tabela Hash** | ✅ **Concluída** | Acesso rápido a bairros por ID e cidadãos por CPF |
| **Filas (FIFO)** | ✅ **Concluída** | Organização de atendimentos por tipo de serviço |
| **Listas Encadeadas** | ✅ **Concluída** | Gerenciamento de unidades de serviço |
| **Pilhas (LIFO)** | ✅ **Nova - Fase 2** | Histórico individual de atendimentos |
| **Listas Cruzadas** | ✅ **Nova - Fase 2** | Associação bairros ↔ serviços |
| **Árvore BST** | 🔄 *planejado* | Consultas ordenadas por ID/horário |
| **Árvore AVL** | 🔄 *planejado* | Priorização inteligente por gravidade |

## 🚀 Funcionalidades

### ✅ Fase 1 - Simulação Básica (Concluída)
- **Cadastro de Bairros** usando tabela hash para acesso O(1)
- **Gerenciamento de Unidades** (ambulâncias, bombeiros, polícia)
- **Sistema de Filas** separadas por tipo de serviço
- **Simulação Temporal** com controle de disponibilidade
- **Interface Interativa** com menus intuitivos

### ✅ Fase 2 - Histórico e Busca Rápida (Concluída)
- **Histórico de Atendimentos** com pilhas (último atendimento no topo)
- **Sistema de Busca Rápida** de cidadãos por CPF usando hashing
- **Mapa da Cidade** com listas cruzadas conectando bairros e serviços
- **Cadastro de Cidadãos** com informações completas
- **Consultas Avançadas** e estatísticas em tempo real
- **Interface Expandida** com novo menu de consultas e históricos

### 🔄 Fase 3 - Busca e Priorização Inteligente (Em Desenvolvimento)
- Consultas inteligentes com árvores BST
- Priorização automática com árvores AVL balanceadas
- Refatoração para substituir buscas sequenciais

## 🛠️ Tecnologias

- **Linguagem:** C (ISO C99)
- **Paradigma:** Programação estruturada
- **Estruturas:** Implementadas do zero, sem bibliotecas externas
- **Gerenciamento:** Controle manual de memória
- **Arquitetura:** Modular (header/implementação/interface)

## 📁 Estrutura do Projeto
```
📦 emergency-simulator/
├── 📄 main.c           # Interface principal e fluxo do programa
├── 📄 emergencia.h     # Definições de estruturas e protótipos
├── 📄 emergencia.c     # Implementação de todas as funcionalidades
├── 📄 README.md        # Documentação do projeto
```

## 🎮 Como Usar

### Compilação
```bash
gcc -o simulador main.c emergencia.c -std=c99 -Wall
./simulador
```

### 📋 Menus Disponíveis

1. **Iniciar Simulação** - Executa simulação automática com dados de exemplo
2. **Verificar Dados** - Visualiza estado atual do sistema
3. **Configurar Sistema** - Cadastra bairros, cidadãos e unidades
4. **Consultas e Históricos** - Busca por CPF, históricos e estatísticas

## 📈 Progresso do Desenvolvimento

### ✅ Entregáveis Concluídos

| Fase | Prazo | Status | Estruturas Implementadas |
|------|-------|--------|-------------------------|
| **Fase 1** | 02/06/2025 | ✅ **Concluída** | Hash Tables, Filas, Listas |
| **Fase 2** | 16/06/2025 | ✅ **Concluída** | Pilhas, Listas Cruzadas, Hash Expandido |
| **Fase 3** | 23/06/2025 | 🔄 *Em Desenvolvimento* | Árvore BST, Árvore AVL |

## 🏆 Características Técnicas

### 🔧 **Gerenciamento de Memória**
- Alocação dinâmica para todas as estruturas
- Funções dedicadas de liberação de memória
- Controle rigoroso de vazamentos

### ⚡ **Complexidade de Operações**
- **Busca de Bairros**: O(1) médio (Hash Table)
- **Busca de Cidadãos**: O(1) médio (Hash Table)
- **Histórico de Atendimentos**: O(1) inserção/remoção (Pilha)
- **Filas de Atendimento**: O(1) inserção/remoção (FIFO)

### 🎨 **Interface de Usuário**
- Menus intuitivos e organizados
- Feedback claro para todas as operações
- Simulação visual do processo de atendimento
- Estatísticas e relatórios em tempo real

## 🔬 Demonstração das Estruturas

### 📊 **Tabelas Hash**
```
Bairros: ID → O(1) → {id, nome}
Cidadãos: CPF → O(1) → {cpf, nome, email, endereço, bairro}
```

### 📋 **Pilhas de Histórico**
```
Ambulâncias: [Último] → [Penúltimo] → [Anterior] → ...
Bombeiros:   [Último] → [Penúltimo] → [Anterior] → ...
Polícia:     [Último] → [Penúltimo] → [Anterior] → ...
```

### 🗺️ **Listas Cruzadas**
```
Bairro Centro → [Ambulância: 2] → [Bombeiro: 1] → [Polícia: 2]
Bairro Jardim → [Ambulância: 1] → [Bombeiro: 2] → [Polícia: 1]
```

---

**Desenvolvido como projeto acadêmico para Estruturas de Dados I - 2025**  
*Demonstrando aplicação prática de conceitos fundamentais em um contexto socialmente relevante*