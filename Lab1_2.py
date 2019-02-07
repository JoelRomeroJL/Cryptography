from collections import OrderedDict

old_alphabet = []
new_alphabet = []
ALPHABET_SIZE = 256

#Use collections
#Function used to remove duplicates from key
def removeDup(string):
    return ''.join(OrderedDict.fromkeys(string))

def encrypt(plaintext):
    ciphertext = ""
    for character in plaintext:
        index = ord(character)
        #index = old_alphabet.index(character)
        ciphertext = ciphertext + str(chr(new_alphabet.index(index)))
    return ciphertext

def decrypt(ciphertext):
    plaintext = ""
    for character in ciphertext:
        index = ord(character)
        #index = new_alphabet.index(character)
        plaintext = plaintext + str(chr(old_alphabet.index(index)))
    return plaintext


if __name__ == '__main__':
    print("============= MIXED ALPHABET CIPHER =============")

    key = str(input("Please insert the key: ")).replace("\s", "")

    #Clean key as a list
    clean_key = list(removeDup(key))
    print("Clean key: ", clean_key)
    
    for i in range(0, ALPHABET_SIZE):
        old_alphabet.append(i)


    temp_alphabet = old_alphabet.copy()

    for character in clean_key:
        try:
            char_as_int = ord(character)
            new_alphabet.append(char_as_int)
            temp_alphabet.remove(char_as_int)
        except:
            print("The character ", character, " from the key is not valid")

    #Old alphabet before character removal
    print("Old alphabet: ", old_alphabet)

    #New alphabet formed (permutation)
    for char_as_int in temp_alphabet:
        new_alphabet.append(char_as_int)
    print("New alphabet: ", new_alphabet)
    
    operation_mode = int(input("\nSelect an operation mode (0:Encrypt, 1:Decrypt): "))

    if operation_mode == 0:
        pt = str(input("\nInsert name of FILE with the plainText: "))
        ct = str(input("\nInsert name of FILE for save the cipherText: "))
        file_read = open(pt, "r", encoding = 'utf-8')
        file_write = open(ct, "w", encoding = 'utf-8')
        for line in file_read:
            sentence = line
            if len(sentence) > 0:
                c_sentence = encrypt(sentence)    
#                print("Message encrypted ASCII: ", c_sentence)
#                print("Message encrypted: ", str(c_sentence))
                file_write.write(c_sentence)

        file_read.close()
        file_write.close()
        
    elif operation_mode == 1:
        pt = str(input("\nInsert name of FILE with the ipherText: "))
        ct = str(input("\nInsert name of FILE for save the plainText: "))

        file_read = open(pt, "r", encoding='utf-8')
        file_write = open(ct, "w", encoding='utf-8')

        for line in file_read:
            sentence = line
            if len(sentence) > 0:
                d_sentence = decrypt(sentence)
#                print("Message decrypted ASCII: ", d_sentence)
#                print("Message decrypted: ", str(d_sentence))
                file_write.write(d_sentence)

        file_read.close()
        file_write.close()
    else:
        print("Bad selection on operation mode :c")




    






# if character == ' ':
#            ciphertext = ciphertext + ' '     
#        elif character == '\n':
#            ciphertext = ciphertext + '\n'   
#        else:    
        
