#Gerenciamento de informações em arquivo binário

#Contribuidores: Frederico Maia Estrella, Guilherme Luiz de Azevedo, Gabriel Ferreira de Castro

#Compilação: g++ -Wall ./main.cpp -o exec.exe

#Execução: ./exec.exe

#Fluxo de execução: ao iniciar, o arquivo csv é lido e passa as informações para um arquivo tipado. Assim, toda e qualquer operação realizada pelo programa será feita diretamente no arquivo tipado (binário). Dentre as operações, temos:

*Adicionar registro em posição específica
*Editar registro de posição específica
*Trocar 2 registros de posição
*Mostrar todos os registros
*Mostrar registros em intervalo de posições
*Imprimir busca a partir da area

Procedimentos internas do programa:
*lerCsvEGravarBinario -> busca dados do csv e escreve no binário 
*nPessoasBin -> calcula o número de registros no arquivo tipado
*nPessoasCsv -> calcula o número de registros no arquivo csv
*main -> inputs + interface