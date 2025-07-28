# Best-Menu-in-C
Ideal console menu for Windows in pure C, featuring interactive navigation, customizable colors, and dynamic item selection.

### **Menus no Console: Limitações e uma Solução em C**

#### **O Problema dos Menus em Console**
Enquanto aplicações Windows tradicionais têm suporte nativo a menus sofisticados (com submenus, atalhos, ícones e barras separadoras), o **console** é um ambiente limitado:
- **Sem APIs dedicadas:** Não há funções nativas para criar menus interativos.
- **Input primitivo:** Leitura de teclado/mouse requer tratamento manual de eventos.
- **Sem componentes visuais:** Tudo deve ser desenhado via texto, incluindo seleção e feedback visual.

Isso explica por que até sistemas como BIOS usam interfaces simples baseadas em texto — a console é um ambiente "cru", compartilhado entre múltiplos programas sem padronização para elementos UI.

---

#### **Solução Proposta: A Função `Menu()`**
A função `Menu()` implementa um sistema interativo para consoles Windows, com:

1. **Seleção Visual por Cores**
   - Inverte cores do item selecionado (`texto/fundo`).
   - Suporte a 16 cores pré-definidas (ex: `verde_claro_`, `vermelho_`).

2. **Navegação Intuitiva**
   - **Teclas ↑/↓**: Movimento entre itens.
   - **+/-**: Alternativas para navegação (útil em teclados sem teclas direcionais).
   - **Enter**: Confirma seleção.
   - **ESC**: Cancela (retorna `0`).

3. **Preservação do Estado**
   - Restaura a posição original do cursor e cores após seleção.
   - Limpa eventos não lidos do buffer de entrada (`FlushConsoleInputBuffer`).

4. **Estrutura Flexível**
   - Recebe um `struct MENU` com:
     - `opcoes`: Array de strings.
     - `opsQtd`: Número de itens.
     - `texto`/`fundo`: Cores personalizáveis.
<img width="157" height="119" alt="image" src="https://github.com/user-attachments/assets/e741d37c-a982-4500-b550-d5e85458495b" />

---

#### **Vantagens**
- **Portável:** Funciona em qualquer console Windows.
- **Sem dependências externas:** Usa apenas a API do Windows (`windows.h`).
- **Customizável:** Cores e itens são definidos pelo usuário.

#### **Limitações**
- **Sem mouse:** Navegação apenas por teclado, mas nada impede de ser implementado já que a WinAPI tem recursos para isso.
- **Sem submenus:** Estrutura plana (uma camada). Um submenu deve ser criado a partir de outra chamada de `Menu()`.
