/**************************************************************************************************
Finalidade do Programa: Cria uma lista encadeada que armazena informações sobre os itens em estoque
de uma empresa. O programa também salva todas essas informações em um arquivo externo, e cada vez
que o programa inicia essas informações são recuperadas para poderem ser manipuladas.
Data da Criação: 21/06/2021
Autor: Murilo Magiolo Geraldini 
****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_ERROR -1
#define MAX_LEN_NAME 50
#define MAX_LEN_DESC 100
#define FILENAME "estoque.dat"

// Structs
typedef struct nodeData {
    int id;                  // Código de identificação do produto
    char name[MAX_LEN_NAME]; // Nome do produto
    char desc[MAX_LEN_DESC]; // Descrição breve do produto
    int price;               // Preço do produto em centavos
    int quantity;            // Quantidade do produto no estoque
} nodeData;

typedef struct node {
    nodeData data;           // Todos os dados de cada item do estoque
    struct node *next;       // Ponteiro para o próximo produto na lista
} node;

// Protótipos
int iinput();
node* init_stock();
void show_stock(node *stock);
node* create_node(nodeData data);
void insert_node(node *stock, node *item);
node* remove_node(node *stock, int id);
void change_node(node *stock, int id);
void release_list(node *stock);
void get_data(node *stock);
void save_data(node *stock);

// Função principal
int main(void) {
    node *stock;            // Lista que representa o estoque da loja
    int opt;

    // Variaveis importantes para inserção e remoção de nós na lista
    int id;
    nodeData data;
    node *tmp = (node *)malloc(sizeof(node));
    node *removed = (node *)malloc(sizeof(node));

    // Inicia a lista e recupera as informações salvas no arquivo
    stock = init_stock();
    get_data(stock);
    
    // Menu
    do {
        save_data(stock);
        printf("\n--- MENU --- \n");
        printf("1. Inserir itens\n");
        printf("2. Remover itens\n");
        printf("3. Modificar atributos\n");
        printf("4. Listar itens \n");
        printf("0. Sair\n");
        printf("> ");
        opt = iinput();

        switch(opt) {
            case 1:  
                // Inserir novos itens no estoque
                printf("ID do produto: ");
                data.id = iinput();
                printf("Nome: ");
                fgets(data.name, MAX_LEN_NAME, stdin);
                printf("Descricao: ");
                fgets(data.desc, MAX_LEN_DESC, stdin);
                printf("Preco (em centavos): ");
                data.price = iinput();
                printf("Quantidade: ");
                data.quantity = iinput();

                tmp = create_node(data);
                insert_node(stock, tmp);
                
                // "Limpa" o conteudo de tmp para não haver conflito com free()
                tmp = NULL;

                break;

            case 2:
                // Retirar itens do estoque
                printf("ID do produto: ");
                id = iinput();
                removed = remove_node(stock, id);

                // "Limpa" o conteudo de removed para não haver conflito com free()
                removed = NULL;
                
                break;

            case 3:
                // Modifica atributos dos itens no estoque
                printf("ID do produto: ");
                id = iinput();
                change_node(stock, id);               

                break;

            case 4:
                // Mostra os itens do estoque
                show_stock(stock);
                break;

            case 0:
                // Encerra o programa
                printf("Saindo...\n");
                break;

            default:
                // Mensagem de erro caso um código invalido seja inserido
                printf("ERRO: Entrada invalida.\n");
                break;
        }
    } while(opt != 0);

    // Salva antes de sair 
    save_data(stock);

    // Libera todos os nós criados durante o programa
    free(tmp);
    free(removed);
    release_list(stock);
}

// Implementação das funções
int iinput() {
    // Função responsável por pegar apenas um número inteiro da entrada padrão
    // e descartar o resto (como letras, por exemplo). Apresenta um erro caso
    // o valor entrado seja invalido
    char buf[100];
    char *end;
    int num;

    while(fgets(buf, sizeof(buf), stdin)) {
        num = strtol(buf, &end, 10);

        if(end == buf || *end != '\n') {
            printf("ERRO: Valor invalido inserido! ");
            printf("Por favor entre com um inteiro\n");
            printf("> ");
        } else break;
    }

    return num;

}

node* init_stock() {
    // Aloca espaço na memória e inicia os valores necessários para a lista
    node *stock = (node *)malloc(sizeof(node));

    // Verifica se a lista foi criada corretamente
    if(!stock) {
        printf("ERRO: Impossivel iniciar a lista\n");
        exit(EXIT_ERROR);
    }

    stock->next = NULL;
    return stock;
}

void show_stock(node *stock) {
    // Lista todos os itens do estoque
    node *i = stock->next;

    // Verifica se o estoque está vazio
    if(i == NULL) {
        printf("Estoque vazio!");
        return;
    }

    // Se o estoque não estiver vazio, mostra os itens
    printf("\nITENS NO ESTOQUE:\n");
    while(i != NULL) {
        printf("ID: %d\n", i->data.id);
        printf("Nome: %s", i->data.name);
        printf("Descricao: %s", i->data.desc);
        printf("Preco: %.2lf\n", (double)i->data.price/100);
        printf("Quantidade: %d\n\n", i->data.quantity);
        i = i->next;
    }
}

node* create_node(nodeData data) {
    // Cria um novo item para o estoque
    node *item = (node *)malloc(sizeof(node));

    // Verifica se o nó foi criado corretamente
    if(!item) {
        printf("ERRO: Impossivel criar novo item.\n");
        return NULL;
    }

    // Verifica os dados para ver se são validos
    if(data.id <= 0) {
        printf("ERRO: Codigo ID nao pode ser menor ou igual a zero.\n");
        return NULL;
    }

    if(strcmp(data.name, "") == 0 || strcmp(data.name, " ") == 0 || strcmp(data.name, "\n") == 0) {
        printf("ERRO: Nome invalido.\n");
        return NULL;
    }

    if(strcmp(data.desc, "") == 0 || strcmp(data.desc, " ") == 0 || strcmp(data.desc, "\n") == 0) {
        printf("ERRO: Descricao invalida.\n");
        return NULL;
    }

    if(data.price < 0) {
        printf("ERRO: Preco nao pode ser negativo.\n");
        return NULL;
    }

    if(data.quantity < 0) {
        printf("ERRO: Quantidade nao pode ser negativa.\n");
        return NULL;
    }

    // Determina os valores dos elementos do novo nó
    item->data.id = data.id;
    strcpy(item->data.name, data.name);
    strcpy(item->data.desc, data.desc);
    item->data.price = data.price;
    item->data.quantity = data.quantity;
    item->next = NULL;

    return item;
}

void insert_node(node *stock, node *item) {
    // Insere um novo item na lista. Caso o item inserido
    // já existir na lista, então só é adicionado x na quantidade
    // do item já presente (campo quantity), caso não exista o 
    // item na lista, ele será adicionado no fim da lista
    node *i = stock;

    // Verifica se o item é valido
    if(item == NULL) {
        printf("ERRO: Impossivel inserir o item\n");
        return;
    }

    // Verifica se a lista é nula
    if(i->next == NULL) stock->next = item;
    else {
        // Passa pela lista toda
        while(i->next != NULL) {
            // Caso o usuário tente inserir um item que já está no estoque
            // o programa apenas soma a quantidade do item que já existe com a
            // quantidade do que seria adicionado
            if(i->next->data.id == item->data.id) 
                if(strcmp(i->next->data.name, item->data.name) == 0) 
                    if(strcmp(i->next->data.desc, item->data.desc) == 0) 
                        if(i->next->data.price == item->data.price) {
                            (i->next->data.quantity) += (item->data.quantity);
                            return;
                        } 

            
            // Verifica se o novo item tem o id de um item do estoque
            if(i->next->data.id == item->data.id) {
                printf("ERRO: Item com o mesmo ID identificado\n");
                return;
            }

            // Verifica se o novo item tem o nome de um item do estoque
            if(strcmp(i->next->data.name, item->data.name) == 0) {
                printf("ERRO: Item com mesmo nome identificado\n");
                return;
            }

            i = i->next;
        }
        
        // Insere o item no fim da lista
        i->next = item;
    }
}

node* remove_node(node *stock, int id) {
    // Remove um nó baseado no ID do item
    node *i = stock->next;
    node *last = stock;

    // Passa por todos os elementos da lista
    while(i != NULL) {
        // Verifica o ID do produto com o ID inserido
        // e se for faz a remoção
        if(i->data.id == id) { 
            last->next = i->next;
            return i;
        }

        last = i;
        i = i->next;
    }

    // Se não existir produto com o ID inserido mostra essa mensagem
    printf("ERRO: Codigo invalido inserido\n");
    return NULL;
}

void change_node(node *stock, int id) {
    // Muda atributos de um item no stock
    // Alguns atributos não podem ser modificados (id; name)
    node *i = stock->next;
    int opt, price, quantity, aux;

    // Menu para escolher o atributo que será alterado
    printf("Atributo para modificar:\n");
    printf("1. Preco\n");
    printf("2. Quantidade\n");
    printf("Aperte outra tecla para sair\n");
    printf("> ");
    opt = iinput();

    switch(opt) {
        case 1:
            aux = 1;
            printf("Novo preco: ");
            price = iinput();

            if(price < 0) {
                printf("ERRO: Preco nao pode ser negativo.\n");
                return;
            }

            break;

        case 2:
            aux = 2;
            printf("Quantidade: ");
            quantity = iinput();

            if(quantity < 0) {
                printf("ERRO: Quantidade nao pode ser negativa.\n");
                return;
            }

            break;

        default: return;
    }
    
    // Passa por todos os elementos da lista
    while(i != NULL) {
        // Verifica o ID do produto com o ID inserido
        if(i->data.id == id) {
            if(aux == 1) i->data.price = price;
            if(aux == 2) i->data.quantity = quantity;
            return;
        }

        i = i->next;
    }

    // Se não existir produto com o ID inserido mostra essa mensagem
    printf("ERRO: Codigo invalido inserido\n");
}

void release_list(node *stock) {
    // Libera todos os nós criados e armazenados na lista
    if(stock->next != NULL) {
        node *nextItem, *item;

        item = stock->next;
        while(item != NULL) {
            nextItem = item->next;
            free(item);
            item = nextItem;
        }
    }
}

void get_data(node *stock) {
    // Função que pega os dados salvos no arquivo e os armazenam na lista
    // para que o programa possa fazer a manipulação apropriada
    FILE *fp;
    nodeData item;
    
    // Tenta abrir o arquivo binário para leitura
    if((fp = fopen(FILENAME, "rb")) == NULL) {
        printf("ERRO: Impossivel abrir o arquivo.\n");
        exit(EXIT_ERROR);
    }

    while(fread(&item, sizeof(item), 1, fp)) {
        node *tmp = create_node(item);
        insert_node(stock, tmp);
    }

    fclose(fp);
}

void save_data(node *stock) {
    // Função que pega todos os dados que estão na lista e armazena esses dados
    // num arquivo
    FILE *fp;
    node *i = stock->next;

    // Tenta abrir o arquivo binário para escrita
    if((fp = fopen(FILENAME, "wb")) == NULL) {
        printf("ERRO: Impossivel abrir o arquivo.\n");
        exit(EXIT_ERROR);
    }
    
    // Verifica se a lista esta vazia
    if(i == NULL) return;

    // Percorre pela lista e salva os elementos no arquivo
    while(i != NULL) {
        nodeData tmp = i->data;
        fwrite(&tmp, sizeof(tmp), 1, fp);
        i = i->next;
    }

    fclose(fp);
}
