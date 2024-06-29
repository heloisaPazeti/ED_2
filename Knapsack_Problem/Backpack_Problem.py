import numpy as np

####################################################### ITEM CLASS

class Item:
    def __init__(self, weight, value, ratio):           # Inicializador
        self.weight = weight                            # Salva o peso
        self.value = value                              # Salva o valor   
        self.ratio = ratio   

####################################################### PROG. DIN.

def Prog_Din(items, c):

    solution = []                                                                       # Solução
    totalValue = 0                                                                      # Valor total final
    r = np.zeros(shape=(len(items)+1, c+1))                                             # Criando matriz solução (elementos+1) x (capacidade+1)

    lin = 1
    col = 1

    for lin in range(len(items)+1):
        for col in range(c+1):
            if(lin > 0):                                                                
                if(items[lin-1].weight <= col):                                         # Se o peso for menor ou igual que a capacidade naquela coluna
                    r[lin, col] = items[lin-1].value                                    # Recebe o valor naquela coordenada

                    if(col - items[lin-1].weight > 0 and lin > 0):                      # Se houver "espaço sobrando"
                        r[lin, col] += r[lin-1, col - items[lin-1].weight]              # Soma-se o valor na linha anterior na coluna - peso

                elif((items[lin-1].weight > col) and (lin > 0)):                        # Se peso for maior que a capacidade na coluna
                    r[lin, col] = r[lin-1, col]                                         # Coloca-se o mesmo valor da linha anterior


                if (r[lin, col] < r[lin-1, col] and lin > 0):                           # Se na linha for um valor menor que a anterior
                    r[lin, col] = r[lin-1, col]                                         # Coloca-se a anterior


    totalValue = r[lin, col]                                                            # O valor final total é o da última coordenada

    while lin > 0:                                                                      # Montando "caminho" solução

        dif = r[lin, col] - r[lin-1,col]                                                # calcula-se a diferença entre duas linhas

        if(dif > 0):                                                                    # Se diferença maior que 0
            solution.append(lin-1)                                                      # Adiciona seu index na solução
            col -= items[lin-1].weight                                                  # Move para coluna - peso

        lin -= 1                                                                        # Retorna uma linha

    return totalValue, solution

####################################################### ALG. GULOSO

def Glut(items, capacity):

    solution = []                                                       # Array solução final
    w = 0                                                               # Peso da mochila
    v = 0                                                               # Valor da mochila

    items.sort(key=lambda x: (x.ratio, -x.weight), reverse=True)        # Array ordenado do maior ao menor ratio, e do menor ao maior peso

    for i in range(len(items)):
        if((w + items[i].weight) > capacity):                           # Se já tiver batido a capacidade da mochila
            return v, solution                                          # Retonar valor e solução final
        
        w += items[i].weight                                            # Soma o peso do item
        v += items[i].value                                             # Soma o valor do item

        solution.append(i)                                              # Adiciona na solução

    return v, solution

####################################################### MAIN

def Main():

    items = []                                                      # Itens a serem adicionados
    itemsCopy = []                                                  # Cópia dos itens não ordenados
    solG = []                                                       # Solução Final Guloso

    D = input().split()                                             # Coletando entradas
    P = int(D[0])                                                   # Peso máx da mochila
    Q = int(D[1])                                                   # Total de elementos

    for i in range(Q):                                              # Coletando dados do problema
        data = input().split()
        w = int(data[0])                                            # Peso do item
        v = int(data[1])                                            # Valor do item
        r = v / w                                                   # Razão = valor / peso

        newItem = Item(w, v, r)                                     # Criando novo item
        items.append(newItem)                                       # Adicionando a lista geral

    itemsCopy = items.copy()                                        # Fazendo cópia da lista

    vProgDin, solutionProgDin = Prog_Din(items, P)                  # Recebendo resultado da programação dinâmica
    vGlut, solutionGlut = Glut(items, P)                            # Recebendo resultado do algoritmo guloso
    porcent = (100*vGlut) / vProgDin                                # Calculando porcentagem dos resultados

    for i in range(len(solutionGlut)):                              # Encontrando index correto da lista não ordenada
        solG.append(itemsCopy.index(items[solutionGlut[i]])) 
    
    print(*list(reversed(solutionProgDin)))                         # Printando solução programação dinâmica
    print(*solG)                                                    # Printando solução algortimo guloso
    print(int(vProgDin), vGlut)                                     # Printando valores finais
    print("{:.2f}".format(porcent))                                 # Printando porcentagem

####################################################### CALL

Main()
