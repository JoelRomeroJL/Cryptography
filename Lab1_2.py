from collections import OrderedDict

old_alphabet = []
new_alphabet = []
ALPHABET_SIZE = 255

#----------------------------Remove spaces-------------------------------
def removeDup(string):
    return ''.join(OrderedDict.fromkeys(string))
#------------------------------------------------------------------------

#------------------------------Encrypt-----------------------------------
def encrypt(plaintext):
    ciphertext = ""
    for character in plaintext:
        index = old_alphabet.index(ord(character))
        #print(" ",index)
        ciphertext = ciphertext + chr(new_alphabet[index])
    return ciphertext
#------------------------------------------------------------------------

#------------------------------Decrypt-----------------------------------
def decrypt(ciphertext):
    plaintext = ""
    for character in ciphertext:
        index = new_alphabet.index(ord(character))
        #print(" ",index)
        plaintext = plaintext + chr(old_alphabet[index])
    return plaintext
#------------------------------------------------------------------------


if __name__ == '__main__':
    
    print("-------------------MIXED ALPHABET CIPHER----------------------------")
    key = str(input("Please insert the key: ")).replace("\s", "")

 #------------------------Remove spaces in the key------------------------
    clean_key = list(removeDup(key))
    print("Clean key: ", clean_key)
 #------------------------------------------------------------------------

 #---------------------------Create Alphabet------------------------------
    for i in range(32, ALPHABET_SIZE):
        old_alphabet.append(i)

 #----------------Old alphabet before character removal--------------
    print("\nOld alphabet: ", old_alphabet)
 #------------------------------------------------------------------------
    temp_alphabet = old_alphabet.copy()
 #----------------------------New Alphabet--------------------------------
 #-----------Verify that Clen key belongs to alphabet------------
    for character in clean_key:
        try:
            char_as_int = ord(character)
            new_alphabet.append(char_as_int)
            temp_alphabet.remove(char_as_int)
        except:
             print("The character ", character, " from the key is not valid")           
 #----------------New alphabet formed (permutation)--------------
    
    for char_as_int in temp_alphabet:
        new_alphabet.append(char_as_int)
    print("\nNew alphabet: ", new_alphabet)
 #------------------------------------------------------------------------

 #------------------------------------MENU--------------------------------------
    option = int(input("\nSelect an operation mode (0:Encrypt, 1:Decrypt): "))

    if option == 0:

        pt = str(input("\nInsert name of FILE with the plainText: "))
        ct = str(input("\nInsert name of FILE for save the cipherText: "))
        
        try:
            file_read = open(pt, "r", encoding = 'utf-8')
        except:
             print("Somethings wrong, we can't open the file: ", pt)
             
        try:
            file_write = open(ct, "w", encoding = 'utf-8')
        except:
             print("Somethings wrong, we can't open the file: ", ct)
             
        print("\nMessage encrypted: ")     

        for line in file_read:
            sentence = line.rstrip('\n')
            if len(sentence) > 0:
                c_sentence = encrypt(sentence)    
                print(c_sentence)
                file_write.write(c_sentence + "\n")

        file_read.close()
        file_write.close()
        
    elif option == 1:

        pt = str(input("\nInsert name of FILE with the ipherText: "))
        ct = str(input("\nInsert name of FILE for save the plainText: "))

        try:
            file_read = open(pt, "r", encoding = 'utf-8')
        except:
             print("Somethings wrong, we can't open the file: ", pt)
             
        try:
            file_write = open(ct, "w", encoding = 'utf-8')
        except:
             print("Somethings wrong, we can't open the file: ", ct)
                     
        print("\nMessage decrypted: ")
                     
        for line in file_read:
            sentence = line.rstrip('\n')
            if len(sentence) > 0:
                d_sentence = decrypt(sentence)
                print(d_sentence)
                file_write.write(d_sentence + "\n")

        file_read.close()
        file_write.close()
    else:
        print("Bad selection on operation mode :c")
 #-----------------------------------------------------------------------------