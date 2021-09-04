# PS-01
> Programa criado para a matéria de Estrutura de Dados I.
  
A ideia principal do trabalho era estudar os conceitos já abordados em sala de pilhas e/ou listas encadeadas. Para isso o aluno tinha a liberdade de desenvolver
um programa qualquer que utilizasse pelo menos uma dessas estruturas de dados. 
  
## Funcionamento
O projeto em si busca desenvolver um programa para gerenciamento de estoque de uma empresa ficticia e de maneira simples, uma vez que o ponto principal do projeto
era a implementação de listas encadeadas. Outro ponto também abordado no código foi a integração de listas encadeadas com um sistema de arquivos.
  
Basicamente, as informações sobre o estoque da empresa ficam armazenadas dentro de uma lista encadeada, permitindo uma manipulação mais fácil dos dados desse
estoque enquanto o programa está em execução. Antes de fecha-lo, o programa salva todas as informações que estão na lista encadeada dentro de um arquivo binário
`estoque.dat`. Esse mesmo arquivo é lido toda vez que o programa é executado para recuperar as informações do estoque armazeado nele. 
