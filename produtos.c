#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>


struct Produto {
    int id;
    char nome[76];
    float preco;
};
void produtos() {
    setlocale(LC_ALL, "Portuguese");
    char saidaprod = 'n';
    do {
        system("cls");
        system("clear");
        printf("\nBem-vindo ao menu de gerenciamento de produtos! Escolha o que deseja fazer: ");
        printf("\n(C) Cadastrar Produto");
        printf("\n(L) Listar produtos");
        printf("\n(E) Editar produto");
        printf("\n(X) Excluir produto");
        printf("\n(S) Sair");
        printf("\nSua opção: ");
        char opcaoprod;
        scanf(" %c", &opcaoprod);
        opcaoprod = toupper(opcaoprod);
        switch(opcaoprod) {
            case 'C': {
                FILE *produtos = fopen("produtos.txt", "a+");
                struct Produto produto;
                int erroid = 0;
                do {
                    printf("\nDigite um ID para o produto (anote-o em algum lugar): ");
                    erroid = scanf("%d", &produto.id);
                    if (erroid != 1) printf("\nErro! Digite um ID numérico adequado");
                } while (erroid != 1);
                int erronome = 0;
                do {
                    printf("\nDigite o nome do produto: ");
                    scanf(" %75[^\n]", produto.nome);
                    if (strlen(produto.nome) > 76) {
                        printf("\nErro, digite novamente o nome do produto!");
                    } else {
                        erronome = 1;
                    }
                } while (erronome != 1);
                int erropreco = 0;
                do {
                    printf("\nDigite o preço do produto: ");
                    erropreco = scanf("%f", &produto.preco);
                    if (erropreco != 1) printf("\nErro! Digite o preço do produto em reais novamente!");
                } while (erropreco != 1);
                fprintf(produtos, "%d|%s|%.2f\n", produto.id, produto.nome, produto.preco);
                fclose(produtos);
                printf("\nProduto cadastrado com sucesso!");
                break;
            }
            case 'L': {
                FILE *produtos = fopen("produtos.txt", "a+");
                struct Produto produto;
                printf("\nLista de produtos");
                while (fscanf(produtos, "%d|%75[^|]|%f\n", &produto.id, produto.nome, &produto.preco) != EOF) {
                    printf("ID: %d, nome: %s, preço: %.2f\n", produto.id, produto.nome, produto.preco);
                }
                system("pause");
                fclose(produtos);
                break;
            }
            case 'E': {
                FILE *produtos = fopen("produtos.txt", "a+");

                int idAlvo;
                printf("\nDigite o ID do produto a ser editado: ");
                scanf("%d", &idAlvo);
                
                struct Produto produto;
                int encontrado = 0;
                FILE *temp = fopen("temp.txt", "w");
                while (fscanf(produtos, "%d|%75[^|]|%f\n", &produto.id, produto.nome, &produto.preco) != EOF) {
                    if (produto.id == idAlvo) {
                        int erronome = 0;
                        do {
                            printf("\nDigite o novo nome do produto (ou pressione Enter para não alterar): ");
                            char novoNome[76];
                            erronome = scanf( " %75[^\n]", novoNome);
                            if (strlen(novoNome) > 0) strcpy(produto.nome, novoNome);
                            if (erronome != 1) printf("\nErro ao registrar novo nome! tente novamente!");
                        } while (erronome != 1);
                        int erropreco = 0;
                        do {
                            printf("\nDigite o novo preço do produto (ou pressione Enter para não alterar): ");
                            float novoPreco;
                            erropreco = scanf("%f", &novoPreco);
                            if (novoPreco > 0) produto.preco = novoPreco;
                            if (erropreco != 1) printf("\nErro ao regsitrar novo preço! Digite novamente o preço em reais");
                        } while (erropreco != 1);
                        encontrado = 1;
                    }
                    fprintf(temp, "%d|%s|%.2f\n", produto.id, produto.nome, produto.preco);
                }
                fclose(temp);
                fclose(produtos);
                remove("produtos.txt");
                rename("temp.txt", "produtos.txt");
                if (encontrado) {
                    printf("\nProduto editado com sucesso!");
                } else {
                    printf("\nProduto não encontrado.");
                }
                break;
            }
            case 'X': {
                FILE *produtos = fopen("produtos.txt", "r");
                int idAlvo;
                printf("\nInforme o ID do produto a ser excluído:");
                scanf("%d", &idAlvo);
                struct Produto produto;
                int encontrado = 0;
                FILE *temp = fopen("temp.txt", "w");
                while (fscanf(produtos, "%d|%75[^|]|%f\n", &produto.id, produto.nome, &produto.preco) != EOF) {
                    if (produto.id == idAlvo) {
                        printf("\nDeseja mesmo exlcluir o produto %s? (S/N): ", produto.nome);
                        char confirmacao;
                        scanf(" %c", &confirmacao);
                        if (toupper(confirmacao) == 'S') {
                            encontrado = 2;
                        } else {
                            encontrado = 1;
                        }
                    } else {
                        fprintf(temp, "%d|%s|%.2f\n", produto.id, produto.nome, produto.preco);
                    }
                }
                fclose(temp);
                fclose(produtos);
                if (encontrado == 2) {
                    remove("produtos.txt");
                    rename("temp.txt", "produtos.txt");
                    printf("\nProduto excluído com sucesso!");
                } else if (encontrado == 1) {
                    printf("\nProduto não excluído.");
                } else {
                    printf("\nProduto não encontrado.");
                }
                break;
            }
            case 'S':
                saidaprod = 'S';
                break;
            default:
                printf("\nOpção inválida, tente novamente.");

        }
    } while (toupper(saidaprod) != 'S');
}