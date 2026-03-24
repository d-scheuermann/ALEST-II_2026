# "Receita de bolo" para fazer gráficos a partir
# de um arquivo de dados com o Gnuplot

# Ajuste conforme a necessidade. Para plotar mais de um
# arquivo de dados, separe por vírgulas
# ex: plot "a.txt" with lines, "b.txt" with lines, ...

# Execute com: gnuplot plot.gnu
# Irá gerar o arquivo de saída "saida.pdf"

set term pdf
set output "saida.pdf"
#plot "bubble_java.csv" with lines
#plot "bubble_c.csv" with lines
#plot "bubble_python.csv" with lines
#plot "quick_java.csv" with lines, "merge_java.csv" with lines
plot "quick_c.csv" with lines, "merge_c.csv" with lines
#plot "quick_python.csv" with lines, "merge_python.csv" with lines
