<h1 text-align="center">Software de locadora de carros com Estrutura de Dados em C</h1>
![Logo do projeto Loca+](https://user-images.githubusercontent.com/103201399/185994746-af04bb7f-ed01-4c0d-a3d5-64619c84e280.png)

<p>Olá, seja bem vindo ao ReadMe desse repositório, espero que goste!</p>

<p>Meu nome é Guilherme sou estudante de Engenharia de Software da PUC Minas e decidi postar esse projeto de backend criado a partir da linguagem de baixo nível C. O projeto foi realizado em parceria com os alunos Samuel Marques Sousa Leal e Tiago Vitor Pereira Saraiva. Nosso objetivo com esse projeto era desenvolver um sistema de Locadora de carros com um conjunto das seguintes funcionalidades: </p>

<p>
1.Função para cadastrar um cliente. Esta função deve garantir que não
haverá mais de um cliente com o mesmo código. Se quiser pode gerar o código
automaticamente.

2.Função para cadastrar um veículo. Esta função deve garantir que não
haverá mais de um veículo com o mesmo código. Se quiser pode gerar o código
automaticamente.

3.Função que cadastre uma locação. Para cadastrar a locação, o sistema
deve receber do usuário o código do cliente que deseja alugar o veículo, a data de
retirada, a data de devolução do veículo e a quantidade de ocupantes necessários. A partir
disso, o sistema deve encontrar um veículo que esteja disponível para a necessidade do
cliente e calcular a quantidade de diárias com base na data de retirada e devolução. O
cliente também pode contratar um seguro para o veículo alugado, caso queira, o valor do
seguro é de R$ 50 e será acrescido ao valor total pago ao final.

4.Função que dê baixa em uma determinada locação, calcule e mostre o
valor total a ser pago por um determinado cliente. Lembre-se de alterar o status do
veículo para disponível. Além disso, será necessário solicitar a data de entrega do veículo
para validar com a data de devolução prevista. Também será preciso calcular multa por
atraso caso o cliente não entregue o veículo no dia combinado (considere como multa o
valor de 5% do total + R$ 30,00 por dia de atraso).

5.Funções para realizar pesquisa tanto para clientes quanto para veículos, ou
seja, digitando o código apresenta na tela todas as informações do cliente ou veículo.
Deve existir também a possibilidade de listar todos os clientes e todos os veículos.

6.Função que mostre na tela todas as locações de um determinado cliente
(a pesquisa vai se basear no código do cliente).

7.Função que calcula a quantidade de pontos de fidelidade de um cliente.
Para cada dia de locação, o cliente ganhará 10 pontos no programa de fidelidade.
Lembre-se que é possível ter mais de uma locação para um mesmo cliente. Implemente
também uma função para pesquisar os clientes que atingiram um total de 500 pontos no
programa de fidelidade, esses clientes serão premiados e receberam um kit da LocaMais.

8.Função extra, criada pelo grupo. Sejam criativos!</p>

<p>Como esse programa foi feito ?</p>
<p>Para realização das funcionalidades utilizamos algumas das bibliotecas mais comuns da linguagem. Utilizamos também estruturas de dados e manipulação de arquivos como as principais ferramentas.</p>

<p>Como posso testar esse programa ?</p>
<p>Para execução do código recomendo o uso da IDE Code Blocks onde você pode ter acesso as principais funcionalidades necessárias para realização dos testes. Caso tenha vontade de testar alguma funcionalidade basta compilar o código e no próprio cmd digitar os comandos desejados conforme a descrição do código descreve.</p>

<p>Agradeço por ler esse ReadMe e utilizar nosso código =)</p>