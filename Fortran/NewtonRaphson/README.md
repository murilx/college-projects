# Método de Newton-Raphson
> Programa criado para a matéria de Cálculo Numérico I

O código implementa na linguagem `Fortran 90` o método de Newton-Raphson (ou simplesmente Método de Newton), um método utilizado em cálculo numérico 
e analise numérica e criado por Isaac Newton e Joseph Raphson para estimar as raízes de uma função. O método pode ser repetido várias vezes utilizando
o resultado encontrado  anteriormente para produzir resultados cada vez mais precisos, ou seja, é um método iterativo. 

## Notação Matemática
Em notação matemática o Método de Newton pode ser escrito pela seguinte sequência recursiva.
<img src="https://latex.codecogs.com/svg.image?x_{n&plus;1}&space;=&space;x_n&space;-&space;\frac{f(x_n)}{f'(x_n)},&space;n&space;\in&space;\mathbb{N}" title="x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}, n \in \mathbb{N}" />

## Funcionamento
O programa funciona de maneira bem simples. Ele é limitado no ponto de não poder receber a função desejada como uma entrada do usuário, ao invés disso é
necessário trocar a função diretamente no código. O usuário então pode entrar com um valor inicial e o valor do erro. A primeira entrada é o ponto de partida,
o ponto inicial que a sequência vai utilizar para começar a calcular a raíz da função e o programa calculará até que o valor do erro absoluto encontrado da
aproximação da raíz seja menor que o erro especificado pelo usuário.
