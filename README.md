# arvres
Trabalho de Algoritmos e Estruturas de Dados III da UFPR

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/VytorCalixto/arvres?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

## Especificação do trabalho:

Trabalho de Alg III - 2015-1

Data de entrega: 29/05
Numero de integrantes(equipe): MAX 3 alunos


### Descrição:

Carlos Eduardo adora jogar. É uma das coisas que mais faz ele feliz nessa vida. Carlos Eduardo quer tornar isso mais prazeroso e menos trabalhoso. Ele encontrou uma bela solução.

Carimbo, seu irmão, o ensinou a mexer com Árvores de Busca Balanceadas e ele as achou muito úteis e interessantes. Ele gostou particularmente de duas: AVL e 2-3-4. 

Ele quer salvar apenas 3 informações dos registros dos jogos: código (criado por ele), nome (parte principal) e descrição (sintetizada). Mas, enquanto pensava como salvar essas informações, ele considerou que poderia precisar/querer procurar os jogos tanto por nome quanto por código. Então resolveu armazenar nas duas árvores com chaves diferentes:

- AVL -> Código
- 2-3-4 -> Nome

Eles devem ser responsáveis por mostrar em qual linha do registro o jogo está armazenado. 

A maioria dos jogos que Carlos Eduardo tem são da Steam e, atualmente, ele usa um linux maroto. No dia 05/05/2015, a lista de jogos da SteamOS+Linux está em 2100, mas como ele é um menino que pensa no futuro, vai colocar um numero maior e códigos mais espaçados. 

* De 10001 até 16000 -> jogos que tem.
* De 16001 até 22000 -> jogos que já jogou e quer comprar.
* De 22001 até 28000 -> jogos que escutou falar e gostou.
* De 28001 até 34000 -> jogos que nunca escutou falar.
* De 34001 até 40000 -> jogos que já jogou e nao gostou.
* De 40001 até 46000 -> jogos que as mães dos criadores deveria ter vergonha.

Carlos Eduardo acha que é um número razoável, pelos menos por enquanto. Algum dia, talvez, se arrependa.
Ele não quer colocar os nomes inteiros dos jogos, entao irá manter apenas um indicador do nome (no lugar de Portal 2 -> Portal, em vez de Team Fortress 2 -> Fortress ...), os diferenciando na descricao. Por isso, para referencia, se houver nomes repedidos os salve a Direita.


*********************************************************************
Especificações de Carlos Eduardo:

Carlos Eduardo é exigente e está anotando instruções especificas do que quer fazer. Vamos ver abaixo o que ele quer fazer:

O programa terá o nome de steamGames e será feito em linguagem C. 

O programa deve permitir duas ações: inserir e buscar. Na busca ele pode ainda escolher se quer buscar por nome ou pelo código. Veja como ele quer abaixo: 

Execução:
	
  `./steamGames arqDados arqBuscas`

  ex.: 
    `./steamGames registros.lol buscarJogos.txt > minhaListaJogos.txt`

Na execucao da busca será puxado os dados de registro.lol, deve ser impresso as duas árvores inteiras (conforme especificacao abaixo) e terá as seguintes características:
* c 10001    -> c == codigo == AVL
* n Portal   -> n == nome == 2-3-4
* f -> f == fim da busca

--------------------------------------------------------------------------------------------------

Suponha que o conteudo do arquivo registros.lol é:

```
10001 Portal Esse e' referente ao jogo Portal 2. Muuuito tops! Um dos melhores jogos da zuera! Descricao do site: "The 'Perpetual Testing Initiative' has been expanded to allow you to design co-op puzzles for you and your friends!"
10002 Torchlight Esse e' referente ao jogo Torchlight II. Bom RPG. Varias opcoes. OBS.: meu bicho de estimacao e' um panda chamado ZueraAssassina.
22001 Goat Jogo Goat Simulator. Parece muito louco! A cabra sobe em uma escada pelo pescoco. 
28001 Savage Jogo Savage Lands. A qualidade parece boa. User reviews: Very positive. 
16001 Portal Esse e' referente so ao jogo Portal. Nao tem algumas coisas do Portal 2, mas mesmo assim...
0
```

E que o conteudo do arquivo buscarJogos.txt é:
```
c 22001
n savage
n portal
f
```

A execucao do programa com a chamada 

`./steamGames registros.lol buscarJogos.txt`

Deve ser como mostrado abaixo.
```
Codigo:
(10002 (10001) (22001 (16001) (28001)))
```
```
Nome:
(Portal (Goat) (Savage;Portal;Torchlight))
```

```
22001 Goat Jogo Goat Simulator. Parece muito louco! A cabra sobe em uma escada pelo pescoco. 
Savage 28001 Jogo Savage Lands. A qualidade parece boa. User reviews: Very positive.
Portal 10001 Esse e' referente ao jogo Portal 2. Muuuito tops! Um dos melhores jogos da zuera! Descricao do site: "The "Perpetual Testing Initiative" has been expanded to allow you to design co-op puzzles for you and your friends!"
Portal 16001 Esse e' referente so ao jogo Portal. Nao tem algumas coisas do Portal 2, mas mesmo assim...
```


--------------------------------------------------------------------------------------------------


Detalhes de Entrega:

Deve ser enviado um arquivo compactado tar.gz com, no mínimo, os seguintes arquivos:
- main.c
- steamGames.c
- steamGames.h
- Makefile
- LEIAME  (com o cabeçalho especificado)

O compactado deve possuir o nome como login.tar.gz. Em caso de trabalho em grupo, deve possuir o login de todos - login1-login2-login3.tar.gz .
Após descompactar deve gerar uma pasta com o nome do compactado (login ou login1-login2-login3) com todos os arquivos necessários, sem subdiretórios.

O trabalho deve ser entregue até 23h59m do dia 29 de maio de 2015, contendo como título do e-mail "CI057 - Trabalho.2015-1" para o  professor de sua turma: 
andrey@inf.ufpr.br
carmem@inf.ufpr.br


*Qualquer dúvida, nao hesitem em procurar a monitoria no horário disponível ou mandar e-mail (cdp13@inf.ufpr.br)*


************************************************

Observações:                                        **IMPORTANTE**
- Deve compilar e rodar nas máquinas do Dinf
- O arquivo Makefile deve possuir opção clean (apaga todos os arquivos objeto -> .o)
- Utilizar o arquivo steamGames.h, podendo acrescentar funções que quiser e julgar necessárias, mas sem alterar o que já esta definido.
- Arquivo LEIAME - utilizando cabeçalho fornecido no arquivo
	-> O que colocar: detalhes do trabalho que achar interessante, dificuldades que teve na implementação e bugs conhecidos. 



------------------------------

Informacoes aleatórias:
- Por que registro.lol? Porque na steam só tem Dota.
- Carlos Eduardo possui nomes muito interessantes em sua família. 
