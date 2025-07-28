#define preto_           0
#define azul_            1
#define verde_           2
#define ciano_           3
#define vermelho_        4
#define magenta_         5
#define marrom_          6
#define cinza_claro_     7
#define cinza_escuro_    8
#define azul_claro_      9
#define verde_claro_    10
#define ciano_claro_    11
#define vermelho_claro_ 12
#define magenta_claro_  13
#define amarelo_        14
#define branco_         15

#include <stdio.h>
#include <windows.h>

typedef struct
{
    char** opcoes;
    int opsQtd;
    int texto;
    int fundo;
} MENU;

// Cria um menu e retorna o número item escolhido
int Menu(MENU mymenu);

int main()
{
    MENU mymenu =
    {
        .opcoes = (char*[]){
            " 1 - Batata",
            " 2 - Cenoura",
            " 3 - Feijao",
            " 4 - Arroz"
            },
        .opsQtd = 4,
        .texto = verde_claro_,
        .fundo = preto_
    };

    printf("%d", Menu(mymenu));

    return 0;
}

int Menu(MENU mymenu)
{
    INPUT_RECORD record;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	COORD pos;
	int total = 0;
	int cont = 0;
	// Tecla
	char c = 0;
	WORD v = 0;

    // Obtendo a posição atual do cursor e as cores de texto e fundo atuais
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    pos.X = 0;
    pos.Y = csbiInfo.dwCursorPosition.Y;
    WORD Oldtexto = csbiInfo.wAttributes & 0xF;
	WORD Oldfundo = csbiInfo.wAttributes & 0xF0;

    // Imprimindo as opções o menu
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.texto | (mymenu.fundo << 4));
    for(int i = 0; i < (mymenu.opsQtd - 1); i++)
        puts(mymenu.opcoes[i]);
    printf("%s", mymenu.opcoes[mymenu.opsQtd-1]);

    // Preparando o menu
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.fundo | (mymenu.texto << 4));
    printf("%s", mymenu.opcoes[cont]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.texto | (mymenu.fundo << 4));

	do {
		FlushConsoleInputBuffer(console);
		WaitForSingleObject(console, INFINITE);

		/* Se PeekConsoleInput() for bem-sucedida,
	    o valor retornado será diferente de zero */
		if(!PeekConsoleInput(console, &record, 1, (LPDWORD)&total))
            return 0;
		if(total > 0)
            if(record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
            {
                v = record.Event.KeyEvent.wVirtualKeyCode;
                c = record.Event.KeyEvent.uChar.AsciiChar;

                if(v == VK_ESCAPE || c == (char)27)
                {
                    // Se teclar ESC, retorna 0
                    FlushConsoleInputBuffer(console);
                    pos.Y = csbiInfo.dwCursorPosition.Y + mymenu.opsQtd;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Oldtexto | (Oldfundo << 4));
                    return 0;
                }
                else if(v == VK_RETURN || c == '\r')
                {
                    // Se teclar Enter, retorna o atual item
                    FlushConsoleInputBuffer(console);
                    pos.Y = csbiInfo.dwCursorPosition.Y + mymenu.opsQtd;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Oldtexto | (Oldfundo << 4));
                    return (cont + 1);
                }
                else if(v == VK_DOWN || v == VK_ADD || v == VK_OEM_PLUS || c == '+')
                {
                    // Retorna para o início da string
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    // Inverte as cores de volta para o original
                    printf("%s", mymenu.opcoes[cont]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.fundo | (mymenu.texto << 4));
                    cont++;
                    pos.Y++;
                    if(pos.Y > (csbiInfo.dwCursorPosition.Y + (mymenu.opsQtd - 1)))
                    {
                        // Se chegar no fim do menu, volta ao início
                        pos.Y = csbiInfo.dwCursorPosition.Y;
                        cont = 0;
                    }
                    // Muda a posição do cursor
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    // Imprime outro item do menu em cores invertidas
                    printf("%s", mymenu.opcoes[cont]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.texto | (mymenu.fundo << 4));
                }
                else if(v == VK_UP || v == VK_SUBTRACT || c == '-')
                {
                    // Retorna para o início da string
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    // Inverte as cores de volta para o original
                    printf("%s", mymenu.opcoes[cont]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.fundo | (mymenu.texto << 4));
                    cont--;
                    pos.Y--;
                    if(pos.Y < csbiInfo.dwCursorPosition.Y)
                    {
                        // Se voltar ao início do menu, vai para o fim
                        pos.Y = csbiInfo.dwCursorPosition.Y + (mymenu.opsQtd - 1);
                        cont = mymenu.opsQtd - 1;
                    }
                    // Muda a posição do cursor
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    // Imprime outro item do menu em cores invertidas
                    printf("%s", mymenu.opcoes[cont]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mymenu.texto | (mymenu.fundo << 4));
                }
            }
	} while(1);
}
