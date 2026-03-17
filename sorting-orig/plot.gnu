# "Receita de bolo" para fazer gráficos a partir
# de um arquivo de dados com o Gnuplot

# Ajuste conforme a necessidade. Para plotar mais de um
# arquivo de dados, separe por vírgulas
# ex: plot "a.txt" with lines, "b.txt" with lines, ...

# Execute com: gnuplot plot.txt
# Irá gerar o arquivo de saída "saida.pdf"

set term pdf
set output "saida.pdf"
plot "arquivo.txt" with lines
