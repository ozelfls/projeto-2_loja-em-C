#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
  char nome[40];
  int idade;
  char sexo;
  float valorCompraTotal;
  int horario;
  int qtdItens;
};

struct Cliente Cliente[51]; // é uma gambiarra estupida, mas funciona kkkkk

typedef struct Cliente cliente;

// função de cadastro (funciona salvando insta dessa vez)
void cadastrar() { // se lauro reclamar do bgl...
  int qtdVenda = 0;
  FILE *arquivo;
  char continuar2;

  arquivo = fopen("arq.txt", "a");

  do {
    do {
      printf("Escreva quantas vendas voce dejesa fazer: ");
      scanf("%d", &qtdVenda);
      printf("\n");

      if (qtdVenda < 0) {
        printf("O numero digitado não pode ser usado \n");
        printf("\n");
      }

    } while (qtdVenda < 0);

    cliente *clientes = (cliente *)malloc(qtdVenda * sizeof(cliente));
    //alguma coisa nessa linha de cima faz o codigo parar de funcionar do nada quando se digita um numero maior q 10, não sei por que
    if (clientes == NULL) {
      printf("A memoria esta cheia, faça o L¿¿¿¿¿ \n");
      return;
    }

    for (int i = 0; i < qtdVenda; i++) {
      getchar();
      do {
        printf("Digite seu nome: \n");
        fgets(clientes[i].nome, sizeof(clientes[i].nome), stdin);
        clientes[i].nome[strcspn(clientes[i].nome, "\n")] = '\0';
        if (strlen(clientes[i].nome) < 4) {
          printf("Escreva um nome valido (você não é o tenshinhan)\n");
        } // tenshinhan é o Hakaishin mais forte n tem jeito 
      } while (strlen(clientes[i].nome) < 4);

      printf("Escreva seu sexo (m, f, n): ");
      scanf(" %c", &clientes[i].sexo);

      if (clientes[i].sexo != 'm' && clientes[i].sexo != 'f' &&
          clientes[i].sexo != 'n' && clientes[i].sexo != 'M' &&
          clientes[i].sexo != 'F' && clientes[i].sexo != 'N') {
        printf("O Sexo digitado é invalido, agora volta la pra cima kkkk\n");
        i--; // pro for resetar só de raiva
        continue;
      }
      printf("Digite a sua idade:");
      scanf("%i", &clientes[i].idade);

      if (clientes[i].idade <= 0) {
        printf("Quem tem menos de 0 anos de idade?\n");
        i--;
        continue;
      }
// precisaria de ifs em todas de baixo, mas n to afim de fazer...
      printf("Digite a quantidade de itens a ser comprada: ");
      scanf("%d", &clientes[i].qtdItens);

      printf("Digite o valor total da compra: ");
      scanf("%f", &clientes[i].valorCompraTotal);

      printf("Digite o horario da compra(de 0 a 23): ");
      scanf("%d", &clientes[i].horario);

      if (clientes[i].horario > 24 || clientes[i].horario < 0) {
        printf("Tu digitou errado, agora volta pra cima dnv kkkkk\n");
        i--;
        continue;
      }
    }

    if (arquivo == NULL) {
      printf("só o tenshinhan pode abrir o arquivo\n");
    } 
    else {
      for (int i = 0; i < qtdVenda; i++) {
        fprintf(arquivo, "Nome do elemento: %s\n", clientes[i].nome);
        fprintf(arquivo, "Sexo do elemento: %c\n", clientes[i].sexo);
        fprintf(arquivo, "Idade do elemento: %d\n", clientes[i].idade);
        fprintf(arquivo,"Quantidade de itens que o elemento quer comprar: %d\n", clientes[i].qtdItens);
        fprintf(arquivo, "Valor total da compra do elemento: %.2f\n", clientes[i].valorCompraTotal);      
        fprintf(arquivo, "Horário da compra do elemento: %d\n", clientes[i].horario);
      }

      fclose(arquivo);
      printf("Registros salvos em 'arq.txt'.\n");
    }

    free(clientes);
    printf("Dejesa cadastrar mais compras? \n");
    scanf(" %c", &continuar2);
  } while (continuar2 == 's' || continuar2 == 'S');
}

