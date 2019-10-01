#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* Nomes: João Coelho, Pedro Mota
Números: 33787, 33904
Data: 05/01/2017 */


#define TAM_NOME 50	    // tamanho max de char na string - MACRO
#define TAM_VECTOR 50	// numero de produtos que podem ser armazenadas em memoria

// estruturas permitem definir novos tipos de dados - tipo de dados neste caso ira ter o nome do produto- e composto por duas strings, categoria e calorias
struct produto
{
    char nome[TAM_NOME];
    int calorias;
    char categoria[TAM_NOME];
};

void lista_todos_produtos();
void ler_novo_produto(struct produto * m);
void gravar_produtos_para_ficheiro();
void carregar_produtos_do_ficheiro();
void le_input(char * temp);
void eliminar_produto();

// variaveis globais

struct produto vec_produtos[TAM_VECTOR]; 	// inicializa-se com a estrutura criada acima um vector de produtos
int num_produtos=0; 			// numero de produtos no vector
char ficheiro_produtos[] = "listaprodutos.txt";// nome do ficheiro

int main()
{
    char op;
    do
    {
        printf("\nEscolha uma opcao entre as possiveis:\n");
        printf(" [1]Carregar produtos do ficheiro para a memoria\n");
        printf(" [2]Listar produtos\n");
        printf(" [3]Inserir novo produto\n");
        printf(" [4]Eliminar um produto\n");
        printf(" [5]Gravar produtos para ficheiro\n");
        printf(" [S]Sair\n");
        fflush(stdin);
        scanf("%c", &op);
        switch (op)
        {
        case '1':
            printf("\n\tMenu 1\n");
            carregar_produtos_do_ficheiro();
            printf("Produtos carregados!\n");
            break;
        case '2':
            printf("\n\tMenu 2\n");
            lista_todos_produtos();
            break;
        case '3':
            printf("\n\tMenu 3\n");
            ler_novo_produto(&vec_produtos[num_produtos]);
            num_produtos++; // aumenta o numero de produtos no vector
            break;
        case '4':
            printf("\n\tMenu 4\n");
            eliminar_produto();
            break;
        case '5':
            printf("\n\tMenu 5\n");
            gravar_produtos_para_ficheiro();
            printf("Gravado!\n");;
            break;
        case 's':
        case 'S':
            break;
        default:
            //system("cls"); // clear screen - cls windows or clear for linux/unix
            printf("Opcao invalida!!!\n");
        }

    }
    while (op!='s' && op!='S');

    return 0;
}


void carregar_produtos_do_ficheiro()
{
    FILE *fp;
    int i=0;
    char linha[TAM_NOME];
    fp = fopen("listaprodutos.txt", "r");
    char aux[TAM_NOME];
    num_produtos=0;
    if (fp != NULL)
    {
        fscanf(fp,"%*s %d\n", &num_produtos); 			// ignore the string and store only the int
        for (i=0; i<num_produtos; i++)
        {
            fgets(linha,sizeof(linha),fp); 			// nome
            linha[strlen(linha)-1]=0; 				// retira quebra de linha
            strcpy(vec_produtos[i].nome, &linha[6]); 		// nome começa no 6º char
            fgets(linha,sizeof(linha),fp); 			// preço
            linha[strlen(linha)-1]=0; 				// retira quebra de linha
            strcpy(aux, &linha[10]); 		// caloria começa no 10º char
            vec_produtos[i].calorias = atoi(aux);
            fgets(linha,sizeof(linha),fp); 			// calorias
            linha[strlen(linha)-1]=0; 				// retira quebra de linha
            strcpy(vec_produtos[i].categoria, &linha[11]);     // categoria começa no 11º char
        }
        fclose(fp);
    }
}


void lista_todos_produtos()
{

    int i=0;
    char linha[TAM_NOME];
        for (i=0; i<num_produtos; i++)
        {
            printf("\nnome: %s", vec_produtos[i].nome);
            printf("\ncalorias: %d",vec_produtos[i].calorias);
            printf("\ncategoria: %s\n",vec_produtos[i].categoria);
        }
}


void ler_novo_produto(struct produto *m)
{
    printf("Nome: ");
    fflush(stdin);
    le_inputStr(m->nome);

    printf("Calorias: ");
    fflush(stdin);
    scanf("%d", &m->calorias);

    printf("Categoria: ");
    fflush(stdin);
    le_inputStr(m->categoria);

    getch();

}

void le_inputStr(char *temp) {          //Recebe como argumento a string que vai guardar o que o utilizador escreve.
    char input[TAM_NOME];
    fgets(input,sizeof(input),stdin);

    if(input[strlen(input)-1] == '\n'){
        input[strlen(input)-1] = '\0';
    }
    strcpy(temp,input);

}


void gravar_produtos_para_ficheiro()
{
    FILE * fp;
    int i;
    fp = fopen(ficheiro_produtos, "w");
    if (fp != NULL)
    {
        fprintf(fp,"produtos: %d\n",num_produtos);
        for (i=0; i<num_produtos; i++)
        {
            fprintf(fp,"\nnome: %s\n", vec_produtos[i].nome);
            fprintf(fp,"calorias: %d\n", vec_produtos[i].calorias);
            fprintf(fp,"categoria: %s\n", vec_produtos[i].categoria);

        }
        fprintf(fp, "\n");
        fclose(fp);
    }
}


void eliminar_produto()
{
    int i, j;
    char n[50];
    printf("Introduza o produto a eliminar: ");
    fflush(stdin);
    le_inputStr(n);
    int eliminado=0;
    for(i=0; i<num_produtos; i++)
    {
        if(strcmp(vec_produtos[i].nome,n)==0)
        {
            for(j=i; j<num_produtos; j++)
            {
                strcpy(vec_produtos[j].nome, vec_produtos[j+1].nome);
                vec_produtos[j].calorias = vec_produtos[j+1].calorias;
                strcpy(vec_produtos[j].categoria, vec_produtos[j+1].categoria);
            }
            eliminado=1;
        }
    }

    if (eliminado==1) {
        num_produtos--;
        printf("Produto eliminado com sucesso\n");
    }
    else {
        printf("Produto nao encontrado\n");
    }

}

