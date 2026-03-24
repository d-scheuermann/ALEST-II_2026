# "Receita de bolo" para fazer gráficos a partir
# de um arquivo de dados com o Gnuplot

# Ajuste conforme a necessidade. Para plotar mais de um
# arquivo de dados, separe por vírgulas
# ex: plot "a.txt" with lines, "b.txt" with lines, ...

# Execute com: gnuplot plot.gnu
# Gera o gráfico compara-sorts.pdf 
# (usei a saída em C, se quiserem ver as outras é só trocar abaixo)

set term pdf
set output "compara-sorts.pdf"
# Assumindo que os nomes dos arquivos são esses, caso não sejam... altere à vontade!
plot "merge_c.txt" with lines title "Merge", "quick_c.txt" with lines title "Quick", "heap_c.txt" with lines title "Heap"

