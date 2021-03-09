#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define numeroLotes 20
#include <ctype.h>




typedef struct Tonel
{
    int cimento, areia, cal, saibro;
} Tonel;

typedef struct Lote
{
    Tonel tonel;
    int tubo;
} Lote;


//prótotipos das funções
void clear_keyboard_buffer(void);
void caractereEspecial(void);
void construtorLote(Lote*);
int verificaEspaco(Lote*, int*, int*, char*);
void mensagemDeErro(int);
void retirarTodoMaterial(Lote*, int);
void retirarMaterial(Lote*, int, int, char*);
void adicionarMaterial(Lote*, int, int, char*);
void rastreiaLotes(Lote*, int, char*);
int totalToneis(Lote*, int);
void totalNoDeposito(Lote*);
void listaLotes(Lote*, char*);
void stringMinuscula(char*);

int main()
{
    caractereEspecial();
    int resposta;
    Lote lote[numeroLotes];
    construtorLote(lote);
    for (;;)
    {
        char material[10] = "";
        int posicaoLote, quantidade;
        system("cls");
        printf("----------------Controle de Estoque----------------\n\n");
        printf("0 - sair.\n");
        printf("1 - Adicionar material ao estoque.\n");
        printf("2 - Retirar material.\n");
        printf("3 - Listar a quantidade total de cada material no depósito.\n");
        printf("4 - Procurar lotes com um material específico.\n");
        printf("5 - Visualizar um lote.\n\n");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 0:
            exit(1);
        case 1:

            system("cls");
            printf("Material: ");
            clear_keyboard_buffer();
            gets(material);
            printf("\nQuantidade: ");
            scanf("%d", &quantidade);

            printf("\n");
            rastreiaLotes(lote, quantidade, material);

            printf("\nLote: ");
            scanf("%d", &posicaoLote);
            adicionarMaterial(lote, posicaoLote - 1, quantidade, material);
            break;
        case 2:
            system("cls");
            printf("0 - Voltar\n");
            printf("1 - Retirar um material específico de um lote\n");
            printf("2 - Retirar todo os materiais de um lote\n\n");
            scanf("%d", &resposta);
            switch (resposta)
            {
            case 0:
                break;
            case 1:
                system("cls");
                printf("Material: ");
                clear_keyboard_buffer();
                gets(material);
                printf("\nQuantidade: ");
                scanf("%d", &quantidade);
                printf("\nLote: ");
                scanf("%d", &posicaoLote);
                retirarMaterial(lote, posicaoLote - 1, quantidade, material);
                break;
            case 2:
                system("cls");
                printf("Lote: ");
                scanf("%d", &posicaoLote);
                retirarTodoMaterial(lote, posicaoLote);
                break;
            }
            break;
        case 3:
            totalNoDeposito(lote);
            break;
        case 4:
            system("cls");
            printf("Entre com o material que deseja procurar: ");
            clear_keyboard_buffer();
            gets(material);
            listaLotes(lote, material);
            break;
        case 5:
            break;
        default:
            break;
        }
    }
}

// Métodos

//Função para limpar o buffer do teclado
void clear_keyboard_buffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}

// método para permitir caracteres especiais no programa
void caractereEspecial()
{
    printf("%s",setlocale(LC_ALL,""));
    system("cls");
}

//  função para inicializar o estoque com 0
void construtorLote(Lote *lote)
{
    for (int i = 0; i < numeroLotes; i++)
    {
        lote[i].tonel.areia = 0;
        lote[i].tonel.cal = 0;
        lote[i].tonel.cimento = 0;
        lote[i].tonel.saibro = 0;
        lote[i].tubo = 0;
    }
}

// função para tratar erros
void mensagemDeErro(int tipo)
{
    system("cls");
    printf("Erro. ");
    switch (tipo)
    {
    case 0:
        printf("Material inválido!\n\n");
        break;
    case 1:
        printf("O valor inserido é maior que o estoque!\n\n");
        break;
    case 2:
        printf("O valor inserido é maior do que o espaço disponível!\n\n");
        break;
    case 3:
        printf("Erro na retirada de materiais!\n\n");
        break;
    }

    system("pause");
}

// função para retirar todos os materiais de dado lote
void retirarTodoMaterial(Lote *lote, int posicao)
{
    if (posicao >= 0 && posicao < 20)
    {
        lote[posicao].tonel.areia = 0;
        lote[posicao].tonel.cal = 0;
        lote[posicao].tonel.cimento = 0;
        lote[posicao].tonel.saibro = 0;
        lote[posicao].tubo = 0;
        system("cls");
        printf("Materiais retirados com sucesso!\n\n");
        system("pause");
    }
    else
    {
        mensagemDeErro(3);
    }
}

