/* O reinflador quântico redundante
Você está irritado com toda essa tecnologia para comprimir textos pois acha que os textos ficam
muito apertados e sofrem com isso. Por este motivo você resolveu fazer um reinflador ! Seu reinflador funciona baseado nas letrinhas minúsculas do alfabeto e cada letrinha deve ser transformada
em uma nova sequencia de letrinhas e cada uma destas em mais uma sequencia, e assim por diante
até nada mais poder ser transformado. Desse jeito, uma entrada bem pequena pode se transformar
em algo gigantesco! Um exemplo bem simples está abaixo: ao receber a entrada
a memimomu
e mimomu
i mooo
u mimimi
o // Opcional! Podia não estar aqui!
m // Opcional! Podia não estar aqui!
você já tem a tabela de substituições para cada letrinha. Por exemplo, a letra “i” deve ser sempre
transformada em “mooo” (devido a uma limitação de software as substituições associadas a cada
letrinha tem no máximo 1024 caracteres). Agora você precisa:
1. Determinar a letra inicial que dá origem a todo o arquivo a ser reinflado. Neste exemplo a
letra inicial é “a” mas poderia ser qualquer outra letra. Identificá-la faz parte do problema
(seus amigos da rede social acham que é impossível).
2. Informar quantas letras terá o arquivo final reinflado. Neste exemplo, teremos um arquivo
final com 47 caracteres, que conteria o texto abaixo:
mmmooomommmooommooommooommooomommmooommooommooo
Agora você deve processar várias entradas disponibilizadas na página da disciplina e dizer, para
cada uma delas, qual o tamanho final do arquivo reinflado. Depois disso você deve entregar um
relatório mostrando:
• Uma descrição do problema que foi resolvido;
• Uma descrição da sua solução: ideias, estruturas usadas, pseudo-código dos algoritmos, dificuldades encontradas, testes para confirmar que está tudo ok.
• Os resultados e tempos para os casos de teste fornecidos. Ilustre com figuras, tabelas, etc.
• A análise de complexidade de seu(s) algoritmo(s).
• Por fim, as suas conclusões: o que deu certo, o que deu errado, o porquê, o que poderia ser
feito de forma diferente...
*/

