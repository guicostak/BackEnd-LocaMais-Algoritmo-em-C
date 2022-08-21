#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

FILE *arquivoClientes;
FILE *arquivoVeiculos;
FILE *arquivoLocacao;

struct Tendereco
{
    int numero;
    char rua[30];
    char cidade[20];
    char estado[20];
    int cep;
};

typedef struct Tendereco endereco;

struct Tcliente
{
    int pontosCliente;
    int codigoCliente;
    char nome[50];
    int telefone;
    endereco endereco;
    int notaUsuario;
};
typedef struct Tcliente cliente;

struct Tlocacao
{
    float multa;
    int codigo;
    int dataRetirada;
    int dataDevolucao;
    int dataDevolucaoC;
    int qtdDias;
    int seguro;
    int codigoCliente;
    int codigoVeiculo;
    int qtdLugares;
    float valorFinal;
};
typedef struct Tlocacao locacao;

struct Tveiculo
{
    int codigoVeiculo;
    char descricao[100];
    char modelo[20];
    char cor[10];
    char placa[7];
    float valorDiaria;
    int qtdOcupantes;
    int status;
};

typedef struct Tveiculo veiculo;

void inicializaArquivos()
{ // function para inicializar todos os arquivos de registro
    if ((arquivoClientes = fopen("arquivoClientes.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de clientes...\n");
        if ((arquivoClientes = fopen("arquivoClientes.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de clientes!!\n");
            exit(1);
        }
    }

    if ((arquivoVeiculos = fopen("arquivoVeiculos.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de veiculos...\n");
        if ((arquivoVeiculos = fopen("arquivoVeiculos.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de veículos!!\n");
            exit(1);
        }
    }

    if ((arquivoLocacao = fopen("arquivoLocacao.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de veiculos...\n");
        if ((arquivoLocacao = fopen("arquivoLocacao.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de veículos!!\n");
            exit(1);
        }
    }

    return;
}

int localizaCliente(FILE *f, int codigo)
{
    int posicao = -1,
        achou = 0;
    cliente c;
    fseek(f, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, f);
    while (!feof(f) && !achou)
    {
        posicao++; // semelhante a  posicao = posicao +1;
        if (c.codigoCliente == codigo)
        {
            achou = 1;
        }
        fread(&c, sizeof(c), 1, f);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

int localizaVeiculo(FILE *f, int codigo, int qnt)
{
    int posicao = -1,
        achou = 0;
    veiculo v;
    fseek(f, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, f);
    while (!feof(f) && !achou)
    {
        posicao++; // semelhante a  posicao = posicao +1;
        if (v.codigoVeiculo == codigo || ((v.qtdOcupantes == qnt && v.status == 0) || qnt == -1))
        {
            achou = 1;
        }
        fread(&v, sizeof(v), 1, f);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

int localizaLocacao(FILE *arquivoLocacao, int codigo)
{
    int posicao = -1, achou = 0;
    locacao l;
    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&l, sizeof(l), 1, arquivoLocacao);
    while (!feof(arquivoLocacao) && !achou)
    {
        posicao++;
        if (l.codigo == codigo)
        {
            achou = 1;
        }
        fread(&l, sizeof(l), 1, arquivoLocacao);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastraVeiculo(FILE *f)
{
    veiculo v;
    int posicao;
    // lendo os dados do teclado
    printf("Digite o c�digo do veiculo: ");
    fflush(stdin);
    scanf("%d", &v.codigoVeiculo);
    posicao = localizaVeiculo(f, v.codigoVeiculo, "---");
    if (posicao == -1) // n�o tinha codigo no arquivo
    {
        printf("Digite a cor: ");
        fflush(stdin);
        gets(v.cor);
        printf("Digite o modelo: ");
        fflush(stdin);
        scanf("%s", &v.placa);
        printf("Digite a descricao: ");
        fflush(stdin);
        scanf("%s", &v.descricao);
        printf("Digite a capacidade: ");
        fflush(stdin);
        scanf("%i", &v.qtdOcupantes);
        printf("Digite o valor da diaria: ");
        fflush(stdin);
        scanf("%f", &v.valorDiaria);
        v.status = 1;

        fseek(f, 0, SEEK_END);       // posicionado o arquivo no final
        fwrite(&v, sizeof(v), 1, f); // gravando os dados
        fflush(f);
    }
    else
    {
        printf("Codigo %d ja existe no arquivo. Inclusao nao realizada!\n", v.codigoVeiculo);
    }
}

void cadastraEndereco(endereco *ender)
{
    endereco e;

    printf("Digite o Estado: ");
    fflush(stdin);
    gets(e.estado);

    printf("Digite a Cidade: ");
    fflush(stdin);
    gets(e.cidade);

    printf("Digite a rua: ");
    fflush(stdin);
    gets(e.estado);

    printf("Digite o numero: ");
    fflush(stdin);
    scanf("%i", &e.numero);

    printf("Digite o CEP: ");
    fflush(stdin);
    scanf("%i", &e.cep);

    *ender = e;
}

void cadastraCliente(FILE *arquivoClientes)
{
    cliente c;
    int posicao;
    // lendo os dados do teclado
    printf("Digite o c�digo do cliente: ");
    fflush(stdin);
    scanf("%d", &c.codigoCliente);
    posicao = localizaCliente(arquivoClientes, c.codigoCliente);
    if (posicao == -1) // n�o tinha codigo no arquivo
    {
        printf("Digite o nome do cliente: ");
        fflush(stdin);
        gets(c.nome);
        printf("Digite o telefone: ");
        fflush(stdin);
        scanf("%i", &c.telefone);

        cadastraEndereco(&c.endereco);

        fseek(arquivoClientes, 0, SEEK_END);       // posicionado o arquivo no final
        fwrite(&c, sizeof(c), 1, arquivoClientes); // gravando os dados
        fflush(arquivoClientes);
    }
    else
    {
        printf("Codigo %d ja existe no arquivo. Inclusao nao realizada!\n", c.codigoCliente);
    }
}

void cadastraLocacao(FILE *arquivoLocacao, FILE *arquivoClientess, FILE *arquivoVeiculos)
{
    int posicaoL, posicao, posicao2, qtdLugares, codigo;

    cliente c;
    veiculo v;
    locacao l;

    printf("\nDigite o código da locação:   ");
    scanf("%d", &codigo);

    posicaoL = localizaLocacao(arquivoLocacao, codigo);
    if (posicaoL == -1)
    {

        // lendo os dados do teclado
        printf("\nDigite o código do cliente: ");
        fflush(stdin);
        scanf("%d", &l.codigoCliente);

        posicao = localizaCliente(arquivoClientes, c.codigoCliente);
        if (posicao == -1) // n�o tinha codigo no arquivo
        {
            fseek(arquivoClientes, sizeof(c) * posicao, SEEK_SET);
            fread(&c, sizeof(c), 1, arquivoClientess);
            fflush(stdin);

            l.codigoCliente = c.codigoCliente;

            printf("\nDigite o dia de retirada: ");
            scanf("%i", &l.dataRetirada);

            printf("\nDigite o dia de devolução: ");
            scanf("%i", &l.dataDevolucao);

            printf("\nQual a quantidade de ocupantes: ");
            scanf("%i", &qtdLugares);

            l.qtdDias = l.dataDevolucao - l.dataRetirada;

            posicao2 = localizaVeiculo(arquivoVeiculos, -1, qtdLugares);
            if (posicao2 != -1)
            {
                fseek(arquivoVeiculos, sizeof(v) * posicao2, SEEK_SET);
                fread(&v, sizeof(v), 1, arquivoVeiculos);
                fflush(stdin);

                l.codigoVeiculo = v.codigoVeiculo;
                v.status = 1;

                printf("Deseja contratar seguro? : ");
                printf("Se sim digite 1, se não digite 0 : ");
                fflush(stdin);
                scanf("%d", &l.seguro);

                if (l.seguro == 1)
                {
                    l.valorFinal = l.qtdDias * v.valorDiaria + 50;
                }
                else
                {
                    l.valorFinal = l.qtdDias * v.valorDiaria;
                }

                fseek(arquivoVeiculos, sizeof(v) * posicao2, SEEK_SET);
                fwrite(&v, sizeof(v), 1, arquivoVeiculos);
                fflush(arquivoVeiculos);

                fseek(arquivoLocacao, sizeof(l) * posicaoL, SEEK_SET);
                fwrite(&l, sizeof(l), 1, arquivoLocacao);
                fflush(arquivoLocacao);
                printf("\nLocação cadastrada com sucesso!");
            }
        }
        else
        {
            printf("Cliente não encontrado! \n");
        }
    }
    else
    {
        printf("Já existe uma locação com esse código. Inclusão não realizada!\n");
    }
}

void baixaLocacao(FILE *arquivoLocacao, FILE *arquivoClientess, FILE *arquivoVeiculos)
{
    int posicaoL, posicao, posicao2, codigo, diaDevolucao;

    cliente c;
    veiculo v;
    locacao l;

    printf("\nDigite o código da locação:   ");
    scanf("%d", &codigo);

    posicaoL = localizaLocacao(arquivoLocacao, codigo);
    if (posicaoL == -1)
    {
        fseek(arquivoLocacao, sizeof(l) * posicaoL, SEEK_SET);
        fread(&l, sizeof(l), 1, arquivoClientess);
        fflush(stdin);

        printf("\nDigite o dia da devolução: ");
        scanf("%i", &diaDevolucao);

        if (diaDevolucao == l.dataDevolucao)
        {
            l.valorFinal;
        }
        else
        {
            l.valorFinal += 0.05 * l.valorFinal;
            l.valorFinal += (diaDevolucao - l.dataDevolucao) * 30;
        }

        posicao = localizaVeiculo(arquivoVeiculos, l.codigoVeiculo, 0);

        if (posicao != -1)
        {

            // Faz alterações nos arquivos
            fseek(arquivoVeiculos, sizeof(v) * (posicao), SEEK_SET);
            fread(&v, sizeof(v), 1, arquivoVeiculos);

            fflush(stdin);
            v.status = 0;

            fseek(arquivoVeiculos, sizeof(v) * posicao, SEEK_SET);
            fwrite(&v, sizeof(v), 1, arquivoVeiculos);
            fflush(arquivoVeiculos);

            fseek(arquivoLocacao, sizeof(l) * posicaoL, SEEK_SET);
            fwrite(&l, sizeof(l), 1, arquivoLocacao);
            fflush(arquivoLocacao);

            printf("Valor total das diarias.:%.2f\n", l.valorFinal);

            // Impressão de qual cliente deverá arcar com o valor
            posicao2 = localizaCliente(arquivoClientes, l.codigoCliente);
            if (posicao2 != -1)
            {
                fseek(arquivoClientes, sizeof(c) * (posicao2), SEEK_SET);
                fread(&c, sizeof(c), 1, arquivoClientes);
                printf("\nCodigo do cliente  :%d\n", c.codigoCliente);
                printf("Nome do cliente  :%s\n", c.nome);
            }
            printf("\nBaixa realizada com sucesso!");
        }
        else
        {
            printf("Veículo não encontrado! \n");
        }
    }
    else
    {
        printf("Já existe uma locação com esse código. Inclusão não realizada!\n");
    }
}

void localizaDados(FILE *arquivoClientes, FILE *arquivoVeiculos)
{
    printf("\n--------Localização de dados--------\n");
    printf("Digite: \n1 - Localizar cliente\n");
    printf("2 - Localizar veículo\n");
    printf("Digite: ");
    int opt;
    scanf("%i", &opt);
    switch (opt)
    {
    case 1:
        printf("Insira o código: ");
        int codigo;
        scanf("%i", &codigo);
        int posicao = localizaCliente(arquivoClientes, codigo);
        if (posicao != -1)
        {
            cliente c;
            fseek(arquivoClientes, sizeof(c) * posicao, SEEK_SET);
            fread(&c, sizeof(c), 1, arquivoClientes);
            fflush(stdin);

            printf("\n\nCodigo: %i\n", c.codigoCliente);
            printf("Nome: %s\n", c.nome);
            printf("Telefone:(%i)\n", c.telefone);
            printf("Endereco: %i, %s, %s, %s,\n", c.endereco.numero, c.endereco.rua, c.endereco.cidade, c.endereco.estado);
        }
        else
        {
            printf("\nCliente não encontrado!\n");
        }
        break;
    case 2:
        printf("Insira o código: ");
        int codigoVeiculo = 0;
        scanf("%i", &codigoVeiculo);
        int posicaoV = localizaVeiculo(arquivoVeiculos, codigoVeiculo, 0);
        if (posicaoV != -1)
        {
            veiculo v;
            fseek(arquivoVeiculos, sizeof(v) * posicaoV, SEEK_SET);
            fread(&v, sizeof(v), 1, arquivoVeiculos);
            fflush(stdin);

            printf("\n\nCodigo:             %i\n", v.codigoVeiculo);
            printf("qnt passageiros:    %i\n", v.qtdOcupantes);
            printf("Status:             %i\n", v.status);
            printf("Descricao:          %s\n", v.descricao);
            printf("Modelo:             %s\n", v.modelo);
            printf("Cor:                %s\n", v.cor);
            printf("Placa:              %s\n", v.placa);
            printf("Valor diária:       %f\n", v.valorDiaria);
        }
        else
        {
            printf("\nVeículo não encontrado!\n");
        }
        break;
    default:
        printf("\nOpção inválida!\n");
    }
}

void buscaLocacoesCliente(FILE *arquivoClientes, FILE *arquivoLocacao)
{
    cliente c;
    locacao l;
    int codigoCliente;
    int posicaoCliente;

    printf("Digite o código do cliente:");
    fflush(stdin);
    scanf("%i", &codigoCliente);

    posicaoCliente = localizaCliente(arquivoClientes, codigoCliente);

    fseek(arquivoClientes, sizeof(c) * (posicaoCliente), SEEK_SET);
    fread(&c, sizeof(c), 1, arquivoClientes);

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&l, sizeof(l), 1, arquivoLocacao);

    printf("Locações de %s:", c.nome);
    while (!feof(arquivoLocacao))
    {
        if (l.codigoCliente == c.codigoCliente)
        {

            printf("\n\nCódigo:                 %d \n", l.codigo);
            printf("Data da Retirada:           %d \n", l.dataRetirada);
            printf("Data da Devolução:          %d\n", l.dataDevolucao);
            printf("Data da Entrega:            %d\n", l.dataDevolucaoC);
            printf("Dias de Aluguel:            %d\n", l.qtdDias);
            printf("Seguro?                    %d\n", l.seguro);
            printf("Código do Cliente:          %d\n", l.codigoCliente);
            printf("Código do Veículo:          %d\n", l.codigoVeiculo);
        }
        fread(&l, sizeof(l), 1, arquivoLocacao);
    }
}

void calculaPonto(FILE *arquivoClientes, FILE *arquivoLocacao)
{
    cliente c;
    locacao l;
    int codigoCliente, posicaoCliente, pontos, dias;

    printf("\nDigite o código do cliente:");
    fflush(stdin);
    scanf("%i", &codigoCliente);

    posicaoCliente = localizaCliente(arquivoClientes, codigoCliente);

    fseek(arquivoClientes, sizeof(c) * (posicaoCliente), SEEK_SET);
    fread(&c, sizeof(c), 1, arquivoClientes);

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&l, sizeof(l), 1, arquivoLocacao);

    while (!feof(arquivoLocacao))
    {
        if (l.codigoCliente == c.codigoCliente)
        {
            dias = (l.dataRetirada - l.dataDevolucao);
            pontos += dias * 10;
        }
        fread(&l, sizeof(l), 1, arquivoLocacao);
    }
    printf("O total de pontos de %s é:%d", c.nome, pontos);
}

void clienteKit(FILE *arquivoClientes, FILE *arquivoLocacao)
{
    cliente c;
    locacao l;
    int pontos = 0;
    fseek(arquivoClientes, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, arquivoClientes);

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&l, sizeof(l), 1, arquivoLocacao);
    printf("Clientes que receberam kit: ");
    while (!feof(arquivoClientes))
    {
        while (!feof(arquivoLocacao))
        {
            if (l.codigoCliente == c.codigoCliente)
            {
                int dias = (l.dataRetirada - l.dataDevolucao);
                pontos += dias * 10;
            }

            fread(&l, sizeof(l), 1, arquivoLocacao);
        }
        if (pontos >= 500)
        {
            printf("\nO cliente %s tem %d pontos e pode retirar um kit da LocaMais", c.nome, pontos);
        }
        pontos = 0;
        fread(&c, sizeof(c), 1, arquivoClientes);
    }
}

void avaliarCliente(FILE *arquivoClientes)
{
    cliente c;
    int posicao;
    // lendo os dados do teclado
    printf("Digite o c�digo do cliente: ");
    fflush(stdin);
    scanf("%d", &c.codigoCliente);
    posicao = localizaCliente(arquivoClientes, c.codigoCliente);
    if (posicao == -1) // n�o tinha codigo no arquivo
    {
        printf("Cliente nao encontrado!!!");
    }
    else
    {
        printf("Digite uma nota para o cliente %i:\n", c.codigoCliente);
        scanf("%i", &c.notaUsuario);

        fseek(arquivoClientes, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, arquivoClientes);
        fflush(arquivoClientes);
    }
}

int main()
{
    int opcao;

    inicializaArquivos(arquivoClientes, arquivoVeiculos, arquivoLocacao);

    printf("Seja BEM-VINDO a LocaMais!!!");
    printf("\n Se deseja se cadastrar digite 1.");
    printf("\n Para cadastrar um veiculo digite 2.");
    printf("\n Para alugar um veiculo digite 3.");
    printf("\n Para dar baixa em um veiculo digite 4.");
    printf("\n Para localizar uma entidade digite 5.");
    printf("\n Para localizar as locacoes de um cliente, digite 6.");
    printf("\n Para ver os clientes que possuem kit, digite 7.");
    printf("\n Para avaliar um cliente, digite 8.");
    printf("\n Insira:");

    scanf("%i", &opcao);

    switch (opcao)
    {
    case 1:
        cadastraCliente(arquivoClientes);
        break;
    case 2:
        cadastraVeiculo(arquivoVeiculos);
        break;
    case 3:
        cadastraLocacao(arquivoLocacao, arquivoClientes, arquivoVeiculos);
        break;
    case 4:
        baixaLocacao(arquivoLocacao, arquivoClientes, arquivoVeiculos);
        break;
    case 5:
        localizaDados(arquivoLocacao, arquivoClientes);
        break;
    case 6:
        buscaLocacoesCliente(arquivoLocacao, arquivoClientes);
        break;
    case 7:
        clienteKit(arquivoLocacao, arquivoClientes);
        break;
    case 8:
        avaliarCliente(arquivoClientes);
        break;
    default:
        printf("Numero Inválido!!!");
        break;
    }
    return 0;
}