// função para retirar um material de um lote específico
void retirarMaterial(Lote *lote, int posicao, int quantidade, char *material)
{

    system("cls");
    for (int i = 0; i < strlen(material); i++)
    {
        material[i] = tolower(material[i]);
    }

    if (strcmp(material, "areia") == 0)
    {
        if (lote[posicao].tonel.areia < quantidade)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.areia -= quantidade;
            printf("%s retirado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "cal") == 0)
    {
        if (lote[posicao].tonel.cal < quantidade)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.cal -= quantidade;
            printf("%s retirado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "cimento") == 0)
    {
        if (lote[posicao].tonel.cimento < quantidade)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.cimento -= quantidade;
            printf("%s retirado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "saibro") == 0)
    {
        if (lote[posicao].tonel.saibro < quantidade)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.saibro -= quantidade;
            printf("%s retirado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "tubo") == 0)
    {
        if (lote[posicao].tubo < quantidade)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tubo -= quantidade;
            printf("%s retirado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else
    {
        mensagemDeErro(0);
    }
}

// Método para verificar se um lote específico está cheio
int verificaEspaco(Lote *lote, int *posicao, int *quantidade, char *material)
{
    if (strcmp(material, "areia") == 0 || strcmp(material, "cal") == 0 || strcmp(material, "cimento") == 0|| strcmp(material, "saibro") == 0)
    {
        if (totalToneis(lote, *posicao) + *quantidade > 20)
        {
            return 0;
        }

    }
    if (strcmp(material, "tubo") == 0)
    {
        if (lote[*posicao].tubo + *quantidade > 100)
        {
            return 0;
        }
    }
    return 1;
}

void rastreiaLotes(Lote *lote, int quantidade, char *material)
{
    for (int i = 0; i < strlen(material); i++)
    {
        material[i] = tolower(material[i]);
    }
    printf("Lotes disponíveis:\n");
    for (int i = 0; i < numeroLotes; i++)
    {
        if (verificaEspaco(lote, &i, &quantidade, material) == 1)
        {
            printf("| Lote %2d: %d toneis %d tubos |\n", i + 1, totalToneis(lote, i), lote[i].tubo);
        }
    }
}

// Método para retornar o totald e toneis de um lote
int totalToneis(Lote *lote, int posicao)
{
    return lote[posicao].tonel.areia + lote[posicao].tonel.cal + lote[posicao].tonel.cimento + lote[posicao].tonel.saibro;
}

// Função para escrever o total de cada material no deposito
void totalNoDeposito(Lote *lote)
{
    int somaAreia = 0, somaCal = 0, somaCimento = 0, somaSaibro = 0, somaTubo = 0;

    for (int i = 0; i < numeroLotes; i++)
    {
        somaAreia += lote[i].tonel.areia;
        somaCal += lote[i].tonel.cal;
        somaCimento += lote[i].tonel.cimento;
        somaSaibro += lote[i].tonel.saibro;
        somaTubo += lote[i].tubo;
    }
    system("cls");
    printf("Quantidade total no estoque:\n\n");
    printf("Areia: %d\n", somaAreia);
    printf("Cal: %d\n", somaCal);
    printf("Cimento: %d\n", somaCimento);
    printf("Saibro: %d\n", somaSaibro);
    printf("Tubo: %d\n", somaTubo);
    system("pause");
}

// Função para listar os lotes com um material específico
void listaLotes(Lote *lote, char *material)
{
    system("cls");
    stringMinuscula(material);
    printf("Lotes com o material %s: |", material);

    if (strcmp(material, "areia") == 0)
    {
        for (int i = 0; i < numeroLotes; i++)
        {
            if (lote[i].tonel.areia > 0)
            {
                printf(" %2d |", i + 1);
            }
        }
    }
    if (strcmp(material, "cal") == 0)
    {
        for (int i = 0; i < numeroLotes; i++)
        {
            if (lote[i].tonel.cal > 0)
            {
                printf(" %2d |", i + 1);
            }
        }
    }
    if (strcmp(material, "cimento") == 0)
    {
        for (int i = 0; i < numeroLotes; i++)
        {
            if (lote[i].tonel.cimento > 0)
            {
                printf(" %2d |", i + 1);
            }
        }
    }
    if (strcmp(material, "saibro") == 0)
    {
        for (int i = 0; i < numeroLotes; i++)
        {
            if (lote[i].tonel.saibro > 0)
            {
                printf(" %2d |", i + 1);
            }
        }
    }
    if (strcmp(material, "tubo") == 0)
    {
        for (int i = 0; i < numeroLotes; i++)
        {
            if (lote[i].tubo > 0)
            {
                printf(" %2d |", i + 1);
            }
        }
    }
    printf("\n");
    system("pause");
}

// Função para adicionar um material
void adicionarMaterial(Lote *lote, int posicao, int quantidade, char *material)
{
    system("cls");

    stringMinuscula(material);

    if (strcmp(material, "areia") == 0)
    {
        if (quantidade + totalToneis(lote, posicao) > 20)
        {
            mensagemDeErro(2);
        }
        else
        {
            lote[posicao].tonel.areia += quantidade;
            printf("%s adicionado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }

    }
    else if (strcmp(material, "cal") == 0)
    {
        if (quantidade + totalToneis(lote, posicao) > 20)
        {
            mensagemDeErro(2);
        }
        else
        {
            lote[posicao].tonel.cal += quantidade;
            printf("%s adicionado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }

    }
    else if (strcmp(material, "cimento") == 0)
    {
        if (quantidade + totalToneis(lote, posicao) > 20)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.cimento += quantidade;
            printf("%s adicionado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "saibro") == 0)
    {
        if (quantidade + totalToneis(lote, posicao) > 20)
        {
            mensagemDeErro(1);
        }
        else
        {
            lote[posicao].tonel.saibro += quantidade;
            printf("%s adicionado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else if (strcmp(material, "tubo") == 0)
    {
        if (quantidade + lote[posicao].tubo > 100)
        {
            mensagemDeErro(2);
        }
        else
        {
            lote[posicao].tubo += quantidade;
            printf("%s adicionado no lote %d com sucesso!\n\n", material, posicao + 1);
            system("pause");
        }
    }
    else
    {
        mensagemDeErro(0);
    }
}

// função para transformar um String em minuscula
void stringMinuscula(char *string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
}
