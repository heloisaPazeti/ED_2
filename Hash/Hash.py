#################################
# HELOÍSA PAZETI - 14577991
#################################

# OBS 1: uma posição NULA nunca teve um valor, uma posição com QUANT == 0 já teve. 
#        Isso ajuda a diminuir o tempo de busca. Assim não é necessário passar a lista inteira.
#        Apenas encontrar o primeiro espaço que aquele valor x de hash nunca foi alcançado.


########################################################################################## ITEM CLASS

class HashItem:
    def __init__(self, word, key):          # Inicializador
        self.word = word                    # Salva a palavra
        self.quant = 1                      # Salva a quantidade de vezes que a palavra foi salva
        self.key = key                      # key = posição dentro da lista

    def Delete(hashItem):                   # Deletar = "Reiniciar" item 
        hashItem.word = ""                  # Deixa vazio o texto
        hashItem.quant = 0                  # Zera a quantidade
        hashItem.key = -1                   # Deixa uma posição "inválida" para esse contexto

########################################################################################## HASH TABLE CLASS

class HashTable:
    def __init__(self, size, c1, c2):       # Inicializador
        self.size = size                    # Tamanho da lista
        self.count = 0                      # Quantidade de itens na lista
        self.c1 = c1                        # Constante 1 utilizado no hash
        self.c2 = c2                        # Constante 2 utilizado no hash
        self.items = [None] * size          # Lista inicializada com nulos

    ######################################################## HASH TABLE ACTIONS

    def Insert_Hash(hashTable):
    
        text = input().split()                      # Pega o texto para inserção e separa em um vetor palavra a palavra
        
        for w in text:                              # Para cada palavra dentro desse vetor

            pos = hashTable.FindPos(w)              # Encontra a posição para inserir

            if(pos >= 0):                           # Se a posição for válida
                newSave = HashItem(w, pos)          # Inicializa um novo item
                hashTable.items[pos] = newSave      # Salva sua posição
                hashTable.count += 1                # Aumenta o contador da tabela

    def Search_Hash(hashTable):                         # Procura dentro da tabela

        lines = int(input())                            # Palavras para buscar

        for i in range(lines):                      
            element = input()                           # Elemento para buscar
            hashItem = hashTable.FindElement(element)   # Procura elemento

            if(hashItem == None):                       # Se for nulo, não encontrou
                print(element, "nao encontrada")
            else:
                print(hashItem.word, "encontrada", hashItem.quant)

    def Delete_Hash(hashTable):                         # Deleta da Tabela

        lines = int(input())                            # Quantos itens para deletar

        for i in range(lines):
            element = input()                           # Elemento a deletar
            hashItem = hashTable.FindElement(element)   # Busca elemento na tabela

            if(hashItem == None):                       # Se for nulo não remove
                print(element, "nao encontrada")
            else:                                       # Se for
                print(hashItem.word, "removida")        # Printa a remoção
                hashItem.Delete()                       # Deleta / Reinicia a posição
                hashTable.count -= 1                    # Diminui o contador

    ######################################################## FINDS

    def FindPos(hashTable, w):                                          # Procura uma posição para inserção

        i = 0                                                           # Contador para Hash Secundário
        savePos = -1                                                    # Possível posição
        hashValue = Hash_Func(w, hashTable.size)                        # Valor inicial do Hash
        pos = hashValue

        while(hashTable.items[pos] != None):                            # Enquanto a posição não for nula

            if(hashTable.items[pos].word == w):                         # Se for a palavra procurada
                hashTable.items[pos].quant += 1                         # Adiciona um na quantidade
                return -1                                               # Sinaliza que não precisa adicionar nova

            if(hashTable.items[pos].quant == 0):                        # Se a quant for zero (já esteve ocupado)
                savePos = pos                                           # Salva como possível posição

            pos = QuadraticProbing(hashTable, i, hashValue)             # Calcula próxima posição
            i += 1                                                      # Segue pelo i
        
        if(savePos != -1):                                              # Nesse caso temos uma posição possível
            pos = savePos 

        return pos
    
    def FindElement(hashTable, w):                                      # Procura elemento na tabela

        i = 0                                                           # Contador Hash Secundário
        hashValue = Hash_Func(w, hashTable.size)                        # Hash inicial
        pos = hashValue

        while(hashTable.items[pos] != None):                            # Enquanto não for nulo (nunca foi ocupado)

            if(hashTable.items[pos].word == w):                         # Se encontrar a palavra
                return hashTable.items[pos]                             # Retonar palavra
            
            pos = QuadraticProbing(hashTable, i, hashValue)             # Continua procurando
            i += 1

        return None                                                     # Caso não encontre retorna nulo

    def Find_Most_Frequent(hashTable):                                  # Encontrar mais frequente

        if(hashTable.count <= 0):                                       # Lista vazia
            return
        
        mostFreq = HashItem("~", -1)                                    # Um item qualquer para iniciar

        for i in range(hashTable.size):                                 # Compara com todos os itens da tabela

            if(hashTable.items[i] != None):                             # Se item não for nulo
                if(mostFreq.quant < hashTable.items[i].quant):          # Verifica quant e ordem alfabética
                    mostFreq = hashTable.items[i]
                elif((mostFreq.quant == hashTable.items[i].quant) and (mostFreq.word > hashTable.items[i].word)):
                    mostFreq = hashTable.items[i]

        return mostFreq

    ######################################################## PRINTS

    def PrintInfo_Hash(hashTable):                      # Printa as infos

        mostFreq = hashTable.Find_Most_Frequent()       # Encontra a mais frequente

        print("foram encontradas", hashTable.count, "palavras diferentes")
        print("palavra mais frequente = ", mostFreq.word, ", encontrada ", mostFreq.quant, " vezes", sep='')

    def PrintAll(hashTable):                            # Printa todas as informações na tabela

        print("imprimindo tabela hash")

        for item in hashTable.items:

            if(item != None and item.quant > 0):        # Qualquer posição não nula e com quant > 0 printa seu item
                print(item.word, item.key)

        print("fim da tabela hash")


###################################### HASH FUNCTIONS

def Hash_Func(word, tableSize):                 # Função Hash disponibilizada
    
    v = 0
    for i in range(len(word)):
        v += 3*v + ord(word[i])                 # ord -> pega o valor int char do caractere
        v = v % tableSize

    return v

def QuadraticProbing(hashTable, i, hashValue):      # Calcula o Hash Quadrático para lidar com colisões

    pos = -1
    pos = (hashValue + (hashTable.c1)*i + (hashTable.c2)*i*i) % hashTable.size
    return pos


########################################################################################## MAIN

while(1):

    tableData = input().split()                     # Pega info da tabela

    tableSize = int(tableData[0])                   # Separa essas infos
    c1 = int(tableData[1])
    c2 = int(tableData[2])

    hashTable = HashTable(tableSize, c1, c2)        # Constrói a tabela

    while(1):

        op = int(input())                           # Pega opções

        match op:
            case 0:
                exit()
            case 1:
                hashTable.Insert_Hash()
            case 2:
                hashTable.PrintInfo_Hash()
            case 3:
                hashTable.Search_Hash()
            case 4:
                hashTable.Delete_Hash()
            case 5:
                hashTable.PrintAll()
            case _:
                print(">> COMANDO NAO ENCONTRADO...")