// função de pesquisa vendas especificas (funcionando perfetamente)
void pesquisarVendas() {
  char nomeBusca[40];
  float soma = 0;
  float compraCara = 0;
  int numCompras = 0;
  char continuarPesquisa;
  FILE *arquivo;
  char linhas[100];
  int achouCliente = 0;
  float valorCompra = 0;
  int qtdItens = 0;
  int horario = 0;

  do {
    printf("Digite o nome do elemento que voce quer:\n");
    getchar();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    arquivo = fopen("arq.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo (você não é o Tenshinhan)\n");
      return;
    }

    printf("\n - Compras para o cliente %s \n", nomeBusca);

    // pra limpar as variaveis da pesquisa por elementos dps q rodar(não mexer)
    soma = 0;
    compraCara = 0;
    numCompras = 0;
    achouCliente = 0;

    // strstr retorna o ponteiro pra primeira string dentro de outra string
    // esse strstr aqui vai verificar o string 'nome do elemento', assim ele sabe onde             começa um novo cadastro 

    while (fgets(linhas, sizeof(linhas), arquivo) != NULL) {
      if (strstr(linhas, "Nome do elemento:") != NULL &&
          strstr(linhas, nomeBusca) != NULL) {
        achouCliente = 1;
        numCompras++;

        fgets(linhas, sizeof(linhas), arquivo);
        sscanf(linhas, "Sexo do elemento: %*c");

        fgets(linhas, sizeof(linhas), arquivo);
        sscanf(linhas, "Idade do elemento: %*d");

        fgets(linhas, sizeof(linhas), arquivo);
        sscanf(linhas, "Quantidade de itens que o elemento quer comprar: %d", &qtdItens);

        fgets(linhas, sizeof(linhas), arquivo);
        sscanf(linhas, "Valor total da compra do elemento: %f", &valorCompra);

        fgets(linhas, sizeof(linhas), arquivo);
        sscanf(linhas, "Horario da compra do elemento: %d", &horario);

        printf("Compra %d:\n", numCompras);
        printf("Quantidade de itens do elemento: %d\n", qtdItens);
        printf("Valor total da compra: %.2f\n", valorCompra);
        printf("Horário da compra do elemento: %d\n\n", horario);

        soma += valorCompra;
        if (valorCompra > compraCara) {
          compraCara = valorCompra;
        }
      }
    }

    fclose(arquivo);

    if (achouCliente) {
      printf("Número de compras: %d\n", numCompras);
      printf("Média das compras: %.2f\n", soma / numCompras); //conta direto no print pra economizar linha 
      printf("Maior valor do elemento: %.2f\n", compraCara);
    } 
    else {
      printf("Não foi possível localizar o elemento %s\n", nomeBusca);
    }

    printf("\nDeseja fazer outra busca? (s ou n): ");
    scanf(" %c", &continuarPesquisa);

  } while (continuarPesquisa == 's' || continuarPesquisa == 'S');
}

