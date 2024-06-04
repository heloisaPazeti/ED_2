class HashItem:
    def __init__(self, word, quant, key):
        self.word = word
        self.quant = quant
        self.key = key

class HashTable:
    def __init__(self, size, c1, c2):
        self.size = size
        self.count = 0
        self.c1 = c1
        self.c2 = c2
        self.item = []


def Insert_Hash():
    text = input().split(' ')
    print(text)
    

while(1):

    tableData = input().split()

    tableSize = int(tableData[0])
    c1 = int(tableData[1])
    c2 = int(tableData[2])

    hashTable = HashTable(tableSize, c1, c2)


    op = -1    
    op = int(input())

    while(1):

        match op:
            case 0:
                exit()
            case 1:
                Insert_Hash()



    """""

    match op:
        case 1: 
            T1()
        case 2:
            T2()
        case 3:
            T3()
        case 4:
            T4()
        case 5:
            T5()
        case _:
            print("\n>> COMANDO NAO ENCONTRADO\n")

    """