//função de pesquisar todas as vendas (resolvi um bug linha 283, agora compara certin)
void pesquisarTodas() {
  FILE *arquivo = fopen("arq.txt", "r");
  float somaTotal = 0;
  float compraCara = 0;
  float totalComprasHomens = 0;
  int totalItensVendidos = 0;
  int vendasAcimaValor = 0;
  int vendasCom2Itens = 0;
  int vendasDepoisDoMeioDia = 0;
  int mulheres = 0;
  int numVendas = 0;
  int menorNome1 = -1; // assim funciona kkkkkk
  int maiorIdade1 = -1;
  int menorNomeTamanho = 100;  // se não for um numero bem alto ele não roda nenhum do menor nome (não sei pq)
  int maiorIdade = -1; 
  cliente vendas[100];
  char linha[100];
  char opcao;

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo \n");
    return;
  }

  float valorMinimo;
  printf("Digite o valor, serão exibidas vendas acima desse valor: ");
  scanf("%f", &valorMinimo);

  while (fgets(linha, sizeof(linha), arquivo)) {
    cliente c; // define struct como c pra escrever menos 
    if (strstr(linha, "Nome do elemento:") != NULL) {

      sscanf(linha, "Nome do elemento: %[^\n]", c.nome);
    }
    //sscanf aqui é melhor por que ele ta procurando por um padrão na string linhas que seja o nome do elemento

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Sexo do elemento: %c", &c.sexo);

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Idade do elemento: %d", &c.idade);

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Quantidade de itens que o elemento quer comprar: %d", &c.qtdItens);

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Valor total da compra do elemento: %f", &c.valorCompraTotal);

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Horário da compra do elemento: %d", &c.horario);

    vendas[numVendas] = c;
    numVendas++;

    if (c.valorCompraTotal > valorMinimo) {
      vendasAcimaValor++;
    }

    if (c.qtdItens == 2) {
      vendasCom2Itens++;
    }

    if (c.horario > 12) {
      vendasDepoisDoMeioDia++;
    }

    if (c.sexo == 'f' || c.sexo == 'F') {
      mulheres++;
    }

    if (c.sexo == 'm' || c.sexo == 'M') {
      totalComprasHomens += c.valorCompraTotal;
    }

    totalItensVendidos += c.qtdItens;

    somaTotal += c.valorCompraTotal;

    if (c.valorCompraTotal > compraCara) {
      compraCara = c.valorCompraTotal;
    }

    if (strlen(c.nome) < menorNomeTamanho) {
      menorNomeTamanho = strlen(c.nome);
      menorNome1 = numVendas - 1;
    }

    if (c.idade > maiorIdade) {
      maiorIdade = c.idade;
      maiorIdade1 = numVendas - 1;
    }
  }

  fclose(arquivo);

  printf("\n- Informações de todas as vendas -\n");

  // comentarios para eu não me perder kkkkkkk
  //  Vendas acima do valor especifico
  printf("vendas acima de R$ %.2f: %d\n", valorMinimo, vendasAcimaValor);
         
  // Vendas com itens = 2
  printf("vendas com exatamente 2 itens: %d\n", vendasCom2Itens);

  // Vendas depois de 12 hrs
  printf("vendas realizadas após o meio-dia: %d\n", vendasDepoisDoMeioDia);

  // Quantidade de mulheres compradoras
  printf("compradoras mulheres: %d\n", mulheres);

  // Valor total da compra dos homens
  printf("total comprado por homens: R$ %.2f\n", totalComprasHomens);

  // Quantidade de itens vendidos
  printf("total de itens vendidos: %d\n", totalItensVendidos);

  // Valor total das vendas
  printf("total das compras: R$ %.2f\n", somaTotal);

  // Valor médio de uma venda
  printf("media das compras: R$ %.2f\n", somaTotal / numVendas); //fiz  tipo no js q tu faz a conta dentro do print, e funfou

  // venda mais cara
  printf("Valor da compra mais cara: R$ %.2f\n", compraCara);

  // venda do cliente com menor nome
  printf("\n -- Venda do cliente com o menor nome: -- \n");
  for (int i = 0; i < numVendas; i++) {
    if (i == menorNome1) {
      printf("Nome do elemento: %s\n", vendas[i].nome);
      printf("Quantidade de itens do elemento: %d\n", vendas[i].qtdItens);
      printf("Valor total da compra do elemento: R$ %.2f\n", vendas[i].valorCompraTotal);
      printf("Horário de compra do elemento: %d\n\n", vendas[i].horario);
    }
  }

  // venda do mais velho
  printf("\n -- Venda do cliente mais velho: -- \n");
  for (int i = 0; i < numVendas; i++) {
    if (i == maiorIdade1) {
      printf("Nome do elemento: %s\n", vendas[i].nome);
      printf("Quantidade de itens do elemento: %d\n", vendas[i].qtdItens);
      printf("Valor total da compra do elemento: R$ %.2f\n", vendas[i].valorCompraTotal);
      printf("Horário da compra do elemento: %d\n\n", vendas[i].horario);
    }
  }

  printf("Deseja pesquisar mais vendas? (s ou n): ");
  scanf(" %c", &opcao);

  if (opcao == 's' || opcao == 'S') {
    return;
  } 
} 

int main(void) {

  char continuar;
  int opção = 0;

  do {
    printf("   Loja dos crias 😈😈😈  \n");
    printf("Selecione a opção que voce deseja: \n");
    printf("\n");
    printf("\n");
    printf("1 - cadastrar novas vendas \n");
    printf("2 - informações de uma venda específica \n");
    printf("3 - Ver informações de todas as vendas \n");
    printf("4 - Encerrar o programa \n");
    scanf("%d", &opção);
    printf("\n");
    printf("\n");

    switch (opção) {
    case 1:
      cadastrar(); //facil
      printf("cadastro realizado com sucesso!\n");
      break;

    case 2:
      pesquisarVendas();
      printf("compra verificada sucesso!\n");
      break;

    case 3: 
      pesquisarTodas(); // essa deu trabalho 
      printf("Compra verificada com sucesso!\n");
      break;

    case 4:
      printf("\nprograma encerrado...");
      return 1;
      break;

    default:
      printf("Opção selecionada invalida\n");
    }

    printf("Deseja retornar ao menu?\n");
    scanf(" %c", &continuar);
  } while (continuar == 's' || continuar == 'S');

  return 0;
}


